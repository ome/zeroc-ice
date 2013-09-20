#!/usr/bin/env python
# **********************************************************************
#
# Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

import os, sys, getopt

path = [ ".", "..", "../..", "../../..", "../../../.." ]
head = os.path.dirname(sys.argv[0])
if len(head) > 0:
    path = [os.path.join(head, p) for p in path]
path = [os.path.abspath(p) for p in path if os.path.exists(os.path.join(p, "scripts", "TestUtil.py")) ]
if len(path) == 0:
    raise RuntimeError("can't find toplevel directory!")
sys.path.append(os.path.join(path[0], "scripts"))
import TestUtil, IceGridAdmin

#
# Test client/server without on demand activation.
#
IceGridAdmin.iceGridClientServerTest("", "--TestAdapter.Endpoints=default --TestAdapter.AdapterId=TestAdapter")

#
# Test client/server with on demand activation.
#
if TestUtil.mono:
    IceGridAdmin.iceGridTest("simple_mono_server.xml", "--with-deploy")
else:
    IceGridAdmin.iceGridTest("simple_server.xml", "--with-deploy")    
