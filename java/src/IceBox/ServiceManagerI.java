// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceBox;

//
// NOTE: the class isn't final on purpose to allow users to eventually
// extend it.
//
public class ServiceManagerI extends _ServiceManagerDisp
{
    public
    ServiceManagerI(Ice.Communicator communicator, String[] args)
    {
        _communicator = communicator;
        _logger = _communicator.getLogger();
        _argv = args;
        _traceServiceObserver = _communicator.getProperties().getPropertyAsInt("IceBox.Trace.ServiceObserver");
        _observerCompletedCB = new Ice.Callback()
            {
                public void completed(Ice.AsyncResult result)
                {
                    try
                    {
                        result.throwLocalException();
                    }
                    catch(Ice.LocalException ex)
                    {
                        ServiceObserverPrx observer = ServiceObserverPrxHelper.uncheckedCast(result.getProxy());
                        synchronized(ServiceManagerI.this)
                        {
                            if(_observers.remove(observer))
                            {
                                observerRemoved(observer, ex);
                            }
                        }
                    }
                }
            };
    }

    public java.util.Map<String, String>
    getSliceChecksums(Ice.Current current)
    {
        return SliceChecksums.checksums;
    }

    public void
    startService(String name, Ice.Current current)
        throws AlreadyStartedException, NoSuchServiceException
    {
        ServiceInfo info = null;
        synchronized(this)
        {
            //
            // Search would be more efficient if services were contained in
            // a map, but order is required for shutdown.
            //
            for(ServiceInfo p : _services)
            {
                if(p.name.equals(name))
                {
                    if(p.status == StatusStarted)
                    {
                        throw new AlreadyStartedException();
                    }
                    p.status = StatusStarting;
                    info = (ServiceInfo)p.clone();
                    break;
                }
            }
            if(info == null)
            {
                throw new NoSuchServiceException();
            }
            _pendingStatusChanges = true;
        }

        boolean started = false;
        try
        {
            info.service.start(name, info.communicator == null ? _sharedCommunicator : info.communicator, info.args);
            started = true;
        }
        catch(java.lang.Exception e)
        {
            java.io.StringWriter sw = new java.io.StringWriter();
            java.io.PrintWriter pw = new java.io.PrintWriter(sw);
            e.printStackTrace(pw);
            pw.flush();
            _logger.warning("ServiceManager: exception while starting service " + info.name + ":\n" + sw.toString());
        }

        synchronized(this)
        {
            for(ServiceInfo p : _services)
            {
                if(p.name.equals(name))
                {
                    if(started)
                    {
                        p.status = StatusStarted;

                        java.util.List<String> services = new java.util.ArrayList<String>();
                        services.add(name);
                        servicesStarted(services, _observers);
                    }
                    else
                    {
                        p.status = StatusStopped;
                    }
                    break;
                }
            }
            _pendingStatusChanges = false;
            notifyAll();
        }
    }

    public void
    stopService(String name, Ice.Current current)
        throws AlreadyStoppedException, NoSuchServiceException
    {
        ServiceInfo info = null;
        synchronized(this)
        {
            //
            // Search would be more efficient if services were contained in
            // a map, but order is required for shutdown.
            //
            for(ServiceInfo p : _services)
            {
                if(p.name.equals(name))
                {
                    if(p.status == StatusStopped)
                    {
                        throw new AlreadyStoppedException();
                    }
                    p.status = StatusStopping;
                    info = (ServiceInfo)p.clone();
                    break;
                }
            }
            if(info == null)
            {
                throw new NoSuchServiceException();
            }
            _pendingStatusChanges = true;
        }

        boolean stopped = false;
        try
        {
            info.service.stop();
            stopped = true;
        }
        catch(java.lang.Exception e)
        {
            java.io.StringWriter sw = new java.io.StringWriter();
            java.io.PrintWriter pw = new java.io.PrintWriter(sw);
            e.printStackTrace(pw);
            pw.flush();
            _logger.warning("ServiceManager: exception while stopping service " + info.name + ":\n" + sw.toString());
        }

        synchronized(this)
        {
            for(ServiceInfo p : _services)
            {
                if(p.name.equals(name))
                {
                    if(stopped)
                    {
                        p.status = StatusStopped;

                        java.util.List<String> services = new java.util.ArrayList<String>();
                        services.add(name);
                        servicesStopped(services, _observers);
                    }
                    else
                    {
                        p.status = StatusStarted;
                    }
                    break;
                }
            }
            _pendingStatusChanges = false;
            notifyAll();
        }
    }

