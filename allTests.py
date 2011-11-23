#!/usr/bin/env python
# **********************************************************************
#
# Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

import os, sys
import getopt

for toplevel in [".", "..", "../..", "../../..", "../../../.."]:
    toplevel = os.path.normpath(toplevel)
    if os.path.exists(os.path.join(toplevel, "config", "TestUtil.py")):
        break
else:
    raise "can't find toplevel directory!"

def isCygwin():

    # The substring on sys.platform is required because some cygwin
    # versions return variations like "cygwin_nt-4.01".
    if sys.platform[:6] == "cygwin":
        return 1
    else:
        return 0

def isWin32():

    if sys.platform == "win32" or isCygwin():
        return 1
    else:
        return 0


def isWin9x():

    if isWin32():
        if os.environ.has_key("OS") and os.environ["OS"] == "Windows_NT":
           return 0
        return 1
    else:
        return 0

def runTests(tests, protocol, host, debug, compress, threadPerConnection, num = 0):

    args = ""
    if protocol:
        args += "--protocol " + protocol + " "
    if host:
        args += "--host " + host + " "
    if debug:
        args += "--debug "
    if compress:
        args += "--compress "
    if threadPerConnection:
        args += "--threadPerConnection "

    if num > 0:
        prefix = "[" + str(num) + "] *** "
    else:
        prefix = "*** "

    #
    # Run each of the tests.
    #
    for i in tests:

        i = os.path.normpath(i)
        dir = os.path.join(toplevel, "test", i)

        print
        print prefix + "running tests in " + dir

        if len(args) > 0:
            print prefix + "options: " + args

        sys.stdout.flush()

        if isWin9x():
            status = os.system("python " + os.path.join(dir, "run.py " + args))
        else:
            status = os.system(os.path.join(dir, "run.py " + args))

        if status:
            print prefix + "test in " + dir + " failed with exit status", status
            sys.exit(status)

#
# List of all basic tests.
#
tests = [ \
    "IceUtil/thread", \
    "IceUtil/unicode", \
    "IceUtil/inputUtil", \
    "IceUtil/uuid", \
    "Slice/errorDetection", \
    "Ice/operations", \
    "Ice/exceptions", \
    "Ice/inheritance", \
    "Ice/facets", \
    "Ice/objects", \
    "Ice/binding", \
    "Ice/faultTolerance", \
    "Ice/location", \
    "Ice/adapterDeactivation", \
    "Ice/slicing/exceptions", \
    "Ice/slicing/objects", \
    "Ice/gc", \
    "Ice/checksum", \
    "Ice/stream", \
    "Ice/hold", \
    "Ice/custom", \
    "Ice/retry", \
    "Ice/timeout", \
    "Ice/servantLocator", \
    "Ice/threads", \
    "IceSSL/configuration", \
    "Freeze/dbmap", \
    "Freeze/complex", \
    "Freeze/evictor", \
    "Freeze/oldevictor", \
    "IceStorm/single", \
    "IceStorm/federation", \
    "IceStorm/federation2", \
    "IceStorm/stress", \
    "FreezeScript/dbmap", \
    "FreezeScript/evictor", \
    "IceGrid/simple", \
    "IceGrid/deployer", \
    "IceGrid/session", \
    "IceGrid/update", \
    "IceGrid/activation", \
    "IceGrid/replicaGroup", \
    "IceGrid/replication", \
    "IceGrid/allocation", \
    "IceGrid/distribution", \
    "Glacier2/router", \
    "Glacier2/attack", \
    "Glacier2/sessionControl", \
    "Glacier2/ssl", \
    "Glacier2/dynamicFiltering", \
    "Glacier2/staticFiltering", \
    ]

#
# These tests are currently disabled on cygwin
#
if isCygwin() == 0:
    tests += [ \
       
      ]

def usage():
    print "usage: " + sys.argv[0] + " --all -l -r <regex> -R <regex> --debug --protocol tcp|ssl --compress --host host --threadPerConnection"
    sys.exit(2)

try:
    opts, args = getopt.getopt(sys.argv[1:], "lr:R:", \
        ["all", "debug", "protocol=", "compress", "host=", "threadPerConnection"])
except getopt.GetoptError:
    usage()

if(args):
    usage()

loop = 0
all = 0
protocol = None
host = None
debug = 0
compress = 0
threadPerConnection = 0
for o, a in opts:
    if o == "-l":
        loop = 1
    if o == "--all":
        all = 1
    if o == "-r" or o == '-R':
        import re
        regexp = re.compile(a)
        if o == '-r':
            def rematch(x): return regexp.search(x)
        else:
            def rematch(x): return not regexp.search(x)
        tests = filter(rematch, tests)
    if o == "--protocol":
        if a not in ( "ssl", "tcp"):
            usage()
        protocol = a
    if o == "--host":
        host = a
    if o == "--debug":
        debug = 1
    if o == "--compress":
        compress = 1
    if o == "--threadPerConnection":
        threadPerConnection = 1

protocols = ["tcp", "ssl"]

if loop:
    num = 1
    while 1:
        if all:
            for protocol in protocols:
                for compress in [0, 1]:
                    for threadPerConnection in [0, 1]:
                        runTests(tests, protocol, host, debug, compress, threadPerConnection, num)
        else:
            runTests(tests, protocol, host, debug, compress, threadPerConnection, num)
        num += 1
else:
    if all:
        for protocol in protocols:
            for compress in [0, 1]:
                for threadPerConnection in [0, 1]:
                    runTests(tests, protocol, host, debug, compress, threadPerConnection)
    else:
        runTests(tests, protocol, host, debug, compress, threadPerConnection)
