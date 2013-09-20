// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/DisableWarnings.h>
#include <IceUtil/Options.h>
#include <Ice/Ice.h>
#include <Ice/DynamicLibrary.h>
#include <Ice/SliceChecksums.h>
#include <Ice/Initialize.h>
#include <Ice/Instance.h>
#include <Ice/PropertiesAdminI.h>
#include <Ice/MetricsAdminI.h>
#include <Ice/InstrumentationI.h>
#include <IceBox/ServiceManagerI.h>

using namespace Ice;
using namespace IceBox;
using namespace std;

typedef IceBox::Service* (*SERVICE_FACTORY)(CommunicatorPtr);


namespace
{

struct StartServiceInfo
{
    StartServiceInfo(const std::string& service, const std::string& value, const Ice::StringSeq& serverArgs)
    {
        name = service;

        //
        // Split the entire property value into arguments. An entry point containing spaces
        // must be enclosed in quotes.
        //
        try
        {
            args = IceUtilInternal::Options::split(value);
        }
        catch(const IceUtilInternal::BadOptException& ex)
        {
            FailureException e(__FILE__, __LINE__);
            e.reason = "ServiceManager: invalid arguments for service `" + name + "':\n" + ex.reason;
            throw e;
        }

        assert(!args.empty());

        //
        // Shift the arguments.
        //
        entryPoint = args[0];
        args.erase(args.begin());

        for(Ice::StringSeq::const_iterator p = serverArgs.begin(); p != serverArgs.end(); ++p)
        {
            if(p->find("--" + name + ".") == 0)
            {
                args.push_back(*p);
            }
        }
    }

    string name;
    string entryPoint;
    Ice::StringSeq args;
};

}

IceBox::ServiceManagerI::ServiceManagerI(CommunicatorPtr communicator, int& argc, char* argv[]) :
    _communicator(communicator),
    _pendingStatusChanges(false),
    _traceServiceObserver(0),
    _observerCompletedCB(newCallback(this, &ServiceManagerI::observerCompleted))
{ 
    _logger = _communicator->getLogger();
    _traceServiceObserver = _communicator->getProperties()->getPropertyAsInt("IceBox.Trace.ServiceObserver");

    for(int i = 1; i < argc; i++)
    {
        _argv.push_back(argv[i]);
    }
}

IceBox::ServiceManagerI::~ServiceManagerI()
{
}

SliceChecksumDict
IceBox::ServiceManagerI::getSliceChecksums(const Current&) const
{
    return sliceChecksums();
}

void
IceBox::ServiceManagerI::startService(const string& name, const Current&)
{
    ServiceInfo info;
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);

        //
        // Search would be more efficient if services were contained in
        // a map, but order is required for shutdown.
        //
        vector<ServiceInfo>::iterator p;
        for(p = _services.begin(); p != _services.end(); ++p)
        {
            if(p->name == name)
            {
                if(p->status != Stopped)
                {
                    throw AlreadyStartedException();
                }
                p->status = Starting;
                info = *p;
                break;
            }
        }
        if(p == _services.end())
        {
            throw NoSuchServiceException();
        }
        _pendingStatusChanges = true;
    }

    bool started = false;
    try
    {
        info.service->start(name, info.communicator == 0 ? _sharedCommunicator : info.communicator, info.args);
        started = true;
    }
    catch(const Exception& ex)
    {
        Warning out(_logger);
        out << "ServiceManager: exception in start for service " << info.name << ":\n";
        out << ex;
    }
    catch(...)
    {
        Warning out(_logger);
        out << "ServiceManager: unknown exception in start for service " << info.name;
    }

    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
        for(vector<ServiceInfo>::iterator p = _services.begin(); p != _services.end(); ++p)
        {
            if(p->name == name)
            {
                if(started)
                {
                    p->status = Started;

                    vector<string> services;
                    services.push_back(name);
                    servicesStarted(services, _observers);
                }
                else
                {
                    p->status = Stopped;
                }
                break;
            }
        }
        _pendingStatusChanges = false;
        notifyAll();
    }
}

