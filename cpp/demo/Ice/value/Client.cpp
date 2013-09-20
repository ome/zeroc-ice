// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <Value.h>
#include <ValueI.h>
#include <ObjectFactory.h>

using namespace std;
using namespace Demo;

class ValueClient : public Ice::Application
{
public:

    ValueClient();
    virtual int run(int, char*[]);
};

int
main(int argc, char* argv[])
{
    ValueClient app;
    return app.main(argc, argv, "config.client");
}

ValueClient::ValueClient() :
    //
    // Since this is an interactive demo we don't want any signal
    // handling.
    //
    Ice::Application(Ice::NoSignalHandling)
{
}

int
ValueClient::run(int argc, char* argv[])
{
    if(argc > 1)
    {
        cerr << appName() << ": too many arguments" << endl;
        return EXIT_FAILURE;
    }

    InitialPrx initial = InitialPrx::checkedCast(communicator()->propertyToProxy("Initial.Proxy"));
    if(!initial)
    {
        cerr << argv[0] << ": invalid object reference" << endl;
        return EXIT_FAILURE;
    }

    char c[2];

    cout << '\n'
         << "Let's first transfer a simple object, for a class without\n"
         << "operations, and print its contents. No factory is required\n"
         << "for this.\n"
         << "[press enter]\n";
    cin.getline(c, 2);

    SimplePtr simple = initial->getSimple();
    cout << "==> " << simple->message << endl;

    cout << '\n'
         << "Yes, this worked. Now let's try to transfer an object for a class\n"
         << "with operations as type ::Demo::Printer, without installing a factory first.\n"
         << "This should give us a `no factory' exception.\n"
         << "[press enter]\n";
    cin.getline(c, 2);

    PrinterPtr printer;
    PrinterPrx printerProxy;
    try
    {
        initial->getPrinter(printer, printerProxy);
        cerr << argv[0] << "Did not get the expected NoObjectFactoryException!" << endl;
        exit(EXIT_FAILURE);
    }
    catch(const Ice::NoObjectFactoryException& ex)
    {
        cout << "==> " << ex << endl;
    }

    cout << '\n'
         << "Yep, that's what we expected. Now let's try again, but with\n"
         << "installing an appropriate factory first. If successful, we print\n"
         << "the object's content.\n"
         << "[press enter]\n";
    cin.getline(c, 2);

    Ice::ObjectFactoryPtr factory = new ObjectFactory;
    communicator()->addObjectFactory(factory, Demo::Printer::ice_staticId());

    initial->getPrinter(printer, printerProxy);
    cout << "==> " << printer->message << endl;

    cout << '\n'
         << "Cool, it worked! Let's try calling the printBackwards() method\n"
         << "on the object we just received locally.\n"
         << "[press enter]\n";
    cin.getline(c, 2);

    cout << "==> ";
    printer->printBackwards();

    cout << '\n'
         << "Now we call the same method, but on the remote object. Watch the\n"
         << "server's output.\n"
         << "[press enter]\n";
    cin.getline(c, 2);

    printerProxy->printBackwards();

    cout << '\n'
         << "Next, we transfer a derived object from the server as a base\n"
         << "object. Since we haven't yet installed a factory for the derived\n"
         << "class, the derived class (::Demo::DerivedPrinter) is sliced\n"
         << "to its base class (::Demo::Printer).\n"
         << "[press enter]\n";
    cin.getline(c, 2);

    PrinterPtr derivedAsBase;
    derivedAsBase = initial->getDerivedPrinter();
    cout << "==> The type ID of the received object is \"" << derivedAsBase->ice_id() << "\"" << endl;
    assert(derivedAsBase->ice_id() == Demo::Printer::ice_staticId());
    
    cout << '\n'
         << "Now we install a factory for the derived class, and try again.\n"
         << "Because we receive the derived object as a base object, we\n"
         << "we need to do a dynamic_cast<> to get from the base to the derived object.\n"
         << "[press enter]\n";
    cin.getline(c, 2);
    
    communicator()->addObjectFactory(factory, Demo::DerivedPrinter::ice_staticId());
    
    derivedAsBase = initial->getDerivedPrinter();
    DerivedPrinterPtr derived = DerivedPrinterPtr::dynamicCast(derivedAsBase);
    assert(derived);
    cout << "==> dynamic_cast<> to derived object succeded" << endl;
    cout << "==> The type ID of the received object is \"" << derived->ice_id() << "\"" << endl;

    cout << '\n'
         << "Let's print the message contained in the derived object, and\n"
         << "call the operation printUppercase() on the derived object\n"
         << "locally.\n"
         << "[press enter]\n";
    cin.getline(c, 2);

    cout << "==> " << derived->derivedMessage << endl;
    cout << "==> ";
    derived->printUppercase();

    cout << '\n'
    	 << "Now let's make sure that slice is preserved with [\"preserve-slice\"]\n"
	 << "metadata. We create a derived type on the client and pass it to the\n"
	 << "server, which does not have a factory for the derived type. We do a\n"
	 << "dynamic_cast<> to make sure we can still access the derived type when\n"
	 << "it has been returned from the server.\n"
         << "[press enter]\n";
    cin.getline(c, 2);

    ClientPrinterPtr clientp = new ClientPrinterI;
    clientp->message = "a message 4 u";
    communicator()->addObjectFactory(factory, Demo::ClientPrinter::ice_staticId());

    derivedAsBase = initial->updatePrinterMessage(clientp);
    clientp = ClientPrinterPtr::dynamicCast(derivedAsBase);
    assert(clientp);
    cout << "==> " << clientp->message << endl;

    cout << '\n'
         << "Finally, we try the same again, but instead of returning the\n"
         << "derived object, we throw an exception containing the derived\n"
         << "object.\n"
         << "[press enter]\n";
    cin.getline(c, 2);

    try
    {
        initial->throwDerivedPrinter();
        cerr << argv[0] << ": Did not get the expected DerivedPrinterException!" << endl;
        exit(EXIT_FAILURE);
    }
    catch(const DerivedPrinterException& ex)
    {
        derived = ex.derived;
        if(!derived)
        {
            cerr << argv[0] << "Unexpected null pointer for `derived'" << endl;
            exit(EXIT_FAILURE);
        }
    }

    cout << "==> " << derived->derivedMessage << endl;
    cout << "==> ";
    derived->printUppercase();

    cout << '\n'
         << "That's it for this demo. Have fun with Ice!\n";

    initial->shutdown();

    return EXIT_SUCCESS;
}
