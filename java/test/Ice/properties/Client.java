// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.properties;

public class Client extends test.Util.Application
{
    public static void
    test(boolean b)
    {
        if(!b)
        {
            throw new RuntimeException();
        }
    }

    class PropertiesClient extends Ice.Application
    {
        public int
        run(String[] args)
        {
            Ice.Properties properties = communicator().getProperties();
            test(properties.getProperty("Ice.Trace.Network").equals("1"));
            test(properties.getProperty("Ice.Trace.Protocol").equals("1"));
            test(properties.getProperty("Config.Path").equals(configPath));
            test(properties.getProperty("Ice.ProgramName").equals("PropertiesClient"));
            test(appName().equals(properties.getProperty("Ice.ProgramName")));
            return 0;
        };
    };

    public int run(String[] args)
    {
        {
            System.out.print("testing load properties from UTF-8 path... ");
            Ice.Properties properties = Ice.Util.createProperties();
            properties.load(configPath);
            test(properties.getProperty("Ice.Trace.Network").equals("1"));
            test(properties.getProperty("Ice.Trace.Protocol").equals("1"));
            test(properties.getProperty("Config.Path").equals(configPath));
            test(properties.getProperty("Ice.ProgramName").equals("PropertiesClient"));
            System.out.println("ok");
            System.out.print("testing load properties from UTF-8 path using Ice::Application... ");
            PropertiesClient c = new PropertiesClient();
            c.main("", args, configPath);
            System.out.println("ok");
        }
        {
            //
            // Try to load multiple config files.
            //
            System.out.print("testing using Ice.Config with multiple config files... ");
            String[] args1 = new String[]{"--Ice.Config=config/config.1, config/config.2, config/config.3"};
            Ice.Properties properties = Ice.Util.createProperties(args1);
            test(properties.getProperty("Config1").equals("Config1"));
            test(properties.getProperty("Config2").equals("Config2"));
            test(properties.getProperty("Config3").equals("Config3"));
            System.out.println("ok");
        }
        return 0;
    }

    public static void main(String[] args)
    {
        Client c = new Client();
        int status = c.main("Client", args);
        System.gc();
        System.exit(status);
    }

    private static String configPath = "./config/\u4E2D\u56FD_client.config";
}