void
IceBox::ServiceManagerI::stopService(const string& name, const Current&)
{
    ServiceInfo info;
    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);

        //
        // Search would be more efficient if services were contained in
        // a map, but order is required for shutdown.
        //
        vector<ServiceInfo>::iterator p;
        for(p = _services.begin(); p != _services.end(); ++p)
        {
            if(p->name == name)
            {
                if(p->status != Started)
                {
                    throw AlreadyStoppedException();
                }
                p->status = Stopping;
                info = *p;
                break;
            }
        }
        if(p == _services.end())
        {
            throw NoSuchServiceException();
        }
        _pendingStatusChanges = true;
    }

    bool stopped = false;
    try
    {
        info.service->stop();
        stopped = true;
    }
    catch(const Exception& ex)
    {
        Warning out(_logger);
        out << "ServiceManager: exception while stopping service " << info.name << ":\n";
        out << ex;
    }
    catch(...)
    {
        Warning out(_logger);
        out << "ServiceManager: unknown exception while stopping service " << info.name;
    }

    {
        IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
        for(vector<ServiceInfo>::iterator p = _services.begin(); p != _services.end(); ++p)
        {
            if(p->name == name)
            {
                if(stopped)
                {
                    p->status = Stopped;

                    vector<string> services;
                    services.push_back(name);
                    servicesStopped(services, _observers);
                }
                else
                {
                    p->status = Started;
                }
                break;
            }
        }
        _pendingStatusChanges = false;
        notifyAll();
    }
}

void
IceBox::ServiceManagerI::addObserver(const ServiceObserverPrx& observer, const Current&)
{
    //
    // Null observers and duplicate registrations are ignored
    //

    IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);
    if(observer != 0 && _observers.insert(observer).second)
    {
        if(_traceServiceObserver >= 1)
        {
            Trace out(_logger, "IceBox.ServiceObserver");
            out << "Added service observer " << _communicator->proxyToString(observer);
        }

        vector<string> activeServices;
        for(vector<ServiceInfo>::iterator p = _services.begin(); p != _services.end(); ++p)
        {
            const ServiceInfo& info = *p;
            if(info.status == Started)
            {
                activeServices.push_back(info.name);
            }
        }

        if(activeServices.size() > 0)
        {
            observer->begin_servicesStarted(activeServices, _observerCompletedCB);
        }
    }
}

void
IceBox::ServiceManagerI::shutdown(const Current&)
{
    _communicator->shutdown();
}

