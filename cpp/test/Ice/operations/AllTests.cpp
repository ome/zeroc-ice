// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <Ice/Locator.h>
#include <TestCommon.h>
#include <Test.h>

using namespace std;

Test::MyClassPrx
allTests(const Ice::CommunicatorPtr& communicator, bool collocated)
{
    string ref = "test:default -p 12010";
    Ice::ObjectPrx base = communicator->stringToProxy(ref);
    Test::MyClassPrx cl = Test::MyClassPrx::checkedCast(base);
    Test::MyDerivedClassPrx derived = Test::MyDerivedClassPrx::checkedCast(cl);

    cout << "testing twoway operations... " << flush;
    void twoways(const Ice::CommunicatorPtr&, const Test::MyClassPrx&);
    twoways(communicator, cl);
    twoways(communicator, derived);
    derived->opDerived();
    cout << "ok" << endl;

    cout << "testing oneway operations... " << flush;
    void oneways(const Ice::CommunicatorPtr&, const Test::MyClassPrx&);
    oneways(communicator, cl);
    cout << "ok" << endl;

    if(!collocated)
    {
        cout << "testing twoway operations with AMI... " << flush;
        void twowaysAMI(const Ice::CommunicatorPtr&, const Test::MyClassPrx&);
        twowaysAMI(communicator, cl);
        twowaysAMI(communicator, derived);
        cout << "ok" << endl;

        cout << "testing twoway operations with new AMI mapping... " << flush;
        void twowaysNewAMI(const Ice::CommunicatorPtr&, const Test::MyClassPrx&);
        twowaysNewAMI(communicator, cl);
        twowaysNewAMI(communicator, derived);
        cout << "ok" << endl;

        cout << "testing oneway operations with AMI... " << flush;
        void onewaysAMI(const Ice::CommunicatorPtr&, const Test::MyClassPrx&);
        onewaysAMI(communicator, cl);
        cout << "ok" << endl;

        cout << "testing oneway operations with new AMI mapping... " << flush;
        void onewaysNewAMI(const Ice::CommunicatorPtr&, const Test::MyClassPrx&);
        onewaysNewAMI(communicator, cl);
        cout << "ok" << endl;

        cout << "testing batch oneway operations... " << flush;
        void batchOneways(const Test::MyClassPrx&);
        batchOneways(cl);
        batchOneways(derived);
        cout << "ok" << endl;
    }

    return cl;
}