    public void
    addObserver(final ServiceObserverPrx observer, Ice.Current current)
    {
        java.util.List<String> activeServices = new java.util.LinkedList<String>();

        //
        // Null observers and duplicate registrations are ignored
        //

        synchronized(this)
        {
            if(observer != null && _observers.add(observer))
            {
                if(_traceServiceObserver >= 1)
                {
                    _logger.trace("IceBox.ServiceObserver",
                                  "Added service observer " + _communicator.proxyToString(observer));
                }

                for(ServiceInfo info: _services)
                {
                    if(info.status == StatusStarted)
                    {
                        activeServices.add(info.name);
                    }
                }
            }
        }

        if(activeServices.size() > 0)
        {
            observer.begin_servicesStarted(activeServices.toArray(new String[0]), _observerCompletedCB);
        }
    }

    public void
    shutdown(Ice.Current current)
    {
        _communicator.shutdown();
    }

    public int
    run()
    {
        try
        {
            Ice.Properties properties = _communicator.getProperties();

            //
            // Create an object adapter. Services probably should NOT share
            // this object adapter, as the endpoint(s) for this object adapter
            // will most likely need to be firewalled for security reasons.
            //
            Ice.ObjectAdapter adapter = null;
            if(properties.getProperty("IceBox.ServiceManager.Endpoints").length() != 0)
            {
                adapter = _communicator.createObjectAdapter("IceBox.ServiceManager");

                Ice.Identity identity = new Ice.Identity();
                identity.category = properties.getPropertyWithDefault("IceBox.InstanceName", "IceBox");
                identity.name = "ServiceManager";
                adapter.add(this, identity);
            }

            //
            // Parse the property set with the prefix "IceBox.Service.". These
            // properties should have the following format:
            //
            // IceBox.Service.Foo=[jar-or-dir:]Package.Foo [args]
            //
            // We parse the service properties specified in IceBox.LoadOrder
            // first, then the ones from remaining services.
            //
            final String prefix = "IceBox.Service.";
            java.util.Map<String, String> services = properties.getPropertiesForPrefix(prefix);
            String[] loadOrder = properties.getPropertyAsList("IceBox.LoadOrder");
            java.util.List<StartServiceInfo> servicesInfo = new java.util.ArrayList<StartServiceInfo>();
            for(String name : loadOrder)
            {
                if(name.length() > 0)
                {
                    String key = prefix + name;
                    String value = services.get(key);
                    if(value == null)
                    {
                        FailureException ex = new FailureException();
                        ex.reason = "ServiceManager: no service definition for `" + name + "'";
                        throw ex;
                    }
                    servicesInfo.add(new StartServiceInfo(name, value, _argv));
                    services.remove(key);
                }
            }
            for(java.util.Map.Entry<String, String> p : services.entrySet())
            {
                String name = p.getKey().substring(prefix.length());
                String value = p.getValue();
                servicesInfo.add(new StartServiceInfo(name, value, _argv));
            }

            //
            // Check if some services are using the shared communicator in which
            // case we create the shared communicator now with a property set which
            // is the union of all the service properties (services which are using
            // the shared communicator).
            //
            if(properties.getPropertiesForPrefix("IceBox.UseSharedCommunicator.").size() > 0)
            {
                Ice.InitializationData initData = new Ice.InitializationData();
                initData.properties = createServiceProperties("SharedCommunicator");
                for(StartServiceInfo service : servicesInfo)
                {
                    if(properties.getPropertyAsInt("IceBox.UseSharedCommunicator." + service.name) <= 0)
                    {
                        continue;
                    }

                    //
                    // Load the service properties using the shared communicator properties as
                    // the default properties.
                    //
                    Ice.StringSeqHolder serviceArgs = new Ice.StringSeqHolder(service.args);
                    Ice.Properties svcProperties = Ice.Util.createProperties(serviceArgs, initData.properties);
                    service.args = serviceArgs.value;

                    //
                    // Erase properties from the shared communicator which don't exist in the
                    // service properties (which include the shared communicator properties
                    // overriden by the service properties).
                    //
                    java.util.Map<String, String> allProps = initData.properties.getPropertiesForPrefix("");
                    for(String key : allProps.keySet())
                    {
                        if(svcProperties.getProperty(key).length() == 0)
                        {
                            initData.properties.setProperty(key, "");
                        }
                    }

                    //
                    // Add the service properties to the shared communicator properties.
                    //
                    for(java.util.Map.Entry<String, String> p : svcProperties.getPropertiesForPrefix("").entrySet())
                    {
                        initData.properties.setProperty(p.getKey(), p.getValue());
                    }

                    //
                    // Parse <service>.* command line options (the Ice command line options
                    // were parsed by the createProperties above)
                    //
                    service.args = initData.properties.parseCommandLineOptions(service.name, service.args);
                }

                //
                // If Ice metrics are enabled on the IceBox communicator, we also enable them on the 
                // shared communicator.
                // 
                IceInternal.MetricsAdminI metricsAdmin = null;
                if(_communicator.getObserver() instanceof IceInternal.CommunicatorObserverI)
                {
                    metricsAdmin = new IceInternal.MetricsAdminI(initData.properties, Ice.Util.getProcessLogger());
                    initData.observer = new IceInternal.CommunicatorObserverI(metricsAdmin);
                }

                _sharedCommunicator = Ice.Util.initialize(initData);

                //
                // Ensure the metrics admin plugin uses the same property set as the
                // communicator. This is necessary to correctly deal with runtime 
                // property updates.
                //
                if(metricsAdmin != null)
                {
                    metricsAdmin.setProperties(_sharedCommunicator.getProperties());
                }
            }

            for(StartServiceInfo s : servicesInfo)
            {
                start(s.name, s.className, s.classDir, s.absolutePath, s.args);
            }

            //
            // We may want to notify external scripts that the services
            // have started. This is done by defining the property:
            //
            // IceBox.PrintServicesReady=bundleName
            //
            // Where bundleName is whatever you choose to call this set of
            // services. It will be echoed back as "bundleName ready".
            //
            // This must be done after start() has been invoked on the
            // services.
            //
            String bundleName = properties.getProperty("IceBox.PrintServicesReady");
            if(bundleName.length() > 0)
            {
                System.out.println(bundleName + " ready");
            }

            //
            // Don't move after the adapter activation. This allows
            // applications to wait for the service manager to be
            // reachable before sending a signal to shutdown the
            // IceBox.
            //
            Ice.Application.shutdownOnInterrupt();

            //
            // Register "this" as a facet to the Admin object and
            // create Admin object
            //
            try
            {
                _communicator.addAdminFacet(this, "IceBox.ServiceManager");
                _communicator.getAdmin();
            }
            catch(Ice.ObjectAdapterDeactivatedException ex)
            {
                //
                // Expected if the communicator has been shutdown.
                //
            }

            //
            // Start request dispatching after we've started the services.
            //
            if(adapter != null)
            {
                try
                {
                    adapter.activate();
                }
                catch(Ice.ObjectAdapterDeactivatedException ex)
                {
                    //
                    // Expected if the communicator has been shutdown.
                    //
                }
            }

            _communicator.waitForShutdown();
            Ice.Application.defaultInterrupt();
        }
        catch(FailureException ex)
        {
            java.io.StringWriter sw = new java.io.StringWriter();
            java.io.PrintWriter pw = new java.io.PrintWriter(sw);
            pw.println(ex.reason);
            ex.printStackTrace(pw);
            pw.flush();
            _logger.error(sw.toString());
            return 1;
        }
        catch(Throwable ex)
        {
            java.io.StringWriter sw = new java.io.StringWriter();
            java.io.PrintWriter pw = new java.io.PrintWriter(sw);
            ex.printStackTrace(pw);
            pw.flush();
            _logger.error("ServiceManager: caught exception:\n" + sw.toString());
            return 1;
        }
        finally
        {
            //
            // Invoke stop() on the services.
            //
            stopAll();
        }

        return 0;
    }

