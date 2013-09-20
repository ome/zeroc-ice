// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
package test.Ice.background;

import test.Ice.background.PluginFactory.PluginI;
import test.Ice.background.Test.BackgroundPrx;

public class Client extends test.Util.Application
{
    public int
    run(String[] args)
    {
        Configuration configuration = new Configuration();
        PluginI plugin = (PluginI)communicator().getPluginManager().getPlugin("Test");
        plugin.setConfiguration(configuration);
        communicator().getPluginManager().initializePlugins();

        BackgroundPrx background = AllTests.allTests(configuration, communicator(), getWriter());
        background.shutdown();
        return 0;
    }
    
    protected Ice.InitializationData getInitData(Ice.StringSeqHolder argsH)
    {
        Ice.InitializationData initData = new Ice.InitializationData();
        initData.properties = Ice.Util.createProperties(argsH);

        // For this test, we want to disable retries.
        //
        initData.properties.setProperty("Ice.RetryIntervals", "-1");

        //
        // This test kills connections, so we don't want warnings.
        //
        initData.properties.setProperty("Ice.Warn.Connections", "0");

        initData.properties.setProperty("Ice.MessageSizeMax", "50000");

        //
        // Setup the test transport plug-in.
        //
        initData.properties.setProperty("Ice.Plugin.Test", "test.Ice.background.PluginFactory");
        String defaultProtocol = initData.properties.getPropertyWithDefault("Ice.Default.Protocol", "tcp");
        initData.properties.setProperty("Ice.Default.Protocol", "test-" + defaultProtocol);
        
        initData.properties.setProperty("Ice.Package.Test", "test.Ice.background");
        
        // Don't initialize the plugin until I've set the configuration.
        initData.properties.setProperty("Ice.InitPlugins", "0");

        return initData;
    }

    public static void
    main(String[] args)
    {
        Client app = new Client();
        int result = app.main("Client", args);
        System.gc();
        System.exit(result);
    }
}
