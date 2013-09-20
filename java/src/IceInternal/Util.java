// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceInternal;

public final class Util
{
    public static Instance
    getInstance(Ice.Communicator communicator)
    {
        Ice.CommunicatorI p = (Ice.CommunicatorI)communicator;
        return p.getInstance();
    }

    public static ProtocolPluginFacade
    getProtocolPluginFacade(Ice.Communicator communicator)
    {
        return new ProtocolPluginFacadeI(communicator);
    }

    //
    // Given a path name, first try to open it as a class path resource (the path is
    // treated as absolute). If that fails, fall back to the file system. Returns null
    // if the file does not exist and raises IOException if an error occurs.
    //
    public static java.io.InputStream
    openResource(ClassLoader cl, String path)
        throws java.io.IOException
    {
        //
        // Calling getResourceAsStream on the class loader means all paths are absolute,
        // whereas calling it on the class means all paths are relative to the class
        // unless the path has a leading forward slash. We call it on the class loader.
        //
        // getResourceAsStream returns null if the resource can't be found.
        //
        java.io.InputStream stream = null;
        try
        {
            stream = cl.getResourceAsStream(path);
        }
        catch(IllegalArgumentException ex)
        {
            //
            // With JDK-7 this can happen if the result url (base url + path) produces a 
            // malformed url for an URLClassLoader. For example the code in following
            // comment will produce this exception under Windows.
            //
            // URLClassLoader cl = new URLClassLoader(new URL[] {new URL("http://localhost:8080/")});
            // java.io.InputStream in = IceInternal.Util.openResource(cl, "c:\\foo.txt");
            //
        }
        if(stream == null)
        {
            try
            {
                java.io.File f = new java.io.File(path);
                if(f.exists())
                {
                    stream = new java.io.FileInputStream(f);
                }
            }
            catch(java.lang.SecurityException ex)
            {
                // Ignore - a security manager may forbid access to the local file system.
            }
        }

        return stream;
    }

    public static Class<?>
    findClass(String className, ClassLoader cl)
        throws LinkageError
    {
        //
        // Try to load the class using the given class loader (if any). If that fails (or
        // none is provided), we try to load the class a few more ways before giving up.
        //
        // Calling Class.forName() doesn't always work. For example, if Ice.jar is installed
        // as an extension (in $JAVA_HOME/jre/lib/ext), calling Class.forName(name) uses the
        // extension class loader, which will not look in CLASSPATH for the target class.
        //

        Class<?> c = null;

        if(cl != null)
        {
            c = loadClass(className, cl);
        }

        //
        // Try using the current thread's class loader.
        //
        if(c == null)
        {
            try
            {
                cl = Thread.currentThread().getContextClassLoader();
                if(cl != null)
                {
                    c = loadClass(className, cl);
                }
            }
            catch(SecurityException ex)
            {
            }
        }

        //
        // Try using Class.forName().
        //
        try
        {
            if(c == null)
            {
                c = Class.forName(className);
            }
        }
        catch(ClassNotFoundException ex)
        {
            // Ignore
        }

        //
        // Fall back to the system class loader (which knows about CLASSPATH).
        //
        if(c == null)
        {
            try
            {
                cl = ClassLoader.getSystemClassLoader();
                if(cl != null)
                {
                    c = loadClass(className, cl);
                }
            }
            catch(SecurityException ex)
            {
            }
        }

        return c;
    }

    private static Class<?>
    loadClass(String className, ClassLoader cl)
    {
        if(cl != null)
        {
            try
            {
                return cl.loadClass(className);
            }
            catch(ClassNotFoundException ex)
            {
                // Ignore
            }
        }

        return null;
    }

    public static int
    getThreadPriorityProperty(Ice.Properties properties, String prefix)
    {
        String pri = properties.getProperty(prefix + ".ThreadPriority");
        if(pri.equals("MIN_PRIORITY") || pri.equals("java.lang.Thread.MIN_PRIORITY"))
        {
            return java.lang.Thread.MIN_PRIORITY;
        }
        else if(pri.equals("NORM_PRIORITY") || pri.equals("java.lang.Thread.NORM_PRIORITY"))
        {
            return java.lang.Thread.NORM_PRIORITY;
        }
        else if(pri.equals("MAX_PRIORITY") || pri.equals("java.lang.Thread.MAX_PRIORITY"))
        {
            return java.lang.Thread.MAX_PRIORITY;
        }

        try
        {
            return Integer.parseInt(pri);
        }
        catch(NumberFormatException ex)
        {
        }
        return java.lang.Thread.NORM_PRIORITY;
    }

    //
    // Return true if the given thread is the android main thread, also know as the GUI thread.
    //
    public static boolean
    isAndroidMainThread(Thread thread)
    {
        if(!System.getProperty("java.vm.name").startsWith("Dalvik"))
        {
            return false;
        }

        if(_androidMainThread == null)
        {
            try
            {
                Class<?> c = Util.findClass("android.os.Looper", null);
                java.lang.reflect.Method getMainLooper = c.getDeclaredMethod("getMainLooper", (Class<?>[])null);
                java.lang.reflect.Method getThread = c.getDeclaredMethod("getThread", (Class<?>[])null);

                Object looper = getMainLooper.invoke(null);
                _androidMainThread = (Thread)getThread.invoke(looper);
            }
            catch(java.lang.reflect.InvocationTargetException ex)
            {
                assert false;
            }
            catch(java.lang.NoSuchMethodException ex)
            {
                assert false;
            }
            catch(IllegalAccessException ex)
            {
                assert false;
            }
        }

        return thread != null && _androidMainThread == thread;
    }

    private static Thread _androidMainThread;
}