    synchronized private void
    start(String service, String className, String classDir, boolean absolutePath, String[] args)
        throws FailureException
    {
        //
        // Load the class.
        //

        //
        // Use a class loader if the user specified a JAR file or class directory.
        //
        Class<?> c = null;
        if(classDir != null)
        {
            try
            {
                if(!absolutePath)
                {
                    classDir = new java.io.File(System.getProperty("user.dir") + java.io.File.separator +
                                                classDir).getCanonicalPath();
                }
                
                if(!classDir.endsWith(java.io.File.separator) && !classDir.endsWith(".jar"))
                {
                    classDir += java.io.File.separator;
                }
                
                //
                // Reuse an existing class loader if we have already loaded a plug-in with
                // the same value for classDir, otherwise create a new one.
                //
                ClassLoader cl = null;
                
                if(_classLoaders == null)
                {
                    _classLoaders = new java.util.HashMap<String, ClassLoader>();
                }
                else
                {
                    cl = _classLoaders.get(classDir);
                }
                
                if(cl == null)
                {
                    final java.net.URL[] url = new java.net.URL[] { new java.net.URL("file:///" + classDir) };
                    
                    cl = new java.net.URLClassLoader(url);
                    
                    _classLoaders.put(classDir, cl);
                }
                
                c = cl.loadClass(className);
            }
            catch(java.net.MalformedURLException ex)
            {
                throw new FailureException("ServiceManager: invalid entry point format `" + classDir + "'", ex);
            }
            catch(java.io.IOException ex)
            {
                throw new FailureException("ServiceManager: invalid path in plug-in entry point `" + classDir +
                                           "'", ex);
            }
            catch(java.lang.ClassNotFoundException ex)
            {
                // Ignored
            }
        }
        else
        {
            c = IceInternal.Util.findClass(className, null);
        }
        
        if(c == null)
        {
            throw new FailureException("ServiceManager: class " + className + " not found");
        }

        ServiceInfo info = new ServiceInfo();
        info.name = service;
        info.status = StatusStopped;
        info.args = args;

        //
        // If Ice.UseSharedCommunicator.<name> is defined, create a
        // communicator for the service. The communicator inherits
        // from the shared communicator properties. If it's not
        // defined, add the service properties to the shared
        // commnunicator property set.
        //
        Ice.Communicator communicator;
        IceInternal.MetricsAdminI metricsAdmin = null;
        if(_communicator.getProperties().getPropertyAsInt("IceBox.UseSharedCommunicator." + service) > 0)
        {
            assert(_sharedCommunicator != null);
            communicator = _sharedCommunicator;
            if(communicator.getObserver() instanceof IceInternal.CommunicatorObserverI)
            {
                IceInternal.CommunicatorObserverI o = (IceInternal.CommunicatorObserverI)communicator.getObserver();
                metricsAdmin = o.getMetricsAdmin();
            }
        }
        else
        {
            try
            {
                //
                // Create the service properties. We use the communicator properties as the default
                // properties if IceBox.InheritProperties is set.
                //
                Ice.InitializationData initData = new Ice.InitializationData();
                initData.properties = createServiceProperties(service);
                Ice.StringSeqHolder serviceArgs = new Ice.StringSeqHolder(info.args);
                if(serviceArgs.value.length > 0)
                {
                    //
                    // Create the service properties with the given service arguments. This should
                    // read the service config file if it's specified with --Ice.Config.
                    //
                    initData.properties = Ice.Util.createProperties(serviceArgs, initData.properties);

                    //
                    // Next, parse the service "<service>.*" command line options (the Ice command
                    // line options were parsed by the createProperties above)
                    //
                    serviceArgs.value = initData.properties.parseCommandLineOptions(service, serviceArgs.value);
                }
                
                //
                // Clone the logger to assign a new prefix. If one of the built-in loggers is configured
                // don't set any logger.
                //
                if(initData.properties.getProperty("Ice.LogFile").length() == 0 &&
                   (initData.properties.getPropertyAsInt("Ice.UseSyslog") == 0 ||
                    System.getProperty("os.name").startsWith("Windows")))
                {
                    initData.logger = _logger.cloneWithPrefix(initData.properties.getProperty("Ice.ProgramName"));
                }

                //
                // If Ice metrics are enabled on the IceBox communicator, we also enable them on
                // the service communicator.
                // 
                if(_communicator.getObserver() instanceof IceInternal.CommunicatorObserverI)
                {
                    metricsAdmin = new IceInternal.MetricsAdminI(initData.properties, initData.logger);
                    initData.observer = new IceInternal.CommunicatorObserverI(metricsAdmin);
                }
                
                //
                // Remaining command line options are passed to the communicator. This is
                // necessary for Ice plug-in properties (e.g.: IceSSL).
                //
                info.communicator = Ice.Util.initialize(serviceArgs, initData);
                info.args = serviceArgs.value;
                communicator = info.communicator;

                //
                // Ensure the metrics admin plugin uses the same property set as the
                // communicator. This is necessary to correctly deal with runtime 
                // property updates.
                //
                if(metricsAdmin != null)
                {
                    metricsAdmin.setProperties(communicator.getProperties());
                }
            }
            catch(Throwable ex)
            {
                FailureException e = new FailureException();
                e.reason = "ServiceManager: exception while starting service " + service;
                e.initCause(ex);
                throw e;
            }
        }

        try
        {
            //
            // Add a PropertiesAdmin facet to the service manager's communicator that provides
            // access to this service's property set. We do this prior to instantiating the
            // service so that the service's constructor is able to access the facet (e.g.,
            // in case it wants to set a callback).
            //
            final String facetName = "IceBox.Service." + service + ".Properties";
            IceInternal.PropertiesAdminI propAdmin = new IceInternal.PropertiesAdminI(facetName, 
                                                                                      communicator.getProperties(), 
                                                                                      communicator.getLogger());
            _communicator.addAdminFacet(propAdmin, facetName);

            //
            // If a metrics admin facet is setup for the service, register
            // it with the IceBox communicator.
            //
            if(metricsAdmin != null)
            {
                _communicator.addAdminFacet(metricsAdmin, "IceBox.Service." + info.name + ".Metrics");

                // Ensure the metrics admin facet is notified of property updates.
                propAdmin.addUpdateCallback(metricsAdmin);
            }

            //
            // Instantiate the service.
            //
            try
            {
                //
                // If the service class provides a constructor that accepts an Ice.Communicator argument,
                // use that in preference to the default constructor.
                //
                java.lang.Object obj = null;
                try
                {
                    java.lang.reflect.Constructor<?> con = c.getDeclaredConstructor(Ice.Communicator.class);
                    obj = con.newInstance(_communicator);
                }
                catch(IllegalAccessException ex)
                {
                    throw new FailureException(
                        "ServiceManager: unable to access service constructor " + className + "(Ice.Communicator)", ex);
                }
                catch(NoSuchMethodException ex)
                {
                    // Ignore.
                }
                catch(java.lang.reflect.InvocationTargetException ex)
                {
                    if(ex.getCause() != null)
                    {
                        throw ex.getCause();
                    }
                    else
                    {
                        throw new FailureException("ServiceManager: exception in service constructor for " + className, ex);
                    }
                }

                if(obj == null)
                {
                    //
                    // Fall back to the default constructor.
                    //
                    try
                    {
                        obj = c.newInstance();
                    }
                    catch(IllegalAccessException ex)
                    {
                        throw new FailureException(
                            "ServiceManager: unable to access default service constructor in class " + className, ex);
                    }
                }

                try
                {
                    info.service = (Service)obj;
                }
                catch(ClassCastException ex)
                {
                    throw new FailureException("ServiceManager: class " + className + " does not implement IceBox.Service");
                }
            }
            catch(InstantiationException ex)
            {
                throw new FailureException("ServiceManager: unable to instantiate class " + className, ex);
            }
            catch(FailureException ex)
            {
                throw ex;
            }
            catch(Throwable ex)
            {
                throw new FailureException("ServiceManager: exception in service constructor for " + className, ex);
            }

            try
            {
                info.service.start(service, communicator, info.args);

                //
                // There is no need to notify the observers since the 'start all'
                // (that indirectly calls this method) occurs before the creation of
                // the Server Admin object, and before the activation of the main
                // object adapter (so before any observer can be registered)
                //
            }
            catch(FailureException ex)
            {
                throw ex;
            }
            catch(Throwable ex)
            {
                FailureException e = new FailureException();
                e.reason = "ServiceManager: exception while starting service " + service;
                e.initCause(ex);
                throw e;
            }

            info.status = StatusStarted;
            _services.add(info);
        }
        catch(Ice.ObjectAdapterDeactivatedException ex)
        {
            //
            // Can be raised by addAdminFacet if the service manager communicator has been shut down.
            //
            if(info.communicator != null)
            {
                destroyServiceCommunicator(service, info.communicator);
            }
        }
        catch(RuntimeException ex)
        {
            try
            {
                _communicator.removeAdminFacet("IceBox.Service." + service + ".Properties");
            }
            catch(Ice.LocalException e)
            {
                // Ignored
            }

            if(info.communicator != null)
            {
                destroyServiceCommunicator(service, info.communicator);
            }

            throw ex;
        }
    }

