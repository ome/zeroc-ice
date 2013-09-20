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

function foo()
{
    $NS = function_exists("Ice\\initialize");
    require_once ($NS ? 'Ice_ns.php' : 'Ice.php');
    require_once 'IceGrid.php';
}

echo "testing generated code in a non-global scope... ";
flush();

foo();

echo "ok\n";

?>