bool
IceBox::ServiceManagerI::start()
{
    try
    {
        ServiceManagerPtr obj = this;
        PropertiesPtr properties = _communicator->getProperties();

        //
        // Create an object adapter. Services probably should NOT share
        // this object adapter, as the endpoint(s) for this object adapter
        // will most likely need to be firewalled for security reasons.
        //
        ObjectAdapterPtr adapter;
        if(properties->getProperty("IceBox.ServiceManager.Endpoints") != "")
        {
            adapter = _communicator->createObjectAdapter("IceBox.ServiceManager");

            Identity identity;
            identity.category = properties->getPropertyWithDefault("IceBox.InstanceName", "IceBox");
            identity.name = "ServiceManager";
            adapter->add(obj, identity);
        }

        //
        // Parse the property set with the prefix "IceBox.Service.". These
        // properties should have the following format:
        //
        // IceBox.Service.Foo=entry_point [args]
        //
        // We parse the service properties specified in IceBox.LoadOrder
        // first, then the ones from remaining services.
        //
        const string prefix = "IceBox.Service.";
        PropertyDict services = properties->getPropertiesForPrefix(prefix);
        PropertyDict::iterator p;
        StringSeq loadOrder = properties->getPropertyAsList("IceBox.LoadOrder");
        vector<StartServiceInfo> servicesInfo;
        for(StringSeq::const_iterator q = loadOrder.begin(); q != loadOrder.end(); ++q)
        {
            p = services.find(prefix + *q);
            if(p == services.end())
            {
                FailureException ex(__FILE__, __LINE__);
                ex.reason = "ServiceManager: no service definition for `" + *q + "'";
                throw ex;
            }
            servicesInfo.push_back(StartServiceInfo(*q, p->second, _argv));
            services.erase(p);
        }
        for(p = services.begin(); p != services.end(); ++p)
        {
            servicesInfo.push_back(StartServiceInfo(p->first.substr(prefix.size()), p->second, _argv));
        }

        //
        // Check if some services are using the shared communicator in which
        // case we create the shared communicator now with a property set which
        // is the union of all the service properties (services which are using
        // the shared communicator).
        //
        PropertyDict sharedCommunicatorServices = properties->getPropertiesForPrefix("IceBox.UseSharedCommunicator.");
        if(!sharedCommunicatorServices.empty())
        {
            InitializationData initData;
            initData.properties = createServiceProperties("SharedCommunicator");
            for(vector<StartServiceInfo>::iterator q = servicesInfo.begin(); q != servicesInfo.end(); ++q)
            {
                if(properties->getPropertyAsInt("IceBox.UseSharedCommunicator." + q->name) <= 0)
                {
                    continue;
                }

                //
                // Load the service properties using the shared communicator properties as
                // the default properties.
                //
                PropertiesPtr svcProperties = createProperties(q->args, initData.properties);

                //
                // Erase properties from the shared communicator which don't exist in the
                // service properties (which include the shared communicator properties
                // overriden by the service properties).
                //
                PropertyDict allProps = initData.properties->getPropertiesForPrefix("");
                for(PropertyDict::iterator p = allProps.begin(); p != allProps.end(); ++p)
                {
                    if(svcProperties->getProperty(p->first) == "")
                    {
                        initData.properties->setProperty(p->first, "");
                    }
                }

                //
                // Add the service properties to the shared communicator properties.
                //
                PropertyDict props = svcProperties->getPropertiesForPrefix("");
                for(PropertyDict::const_iterator r = props.begin(); r != props.end(); ++r)
                {
                    initData.properties->setProperty(r->first, r->second);
                }

                //
                // Parse <service>.* command line options (the Ice command line options
                // were parsed by the createProperties above)
                //
                q->args = initData.properties->parseCommandLineOptions(q->name, q->args);
            }

            //
            // If Ice metrics are enabled on the IceBox communicator, we also enable them on the 
            // shared communicator.
            // 
            IceInternal::MetricsAdminIPtr metricsAdmin;
            if(IceInternal::CommunicatorObserverIPtr::dynamicCast(_communicator->getObserver()))
            {
                metricsAdmin = new IceInternal::MetricsAdminI(initData.properties, getProcessLogger());
                initData.observer = new IceInternal::CommunicatorObserverI(metricsAdmin);
            }

            _sharedCommunicator = initialize(initData);

            //
            // Ensure the metrics admin plugin uses the same property set as the
            // communicator. This is necessary to correctly deal with runtime 
            // property updates.
            //
            if(metricsAdmin)
            {
                metricsAdmin->setProperties(_sharedCommunicator->getProperties());
            }
        }

        //
        // Start the services.
        //
        for(vector<StartServiceInfo>::const_iterator r = servicesInfo.begin(); r != servicesInfo.end(); ++r)
        {
            start(r->name, r->entryPoint, r->args);
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
        string bundleName = properties->getProperty("IceBox.PrintServicesReady");
        if(!bundleName.empty())
        {
            cout << bundleName << " ready" << endl;
        }

        //
        // Register "this" as a facet to the Admin object, and then create
        // Admin object
        //
        try
        {
            _communicator->addAdminFacet(this, "IceBox.ServiceManager");
            _communicator->getAdmin();
        }
        catch(const ObjectAdapterDeactivatedException&)
        {
            //
            // Expected if the communicator has been shutdown.
            //
        }

        if(adapter)
        {
            try
            {
                adapter->activate();
            }
            catch(const ObjectAdapterDeactivatedException&)
            {
                //
                // Expected if the communicator has been shutdown.
                //
            }
        }
    }
    catch(const FailureException& ex)
    {
        Error out(_logger);
        out << ex.reason;
        stopAll();
        return false;
    }
    catch(const Exception& ex)
    {
        Error out(_logger);
        out << "ServiceManager: " << ex;
        stopAll();
        return false;
    }
    catch(const std::exception& ex)
    {
        Error out(_logger);
        out << "ServiceManager: " << ex.what();
        stopAll();
        return false;
    }
    catch(...)
    {
        Error out(_logger);
        out << "ServiceManager: unknown exception";
        stopAll();
        return false;
    }

    return true;
}

void
IceBox::ServiceManagerI::stop()
{
    stopAll();
}

void
IceBox::ServiceManagerI::start(const string& service, const string& entryPoint, const StringSeq& args)
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);

    //
    // Load the entry point.
    //
    IceInternal::DynamicLibraryPtr library = 
        new IceInternal::DynamicLibrary(IceInternal::getInstance(_communicator)->initializationData().stringConverter);
    IceInternal::DynamicLibrary::symbol_type sym = library->loadEntryPoint(entryPoint, false);
    if(sym == 0)
    {
        string msg = library->getErrorMessage();
        FailureException ex(__FILE__, __LINE__);
        ex.reason = "ServiceManager: unable to load entry point `" + entryPoint + "'";
        if(!msg.empty())
        {
            ex.reason += ": " + msg;
        }
        throw ex;
    }

    ServiceInfo info;
    info.name = service;
    info.status = Stopped;
    info.args = args;

    //
    // If Ice.UseSharedCommunicator.<name> is not defined, create
    // a communicator for the service. The communicator inherits
    // from the shared communicator properties. If it's defined
    // add the service properties to the shared commnunicator
    // property set.
    //
    Ice::CommunicatorPtr communicator;
    IceInternal::MetricsAdminIPtr metricsAdmin;
    if(_communicator->getProperties()->getPropertyAsInt("IceBox.UseSharedCommunicator." + service) > 0)
    {
        assert(_sharedCommunicator);
        communicator = _sharedCommunicator;
        Ice::Instrumentation::CommunicatorObserverPtr o = communicator->getObserver();
        if(o)
        {
            metricsAdmin = IceInternal::CommunicatorObserverIPtr::dynamicCast(o)->getMetricsAdmin();
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
            InitializationData initData;
            initData.properties = createServiceProperties(service);

            if(!info.args.empty())
            {
                //
                // Create the service properties with the given service arguments. This should
                // read the service config file if it's specified with --Ice.Config.
                //
                initData.properties = createProperties(info.args, initData.properties);
                
                //
                // Next, parse the service "<service>.*" command line options (the Ice command
                // line options were parsed by the createProperties above)
                //
                info.args = initData.properties->parseCommandLineOptions(service, info.args);
            }
            
            //
            // Clone the logger to assign a new prefix. If one of the built-in loggers is configured
            // don't set any logger.
            //
            if(initData.properties->getProperty("Ice.LogFile").empty() 
#ifndef _WIN32
               && initData.properties->getPropertyAsInt("Ice.UseSyslog") == 0
#endif
               )
            {
                initData.logger = _logger->cloneWithPrefix(initData.properties->getProperty("Ice.ProgramName"));
            }

            //
            // If Ice metrics are enabled on the IceBox communicator, we also enable them on
            // the service communicator.
            // 
            if(IceInternal::CommunicatorObserverIPtr::dynamicCast(_communicator->getObserver()))
            {
                metricsAdmin = new IceInternal::MetricsAdminI(initData.properties, initData.logger);
                initData.observer = new IceInternal::CommunicatorObserverI(metricsAdmin);
            }

            //
            // Remaining command line options are passed to the communicator. This is
            // necessary for Ice plug-in properties (e.g.: IceSSL).
            //
            info.communicator = initialize(info.args, initData);
            communicator = info.communicator;

            //
            // Ensure the metrics admin plugin uses the same property set as the
            // communicator. This is necessary to correctly deal with runtime 
            // property updates.
            //
            if(metricsAdmin)
            {
                metricsAdmin->setProperties(communicator->getProperties());
            }
        }
        catch(const Exception& ex)
        {
            LoggerOutputBase s;
            s << "ServiceManager: exception while starting service " << service << ":\n";
            s << ex;

            FailureException e(__FILE__, __LINE__);
            e.reason = s.str();
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
        string facetName = "IceBox.Service." + info.name + ".Properties";
        PropertiesAdminIPtr propAdmin = 
            new PropertiesAdminI(facetName, communicator->getProperties(), communicator->getLogger());
        _communicator->addAdminFacet(propAdmin, facetName);

        //
        // If a metrics admin facet is setup for the service, register
        // it with the IceBox communicator.
        //
        if(metricsAdmin)
        {
            _communicator->addAdminFacet(metricsAdmin, "IceBox.Service." + info.name + ".Metrics");

            // Ensure the metrics admin facet is notified of property updates.
            propAdmin->addUpdateCallback(metricsAdmin);
        }

        //
        // Invoke the factory function.
        //
        SERVICE_FACTORY factory = (SERVICE_FACTORY)sym;
        try
        {
            info.service = factory(_communicator);
        }
        catch(const FailureException&)
        {
            throw;
        }
        catch(const Exception& ex)
        {
            LoggerOutputBase s;
            s << "ServiceManager: exception in entry point `" + entryPoint + "' for service " << info.name << ":\n";
            s << ex;
            
            FailureException e(__FILE__, __LINE__);
            e.reason = s.str();
            throw e;
        }
        catch(...)
        {
            ostringstream s;
            s << "ServiceManager: unknown exception in entry point `" + entryPoint + "' for service " << info.name;
            
            FailureException e(__FILE__, __LINE__);
            e.reason = s.str();
            throw e;
        }
            
        //
        // Start the service.
        //
        try
        {
            info.service->start(info.name, communicator, info.args);
            
            //
            // There is no need to notify the observers since the 'start all'
            // (that indirectly calls this function) occurs before the creation of
            // the Server Admin object, and before the activation of the main
            // object adapter (so before any observer can be registered)
            //
        }
        catch(const FailureException&)
        {
            throw;
        }
        catch(const Exception& ex)
        {
            LoggerOutputBase s;
            s << "ServiceManager: exception while starting service " << info.name << ":\n";
            s << ex;

            FailureException e(__FILE__, __LINE__);
            e.reason = s.str();
            throw e;
        }
        catch(...)
        {
            ostringstream s;
            s << "ServiceManager: unknown exception while starting service " << info.name;

            FailureException e(__FILE__, __LINE__);
            e.reason = s.str();
            throw e;
        }

        info.library = library;
        info.status = Started;
        _services.push_back(info);
    }
    catch(const ObjectAdapterDeactivatedException&)
    {
        //
        // Can be raised by addAdminFacet if the service manager communicator has been shut down.
        //
        if(info.communicator)
        {
            destroyServiceCommunicator(info.name, info.communicator);
        }
    }
    catch(const Exception&)
    {
        try
        {
            _communicator->removeAdminFacet("IceBox.Service." + info.name + ".Properties");
        }
        catch(const LocalException&)
        {
            // Ignored
        }

        try
        {
            Ice::ObjectPtr admin = _communicator->removeAdminFacet("IceBox.Service." + info.name + ".Metrics");
            if(admin && communicator != _sharedCommunicator)
            {
                IceInternal::MetricsAdminIPtr::dynamicCast(admin)->destroy();
            }
        }
        catch(const LocalException&)
        {
            // Ignored
        }

        if(info.communicator)
        {
            destroyServiceCommunicator(info.name, info.communicator);
        }

        throw;
    }
}