    private synchronized void
    stopAll()
    {
        //
        // First wait for any active startService/stopService calls to complete.
        //
        while(_pendingStatusChanges)
        {
            try
            {
                wait();
            }
            catch(java.lang.InterruptedException ex)
            {
            }
        }

        //
        // For each service, we call stop on the service and flush its database environment to
        // the disk. Services are stopped in the reverse order of the order they were started.
        //
        java.util.List<String> stoppedServices = new java.util.ArrayList<String>();
        java.util.ListIterator<ServiceInfo> p = _services.listIterator(_services.size());
        while(p.hasPrevious())
        {
            ServiceInfo info = p.previous();
            if(info.status == StatusStarted)
            {
                try
                {
                    info.service.stop();
                    info.status = StatusStopped;
                    stoppedServices.add(info.name);
                }
                catch(Throwable e)
                {
                    java.io.StringWriter sw = new java.io.StringWriter();
                    java.io.PrintWriter pw = new java.io.PrintWriter(sw);
                    e.printStackTrace(pw);
                    pw.flush();
                    _logger.warning("ServiceManager: exception while stopping service " + info.name + ":\n" +
                                    sw.toString());
                }
            }

            try
            {
                _communicator.removeAdminFacet("IceBox.Service." + info.name + ".Properties");
            }
            catch(Ice.LocalException e)
            {
                // Ignored
            }

            if(info.communicator != null)
            {
                destroyServiceCommunicator(info.name, info.communicator);
            }
        }

        if(_sharedCommunicator != null)
        {
            try
            {
                _sharedCommunicator.destroy();
            }
            catch(java.lang.Exception e)
            {
                java.io.StringWriter sw = new java.io.StringWriter();
                java.io.PrintWriter pw = new java.io.PrintWriter(sw);
                e.printStackTrace(pw);
                pw.flush();
                _logger.warning("ServiceManager: exception while destroying shared communicator:\n" + sw.toString());
            }
            _sharedCommunicator = null;
        }

        _services.clear();
        servicesStopped(stoppedServices, _observers);
    }

