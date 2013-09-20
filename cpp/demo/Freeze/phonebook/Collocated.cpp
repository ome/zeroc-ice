// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <ContactFactory.h>
#include <NameIndex.h>
#include <PhoneBookI.h>
#include <Parser.h>

using namespace std;

class PhoneBookCollocated : public Ice::Application
{
public:
    
    PhoneBookCollocated(const string&);
    virtual int run(int argc, char* argv[]);

private:

    const string _envName;
};

int
main(int argc, char* argv[])
{
    PhoneBookCollocated app("db");
    return app.main(argc, argv, "config.collocated");
}

PhoneBookCollocated::PhoneBookCollocated(const string& envName) :
    //
    // Since this is an interactive demo we don't want any signal
    // handling.
    //
    Ice::Application(Ice::NoSignalHandling),
    _envName(envName)
{
}

int
PhoneBookCollocated::run(int argc, char* argv[])
{
    Ice::PropertiesPtr properties = communicator()->getProperties();

    //
    // Create and install a factory for contacts.
    //
    ContactFactoryPtr contactFactory = new ContactFactory();
    communicator()->addObjectFactory(contactFactory, Demo::Contact::ice_staticId());

    //
    // Create the name index.
    //
    NameIndexPtr index = new NameIndex("name");
    vector<Freeze::IndexPtr> indices;
    indices.push_back(index);

    //
    // Create an object adapter, use the evictor as servant locator.
    //
    Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("PhoneBook");

    //
    // Create an evictor for contacts.
    //
    // When Freeze.Evictor.db.contacts.PopulateEmptyIndices is not 0
    // and the Name index is empty, Freeze will traverse the database
    // to recreate the index during createXXXEvictor(). Therefore the
    // factories for the objects stored in evictor (contacts here)
    // must be registered before the call to createXXXEvictor().
    //
    Freeze::EvictorPtr evictor = Freeze::createBackgroundSaveEvictor(adapter, _envName, "contacts", 0, indices);
    adapter->addServantLocator(evictor, "contact");

    Ice::Int evictorSize = properties->getPropertyAsInt("EvictorSize");
    if(evictorSize > 0)
    {
        evictor->setSize(evictorSize);
    }

    //
    // Completes the initialization of the contact factory. Note that ContactI/
    // ContactFactoryI uses this evictor only when a Contact is destroyed,
    // which cannot happen during createXXXEvictor().
    //
    contactFactory->setEvictor(evictor);
    
    //
    // Create the phonebook, and add it to the Object Adapter.
    //
    PhoneBookIPtr phoneBook = new PhoneBookI(evictor, contactFactory, index);
    adapter->add(phoneBook, communicator()->stringToIdentity("phonebook"));
    
    //
    // Everything ok, let's go.
    //
    int runParser(int, char*[], const Ice::CommunicatorPtr&);
    int status = runParser(argc, argv, communicator());
    adapter->destroy();

    return status;
}