void
IceBox::ServiceManagerI::stopAll()
{
    IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);

    //
    // First wait for any active startService/stopService calls to complete.
    //
    while(_pendingStatusChanges)
    {
        wait();
    }

    //
    // Services are stopped in the reverse order from which they are started.
    //

    vector<string> stoppedServices;

    //
    // First, for each service, we call stop on the service and flush its database environment to
    // the disk.
    //
    for(vector<ServiceInfo>::reverse_iterator p = _services.rbegin(); p != _services.rend(); ++p)
    {
        ServiceInfo& info = *p;

        if(info.status == Started)
        {
            try
            {
                info.service->stop();
                info.status = Stopped;
                stoppedServices.push_back(info.name);
            }
            catch(const Exception& ex)
            {
                Warning out(_logger);
                out << "ServiceManager: exception while stopping service " << info.name << ":\n";
                out << ex;
            }
            catch(...)
            {
                Warning out(_logger);
                out << "ServiceManager: unknown exception while stopping service " << info.name;
            }
        }
    }

    for(vector<ServiceInfo>::reverse_iterator p = _services.rbegin(); p != _services.rend(); ++p)
    {
        ServiceInfo& info = *p;

        try
        {
            _communicator->removeAdminFacet("IceBox.Service." + info.name + ".Properties");
        }
        catch(const LocalException&)
        {
            // Ignored
        }
        
        try
        {
            Ice::ObjectPtr admin = _communicator->removeAdminFacet("IceBox.Service." + info.name + ".Metrics");
            if(admin && info.communicator != _sharedCommunicator)
            {
                IceInternal::MetricsAdminIPtr::dynamicCast(admin)->destroy();
            }
        }
        catch(const LocalException&)
        {
            // Ignored
        }

        if(info.communicator)
        {
            try
            {
                info.communicator->shutdown();
                info.communicator->waitForShutdown();
            }
            catch(const CommunicatorDestroyedException&)
            {
                //
                // Ignore, the service might have already destroyed
                // the communicator for its own reasons.
                //
            }
            catch(const Exception& ex)
            {
                Warning out(_logger);
                out << "ServiceManager: exception while stopping service " << info.name << ":\n";
                out << ex;
            }
        }

        //
        // Release the service, the service communicator and then the library. The order is important,
        // the service must be released before destroying the communicator so that the communicator
        // leak detector doesn't report potential leaks, and the communicator must be destroyed before
        // the library is released since the library will destroy its global state.
        //
        try
        {
            info.service = 0;
        }
        catch(const Exception& ex)
        {
            Warning out(_logger);
            out << "ServiceManager: exception while stopping service " << info.name << ":\n";
            out << ex;
        }
        catch(...)
        {
            Warning out(_logger);
            out << "ServiceManager: unknown exception while stopping service " << info.name;
        }

        if(info.communicator)
        {
            try
            {
                info.communicator->destroy();
                info.communicator = 0;
            }
            catch(const Exception& ex)
            {
                Warning out(_logger);
                out << "ServiceManager: exception while stopping service " << info.name << ":\n";
                out << ex;
            }
        }

        try
        {
            info.library = 0;
        }
        catch(const Exception& ex)
        {
            Warning out(_logger);
            out << "ServiceManager: exception while stopping service " << info.name << ":\n";
            out << ex;
        }
        catch(...)
        {
            Warning out(_logger);
            out << "ServiceManager: unknown exception while stopping service " << info.name;
        }
    }

    if(_sharedCommunicator)
    {
        Ice::Instrumentation::CommunicatorObserverPtr o = _sharedCommunicator->getObserver();
        if(o)
        {
            IceInternal::CommunicatorObserverIPtr::dynamicCast(o)->getMetricsAdmin()->destroy();
        }

        try
        {
            _sharedCommunicator->destroy();
        }
        catch(const std::exception& ex)
        {
            Warning out(_logger);
            out << "ServiceManager: exception while destroying shared communicator:\n" << ex;
        }
        _sharedCommunicator = 0;
    }

    _services.clear();

    servicesStopped(stoppedServices, _observers);

    _observerCompletedCB = 0; // Break cyclic reference count.
}

