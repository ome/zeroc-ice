// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package Ice;

//
// The base class for all ImplicitContext implementations
//
public abstract class ImplicitContextI implements ImplicitContext
{
    public static ImplicitContextI create(String kind)
    {
        if(kind.equals("None") || kind.equals(""))
        {
            return null;
        }
        else if(kind.equals("Shared"))
        {
            return new Shared();
        }
        else if(kind.equals("PerThread"))
        {
            return new PerThread();
        }
        else
        {
            throw new Ice.InitializationException(
                "'" + kind + "' is not a valid value for Ice.ImplicitContext");
        }
    }

    abstract public void write(java.util.Map<String, String> prxContext, IceInternal.BasicStream os);
    abstract java.util.Map<String, String> combine(java.util.Map<String, String> prxContext);

    static class Shared extends ImplicitContextI
    {
        public synchronized java.util.Map<String, String> getContext()
        {
            return new java.util.HashMap<String, String>(_context);
        }

        public synchronized void setContext(java.util.Map<String, String> context)
        {
            _context.clear();
            if(context != null && !context.isEmpty())
            {
                _context.putAll(context);
            }
        }

        public synchronized boolean containsKey(String key)
        {
            if(key == null)
            {
                key = "";
            }

            return _context.containsKey(key);
        }

        public synchronized String get(String key)
        {
            if(key == null)
            {
                key = "";
            }

            String val = _context.get(key);
            if(val == null)
            {
                val = "";
            }

            return val;
        }

        public synchronized String put(String key, String value)
        {
            if(key == null)
            {
                key = "";
            }
            if(value == null)
            {
                value = "";
            }

            String oldVal = _context.put(key, value);
            if(oldVal == null)
            {
                oldVal = "";
            }
            return oldVal;
        }

        public synchronized String remove(String key)
        {
            if(key == null)
            {
                key = "";
            }

            String val = _context.remove(key);

            if(val == null)
            {
                val = "";
            }
            return val;
        }

        public void write(java.util.Map<String, String> prxContext, IceInternal.BasicStream os)
        {
            if(prxContext.isEmpty())
            {
                synchronized(this)
                {
                    ContextHelper.write(os, _context);
                }
            }
            else
            {
                java.util.Map<String, String> ctx = null;
                synchronized(this)
                {
                    ctx = _context.isEmpty() ? prxContext : combine(prxContext);
                }
                ContextHelper.write(os, ctx);
            }
        }

        synchronized java.util.Map<String, String> combine(java.util.Map<String, String> prxContext)
        {
            java.util.Map<String, String> combined = new java.util.HashMap<String, String>(_context);
            combined.putAll(prxContext);
            return combined;
        }

        private java.util.Map<String, String> _context = new java.util.HashMap<String, String>();
    }

    static class PerThread extends ImplicitContextI
    {

        public java.util.Map<String, String> getContext()
        {
            //
            // Note that _map is a *synchronized* map
            //
            java.util.Map<String, String> threadContext = _map.get(Thread.currentThread());

            if(threadContext == null)
            {
                threadContext = new java.util.HashMap<String, String>();
            }
            return threadContext;
        }

        public void setContext(java.util.Map<String, String> context)
        {
            if(context == null || context.isEmpty())
            {
                _map.remove(Thread.currentThread());
            }
            else
            {
                java.util.Map<String, String> threadContext = new java.util.HashMap<String, String>(context);
                _map.put(Thread.currentThread(), threadContext);
            }
        }

        public boolean containsKey(String key)
        {
            if(key == null)
            {
                key = "";
            }

            java.util.Map<String, String> threadContext = _map.get(Thread.currentThread());

            if(threadContext == null)
            {
                return false;
            }

            return threadContext.containsKey(key);
        }

        public String get(String key)
        {
            if(key == null)
            {
                key = "";
            }

            java.util.Map<String, String> threadContext = _map.get(Thread.currentThread());

            if(threadContext == null)
            {
                return "";
            }
            String val = threadContext.get(key);
            if(val == null)
            {
                val = "";
            }
            return val;
        }

        public String put(String key, String value)
        {
            if(key == null)
            {
                key = "";
            }
            if(value == null)
            {
                value = "";
            }

            Thread currentThread = Thread.currentThread();
            java.util.Map<String, String> threadContext = _map.get(currentThread);

            if(threadContext == null)
            {
                threadContext = new java.util.HashMap<String, String>();
                _map.put(currentThread, threadContext);
            }

            String oldVal = threadContext.put(key, value);
            if(oldVal == null)
            {
                oldVal = "";
            }
            return oldVal;
        }

        public String remove(String key)
        {
            if(key == null)
            {
                key = "";
            }

            java.util.Map<String, String> threadContext = _map.get(Thread.currentThread());

            if(threadContext == null)
            {
                return null;
            }

            String val = threadContext.remove(key);

            if(val == null)
            {
                val = "";
            }
            return val;
        }

        public void write(java.util.Map<String, String> prxContext, IceInternal.BasicStream os)
        {
            java.util.Map<String, String> threadContext = _map.get(Thread.currentThread());

            if(threadContext == null || threadContext.isEmpty())
            {
                ContextHelper.write(os, prxContext);
            }
            else if(prxContext.isEmpty())
            {
                ContextHelper.write(os, threadContext);
            }
            else
            {
                java.util.Map<String, String> combined = new java.util.HashMap<String, String>(threadContext);
                combined.putAll(prxContext);
                ContextHelper.write(os, combined);
            }
        }

        java.util.Map<String, String> combine(java.util.Map<String, String> prxContext)
        {
            java.util.Map<String, String> threadContext = _map.get(Thread.currentThread());

            java.util.Map<String, String> combined = new java.util.HashMap<String, String>(threadContext);
            combined.putAll(prxContext);
            return combined;
        }

        //
        // Synchronized map Thread -> Context
        //
        private java.util.Map<Thread, java.util.Map<String, String> > _map =
            java.util.Collections.synchronizedMap(new java.util.HashMap<Thread, java.util.Map<String, String> >());
    }
}