    private void
    servicesStarted(java.util.List<String> services, java.util.Set<ServiceObserverPrx> observers)
    {
        if(services.size() > 0)
        {
            String[] servicesArray = services.toArray(new String[0]);

            for(final ServiceObserverPrx observer: observers)
            {
                observer.begin_servicesStarted(servicesArray, _observerCompletedCB);
            }
        }
    }

    private void
    servicesStopped(java.util.List<String> services, java.util.Set<ServiceObserverPrx> observers)
    {
        if(services.size() > 0)
        {
            String[] servicesArray = services.toArray(new String[0]);

            for(final ServiceObserverPrx observer: observers)
            {
                observer.begin_servicesStopped(servicesArray, _observerCompletedCB);
            }
        }
    }

    private void
    observerRemoved(ServiceObserverPrx observer, RuntimeException ex)
    {
        if(_traceServiceObserver >= 1)
        {
            //
            // CommunicatorDestroyedException may occur during shutdown. The observer notification has
            // been sent, but the communicator was destroyed before the reply was received. We do not
            // log a message for this exception.
            //
            if(!(ex instanceof Ice.CommunicatorDestroyedException))
            {
                _logger.trace("IceBox.ServiceObserver",
                              "Removed service observer " + _communicator.proxyToString(observer)
                              + "\nafter catching " + ex.toString());
            }
        }
    }

