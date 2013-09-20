<?
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

$NS = function_exists("Ice\\initialize");
require_once ($NS ? 'Ice_ns.php' : 'Ice.php');
require_once 'Test.php';

function test($b)
{
    if(!$b)
    {
        $bt = debug_backtrace();
        die("\ntest failed in ".$bt[0]["file"]." line ".$bt[0]["line"]."\n");
    }
}

function allTests($communicator)
{
    echo "testing stringToProxy... ";
    flush();
    $ref = "d:default -p 12010";
    $db = $communicator->stringToProxy($ref);
    test($db != null);
    echo "ok\n";

    echo "testing checked cast... ";
    flush();
    $d = $db->ice_checkedCast("::Test::D");
    test($d != null);
    test($d == $db);
    test($db->ice_checkedCast("::Test::D", "bogus") == null);
    echo "ok\n";

    echo "testing non-facets A, B, C, and D... ";
    flush();
    test($d->callA() == "A");
    test($d->callB() == "B");
    test($d->callC() == "C");
    test($d->callD() == "D");
    echo "ok\n";

    echo "testing facets A, B, C, and D... ";
    flush();
    $df = $d->ice_checkedCast("::Test::D", "facetABCD");
    test($df != null);
    test($df->callA() == "A");
    test($df->callB() == "B");
    test($df->callC() == "C");
    test($df->callD() == "D");
    echo "ok\n";

    echo "testing facets E and F... ";
    flush();
    $ff = $d->ice_checkedCast("::Test::F", "facetEF");
    test($ff != null);
    test($ff->callE() == "E");
    test($ff->callF() == "F");
    echo "ok\n";

    echo "testing facet G... ";
    flush();
    $gf = $ff->ice_checkedCast("::Test::G", "facetGH");
    test($gf != null);
    test($gf->callG() == "G");
    echo "ok\n";

    echo "testing whether casting preserves the facet... ";
    flush();
    $hf = $gf->ice_checkedCast("::Test::H");
    test($hf != null);
    test($hf->callG() == "G");
    test($hf->callH() == "H");
    echo "ok\n";

    return $gf;
}

$communicator = Ice_initialize($argv);
$g = allTests($communicator);
$g->shutdown();
$communicator->destroy();
exit();
?>