void
IceBox::ServiceManagerI::servicesStarted(const vector<string>& services, const set<ServiceObserverPrx>& observers)
{
    if(services.size() > 0)
    {
        for(set<ServiceObserverPrx>::const_iterator p = observers.begin(); p != observers.end(); ++p)
        {
            (*p)->begin_servicesStarted(services, _observerCompletedCB);
        }
    }
}

void
IceBox::ServiceManagerI::servicesStopped(const vector<string>& services, const set<ServiceObserverPrx>& observers)
{
    if(services.size() > 0)
    {
        for(set<ServiceObserverPrx>::const_iterator p = observers.begin(); p != observers.end(); ++p)
        {
            (*p)->begin_servicesStopped(services, _observerCompletedCB);
        }
    }
}

void
IceBox::ServiceManagerI::observerRemoved(const ServiceObserverPrx& observer, const std::exception& ex)
{
    if(_traceServiceObserver >= 1)
    {
        //
        // CommunicatorDestroyedException may occur during shutdown. The observer notification has
        // been sent, but the communicator was destroyed before the reply was received. We do not
        // log a message for this exception.
        //
        if(dynamic_cast<const CommunicatorDestroyedException*>(&ex) == 0)
        {
            Trace out(_logger, "IceBox.ServiceObserver");
            out << "Removed service observer " << _communicator->proxyToString(observer)
                << "\nafter catching " << ex.what();
        }
    }
}