    public final static int StatusStopping = 0;
    public final static int StatusStopped = 1;
    public final static int StatusStarting = 2;
    public final static int StatusStarted = 3;

    static class ServiceInfo implements Cloneable
    {
        public Object clone()
        {
            Object o = null;
            try
            {
                o = super.clone();
            }
            catch(CloneNotSupportedException ex)
            {
            }
            return o;
        }

        public String name;
        public Service service;
        public Ice.Communicator communicator = null;
        public int status;
        public String[] args;
    }

    static class StartServiceInfo
    {
        StartServiceInfo(String service, String value, String[] serverArgs)
        {
            name = service;

            //
            // We support the following formats:
            //
            // <class-name> [args]
            // <jar-file>:<class-name> [args]
            // <class-dir>:<class-name> [args]
            // "<path with spaces>":<class-name> [args]
            // "<path with spaces>:<class-name>" [args]
            //

            try
            {
                args = IceUtilInternal.Options.split(value);
            }
            catch(IceUtilInternal.Options.BadQuote ex)
            {
                throw new FailureException("ServiceManager: invalid arguments for service `" + name + "':\n" +
                                           ex.getMessage());
            }

            assert(args.length > 0);

            final String entryPoint = args[0];

            final boolean isWindows = System.getProperty("os.name").startsWith("Windows");
            absolutePath = false;

            //
            // Find first ':' that isn't part of the file path.
            //
            int pos = entryPoint.indexOf(':');
            if(isWindows)
            {
                final String driveLetters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
                if(pos == 1 && entryPoint.length() > 2 && driveLetters.indexOf(entryPoint.charAt(0)) != -1 &&
                   (entryPoint.charAt(2) == '\\' || entryPoint.charAt(2) == '/'))
                {
                    absolutePath = true;
                    pos = entryPoint.indexOf(':', pos + 1);
                }
                if(!absolutePath)
                {
                    absolutePath = entryPoint.startsWith("\\\\");
                }
            }
            else
            {
                absolutePath = entryPoint.startsWith("/");
            }

            if((pos == -1 && absolutePath) || (pos != -1 && entryPoint.length() <= pos + 1))
            {
                //
                // Class name is missing.
                //
                throw new FailureException("ServiceManager: invalid entry point for service `" + name + "':\n" +
                                           entryPoint);
            }

            //
            // Extract the JAR file or subdirectory, if any.
            //
            classDir = null; // Path name of JAR file or subdirectory.

            if(pos == -1)
            {
                className = entryPoint;
            }
            else
            {
                classDir = entryPoint.substring(0, pos).trim();
                className = entryPoint.substring(pos + 1).trim();
            }

            //
            // Shift the arguments.
            //
            String[] tmp = new String[args.length - 1];
            System.arraycopy(args, 1, tmp, 0, args.length - 1);
            args = tmp;

            if(serverArgs.length > 0)
            {
                java.util.List<String> l = new java.util.ArrayList<String>(java.util.Arrays.asList(args));
                for(String arg : serverArgs)
                {
                    if(arg.startsWith("--" + service + "."))
                    {
                        l.add(arg);
                    }
                }
                args = l.toArray(args);
            }
        }

