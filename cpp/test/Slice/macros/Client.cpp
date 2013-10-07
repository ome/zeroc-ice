// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <TestCommon.h>
#include <Test.h>

using namespace Test;
using namespace std;

int
main(int argc, char* argv[])
{
    int status = EXIT_SUCCESS;
    try
    {
        cout << "testing Slice predefined macros... " << flush;
        DefaultPtr d = new Default();
        test(d->x == 10);
        test(d->y == 10);

        NoDefaultPtr nd = new NoDefault();
        test(nd->x != 10);
        test(nd->y != 10);

        CppOnlyPtr c = new CppOnly();
        test(c->lang == "cpp");
        test(c->version == ICE_INT_VERSION);
        cout << "ok" << endl;
    }
    catch(const Ice::Exception& ex)
    {
        cerr << ex << endl;
        status = EXIT_FAILURE;
    }
    return status;
}
