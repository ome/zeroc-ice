<?php
// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

error_reporting(E_ALL | E_STRICT);

if(!extension_loaded("ice"))
{
    echo "\nerror: Ice extension is not loaded.\n\n";
    exit(1);
}

function test($b)
{
    if(!$b)
    {
        $bt = debug_backtrace();
        die("\ntest failed in ".$bt[0]["file"]." line ".$bt[0]["line"]."\n");
    }
}

$NS = function_exists("Ice\\initialize");
require_once ($NS ? 'Ice_ns.php' : 'Ice.php');

//
// Load the Demo profile.
//


$communicator = null;

if($NS)
{
    $initData = eval("return new Ice\\InitializationData;");
    $initData->properties = eval("return Ice\\getProperties();");
    $communicator = eval("return Ice\\initialize(\$initData);");
}
else
{
    $initData = new Ice_InitializationData;
    $initData->properties = Ice_getProperties();
    $communicator = Ice_initialize($initData);
}

test($communicator != null);

$properties = null;
if($NS)
{
    $properties = eval("return Ice\\getProperties(\"Test\");");
}
else
{
    $properties = Ice_getProperties("Test");
}

test($properties != null);

test($properties->getPropertyAsInt("Ice.Trace.Protocol") == 1);
test($properties->getPropertyAsInt("Ice.Trace.Network") == 1);
test($properties->getPropertyAsInt("Ice.Warn.Connections") == 1);
test($properties->getProperty("Hello.Proxy") == "hello:tcp -h localhost -p 10000");

?>