        String name;
        String[] args;
        String className;
        String classDir;
        boolean absolutePath;
    }

    private Ice.Properties
    createServiceProperties(String service)
    {
        Ice.Properties properties;
        Ice.Properties communicatorProperties = _communicator.getProperties();
        if(communicatorProperties.getPropertyAsInt("IceBox.InheritProperties") > 0)
        {
            properties = communicatorProperties._clone();
            properties.setProperty("Ice.Admin.Endpoints", ""); // Inherit all except Ice.Admin.Endpoints!
        }
        else
        {
            properties = Ice.Util.createProperties();
        }

        String programName = communicatorProperties.getProperty("Ice.ProgramName");
        if(programName.length() == 0)
        {
            properties.setProperty("Ice.ProgramName", service);
        }
        else
        {
            properties.setProperty("Ice.ProgramName", programName + "-" + service);
        }
        return properties;
    }

    private void
    destroyServiceCommunicator(String service, Ice.Communicator communicator)
    {
        try
        {
            communicator.shutdown();
            communicator.waitForShutdown();
        }
        catch(Ice.CommunicatorDestroyedException e)
        {
            //
            // Ignore, the service might have already destroyed
            // the communicator for its own reasons.
            //
        }
        catch(java.lang.Exception e)
        {
            java.io.StringWriter sw = new java.io.StringWriter();
            java.io.PrintWriter pw = new java.io.PrintWriter(sw);
            e.printStackTrace(pw);
            pw.flush();
            _logger.warning("ServiceManager: exception in shutting down communicator for service "
                            + service + "\n" + sw.toString());
        }

        try
        {
            communicator.destroy();
        }
        catch(java.lang.Exception e)
        {
            java.io.StringWriter sw = new java.io.StringWriter();
            java.io.PrintWriter pw = new java.io.PrintWriter(sw);
            e.printStackTrace(pw);
            pw.flush();
            _logger.warning("ServiceManager: exception in destroying communicator for service "
                            + service + "\n" + sw.toString());
        }
    }

    private Ice.Communicator _communicator;
    private Ice.Communicator _sharedCommunicator;
    private Ice.Logger _logger;
    private String[] _argv; // Filtered server argument vector
    private java.util.List<ServiceInfo> _services = new java.util.LinkedList<ServiceInfo>();
    private boolean _pendingStatusChanges = false;
    private Ice.Callback _observerCompletedCB;
    private java.util.HashSet<ServiceObserverPrx> _observers = new java.util.HashSet<ServiceObserverPrx>();
    private int _traceServiceObserver = 0;
    private java.util.Map<String, ClassLoader> _classLoaders;
}
