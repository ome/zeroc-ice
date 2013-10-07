#!/usr/bin/env python
# -*- coding: utf-8 -*-
# **********************************************************************
#
# Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************


import os, sys, traceback
import Ice

def test(b):
    if not b:
        raise RuntimeError('test assertion failed')
    
class Client(Ice.Application):
    def run(self, args):
        properties = self.communicator().getProperties()
        test(properties.getProperty("Ice.Trace.Network") == "1")
        test(properties.getProperty("Ice.Trace.Protocol") == "1")
        test(properties.getProperty("Config.Path") == "./config/中国_client.config")
        test(properties.getProperty("Ice.ProgramName") == "PropertiesClient")
        test(self.appName() == properties.getProperty("Ice.ProgramName"))


sys.stdout.write("testing load properties from UTF-8 path... ")
sys.stdout.flush()
properties = Ice.createProperties()
properties.load("./config/中国_client.config")
test(properties.getProperty("Ice.Trace.Network") == "1")
test(properties.getProperty("Ice.Trace.Protocol") == "1")
test(properties.getProperty("Config.Path") == "./config/中国_client.config")
test(properties.getProperty("Ice.ProgramName") == "PropertiesClient")
print("ok")
sys.stdout.write("testing load properties from UTF-8 path using Ice::Application... ")
sys.stdout.flush()
c  = Client()
c.main(sys.argv, "./config/中国_client.config")
print("ok")

sys.stdout.write("testing using Ice.Config with multiple config files... ")
sys.stdout.flush()
properties = Ice.createProperties(["--Ice.Config=config/config.1, config/config.2, config/config.3"]);
test(properties.getProperty("Config1") == "Config1");
test(properties.getProperty("Config2") == "Config2");
test(properties.getProperty("Config3") == "Config3");
print("ok")

sys.exit(0)