Ice::PropertiesPtr
IceBox::ServiceManagerI::createServiceProperties(const string& service)
{
    PropertiesPtr properties;
    PropertiesPtr communicatorProperties = _communicator->getProperties();
    if(communicatorProperties->getPropertyAsInt("IceBox.InheritProperties") > 0)
    {
        properties = communicatorProperties->clone();
        properties->setProperty("Ice.Admin.Endpoints", ""); // Inherit all except Ice.Admin.Endpoints!
    }
    else
    {
        properties = createProperties();
    }

    string programName = communicatorProperties->getProperty("Ice.ProgramName");
    if(programName.empty())
    {
        properties->setProperty("Ice.ProgramName", service);
    }
    else
    {
        properties->setProperty("Ice.ProgramName", programName + "-" + service);
    }
    return properties;
}

void
ServiceManagerI::observerCompleted(const Ice::AsyncResultPtr& result)
{
     try 
     {
         result->throwLocalException();
     }
     catch(const Ice::LocalException& ex)
     {
        ServiceObserverPrx observer = ServiceObserverPrx::uncheckedCast(result->getProxy());
        IceUtil::Monitor<IceUtil::Mutex>::Lock lock(*this);

        //
        // It's possible to remove several times the same observer, e.g. multiple concurrent
        // requests that fail
        //        
        set<ServiceObserverPrx>::iterator p = _observers.find(observer);
        if(p != _observers.end())
        {
            ServiceObserverPrx observer = *p;
            _observers.erase(p);
            observerRemoved(observer, ex);
        }
     }
}

void
IceBox::ServiceManagerI::destroyServiceCommunicator(const string& service, const CommunicatorPtr& communicator)
{
    try
    {
        communicator->shutdown();
        communicator->waitForShutdown();
    }
    catch(const CommunicatorDestroyedException&)
    {
        //
        // Ignore, the service might have already destroyed
        // the communicator for its own reasons.
        //
    }
    catch(const Exception& ex)
    {
        Warning out(_logger);
        out << "ServiceManager: exception in shutting down communicator for service " << service << ":\n";
        out << ex;
    }

    try
    {
        communicator->destroy();
    }
    catch(const Exception& ex)
    {
        Warning out(_logger);
        out << "ServiceManager: exception in shutting down communicator for service " << service << ":\n";
        out << ex;
    }
}
