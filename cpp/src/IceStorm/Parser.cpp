// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/DisableWarnings.h>
#include <Ice/Ice.h>
#include <IceStorm/Parser.h>
#include <IceStorm/IceStormInternal.h>
#include <algorithm>

#ifdef HAVE_READLINE
#   include <readline/readline.h>
#   include <readline/history.h>
#endif

extern FILE* yyin;
extern int yydebug;

using namespace std;
using namespace Ice;
using namespace IceStorm;

namespace IceStorm
{

Parser* parser;

}

namespace
{

class UnknownManagerException : public Exception
{
public:
    
    UnknownManagerException(const string& name, const char* file, int line) :
        Exception(file, line),
        name(name)
    {
    }

    virtual
    ~UnknownManagerException() throw()
    {
    }
    virtual string
    ice_name() const
    {
        return "UnknownManagerException";
    }

    virtual Exception*
    ice_clone() const
    {
        return new UnknownManagerException(*this);
    }
    
    virtual void
    ice_throw() const
    {
        throw *this;
    }

    const string name;
};

}

ParserPtr
Parser::createParser(const CommunicatorPtr& communicator, const TopicManagerPrx& admin,
                     const map<Ice::Identity, TopicManagerPrx>& managers)
{
    return new Parser(communicator, admin, managers);
}

void
Parser::usage()
{
    cout <<
        "help                     Print this message.\n"
        "exit, quit               Exit this program.\n"
        "create TOPICS            Add TOPICS.\n"
        "destroy TOPICS           Remove TOPICS.\n"
        "link FROM TO [COST]      Link FROM to TO with the optional given COST.\n"
        "unlink FROM TO           Unlink TO from FROM.\n"
        "links [INSTANCE-NAME]    Display all links for the topics in the current topic\n"
        "                         manager, or in the given INSTANCE-NAME.\n"
        "topics [INSTANCE-NAME]   Display the names of all topics in the current topic\n"
        "                         manager, or in the given INSTANCE-NAME.\n"
        "current [INSTANCE-NAME]  Display the current topic manager, or change it to\n"
        "                         INSTANCE-NAME.\n"
        "replica [INSTANCE-NAME]  Display replication information for the given INSTANCE-NAME.\n"
        ;
}

void
Parser::create(const list<string>& args)
{
    if(args.empty())
    {
        error("`create' requires at least one argument (type `help' for more info)");
        return;
    }

    for(list<string>::const_iterator i = args.begin(); i != args.end() ; ++i)
    {
        try
        {
            string topicName;
            TopicManagerPrx manager = findManagerById(*i, topicName);
            manager->create(topicName);
        }
        catch(const Ice::Exception& ex)
        {
            exception(ex, args.size() > 1); // Print a warning if we're creating multiple topics, an error otherwise.
        }
    }
}

void
Parser::destroy(const list<string>& args)
{
    if(args.empty())
    {
        error("`destroy' requires at least one argument (type `help' for more info)");
        return;
    }

    for(list<string>::const_iterator i = args.begin(); i != args.end() ; ++i)
    {
        try
        {
            findTopic(*i)->destroy();
        }
        catch(const Ice::Exception& ex)
        {
            exception(ex, args.size() > 1); // Print a warning if we're destroying multiple topics, an error otherwise.
        }
    }
}

void
Parser::link(const list<string>& args)
{
    if(args.size() != 2 && args.size() != 3)
    {
        error("`link' requires two or three arguments (type `help' for more info)");
        return;
    }

    try
    {    
        list<string>::const_iterator p = args.begin(); 

        TopicPrx fromTopic = findTopic(*p++);
        TopicPrx toTopic = findTopic(*p++);
        Ice::Int cost = p != args.end() ? atoi(p->c_str()) : 0;

        fromTopic->link(toTopic, cost);
    }
    catch(const Exception& ex)
    {
        exception(ex);
    }
}

void
Parser::unlink(const list<string>& args)
{
    if(args.size() != 2)
    {
        error("`unlink' requires exactly two arguments (type `help' for more info)");
        return;
    }

    try
    {   
        list<string>::const_iterator p = args.begin();

        TopicPrx fromTopic = findTopic(*p++);
        TopicPrx toTopic = findTopic(*p++);

        fromTopic->unlink(toTopic);
    }
    catch(const Exception& ex)
    {
        exception(ex);
    }
}

void
Parser::links(const list<string>& args)
{
    if(args.size() > 1)
    {
        error("`links' requires at most one argument (type `help' for more info)");
        return;
    }

    try
    {
        TopicManagerPrx manager;
        if(args.size() == 0)
        {
            manager = _defaultManager;
        }
        else
        {
            manager = findManagerByCategory(args.front());
        }

        TopicDict d = manager->retrieveAll();
        for(TopicDict::iterator i = d.begin(); i != d.end(); ++i)
        {
            LinkInfoSeq links = i->second->getLinkInfoSeq();
            for(LinkInfoSeq::const_iterator p = links.begin(); p != links.end(); ++p)
            {
                cout << i->first << " to " << (*p).name << " with cost " << (*p).cost << endl;
            }
        }
    }
    catch(const Exception& ex)
    {
        exception(ex);
    }
}

void
Parser::topics(const list<string>& args)
{
    if(args.size() > 1)
    {
        error("`topics' requires at most one argument (type `help' for more info)");
        return;
    }

    try
    {
        TopicManagerPrx manager;
        if(args.size() == 0)
        {
            manager = _defaultManager;
        }
        else
        {
            manager = findManagerByCategory(args.front());
        }

        TopicDict d = manager->retrieveAll();
        for(TopicDict::iterator i = d.begin(); i != d.end(); ++i)
        {
            cout << i->first << endl;
        }
    }
    catch(const Exception& ex)
    {
        exception(ex);
    }
}

void
Parser::replica(const list<string>& args)
{
    if(args.size() > 1)
    {
        error("`replica' requires at most one argument (type `help' for more info)");
        return;
    }

    try
    {
        TopicManagerPrx m;
        if(args.size() == 0)
        {
            m = _defaultManager;
        }
        else
        {
            m = findManagerByCategory(args.front());
        }
        TopicManagerInternalPrx manager = TopicManagerInternalPrx::uncheckedCast(m);
        IceStormElection::NodePrx node = manager->getReplicaNode();
        if(!node)
        {
            error("This topic is not replicated");
        }
        IceStormElection::NodeInfoSeq nodes = node->nodes();
        cout << "replica count: " << nodes.size() << endl;
        for(IceStormElection::NodeInfoSeq::const_iterator p = nodes.begin(); p != nodes.end(); ++p)
        {
            try
            {
                IceStormElection::QueryInfo info = p->n->query();
                cout << p->id << ": id:         " << info.id << endl;
                cout << p->id << ": coord:      " << info.coord << endl;
                cout << p->id << ": group name: " << info.group << endl;
                cout << p->id << ": state:      ";
                switch(info.state)
                {
                case IceStormElection::NodeStateInactive:
                    cout << "inactive";
                    break;
                case IceStormElection::NodeStateElection:
                    cout << "election";
                    break;
                case IceStormElection::NodeStateReorganization:
                    cout << "reorganization";
                    break;
                case IceStormElection::NodeStateNormal:
                    cout << "normal";
                    break;
                default:
                    cout << "unknown";
                }
                cout << endl;
                cout << p->id << ": group:      ";
                for(IceStormElection::GroupInfoSeq::const_iterator q = info.up.begin(); q != info.up.end(); ++q)
                {
                    if(q != info.up.begin())
                    {
                        cout << ",";
                    }
                    cout << q->id;
                }
                cout << endl;
                cout << p->id << ": max:        " << info.max << endl;
            }
            catch(const Exception& ex)
            {
                cout << p->id << ": " << ex.ice_name() << endl;
            }
        }
    }
    catch(const Exception& ex)
    {
        exception(ex);
    }
}

void
Parser::current(const list<string>& args)
{
    if(args.empty())
    {
        cout << _communicator->identityToString(_defaultManager->ice_getIdentity()) << endl;
        return;
    }
    else if(args.size() > 1)
    {
        error("`current' requires at most one argument (type `help' for more info)");
        return;
    }

    try
    {
        TopicManagerPrx manager = findManagerByCategory(args.front());
        manager->ice_ping();
        _defaultManager = manager;
    }
    catch(const Exception& ex)
    {
        exception(ex);
    }
}

void
Parser::showBanner()
{
    cout << "Ice " << ICE_STRING_VERSION << "  Copyright (c) 2003-2013 ZeroC, Inc." << endl;
}

void
Parser::getInput(char* buf, int& result, int maxSize)
{
    if(!_commands.empty())
    {
        if(_commands == ";")
        {
            result = 0;
        }
        else
        {
            result = min(maxSize, static_cast<int>(_commands.length()));
            strncpy(buf, _commands.c_str(), result);
            _commands.erase(0, result);
            if(_commands.empty())
            {
                _commands = ";";
            }
        }
    }
    else
    {
#ifdef HAVE_READLINE

        const char* prompt = parser->getPrompt();
        char* line = readline(const_cast<char*>(prompt));
        if(!line)
        {
            result = 0;
        }
        else
        {
            if(*line)
            {
                add_history(line);
            }

            result = strlen(line) + 1;
            if(result > maxSize)
            {
                free(line);
                error("input line too long");
                result = 0;
            }
            else
            {
                strcpy(buf, line);
                strcat(buf, "\n");
                free(line);
            }
        }

#else

        cout << parser->getPrompt() << flush;

        string line;
        while(true)
        {
            char c = static_cast<char>(getc(yyin));
            if(c == EOF)
            {
                if(line.size())
                {
                    line += '\n';
                }
                break;
            }

            line += c;

            if(c == '\n')
            {
                break;
            }
        }
        
        result = (int) line.length();
        if(result > maxSize)
        {
            error("input line too long");
            buf[0] = EOF;
            result = 1;
        }
        else
        {
            strcpy(buf, line.c_str());
        }

#endif
    }
}

void
Parser::continueLine()
{
    _continue = true;
}

const char*
Parser::getPrompt()
{
    assert(_commands.empty());

    if(_continue)
    {
        _continue = false;
        return "(cont) ";
    }
    else
    {
        return ">>> ";
    }
}

void
Parser::error(const char* s)
{
    cerr << "error: " << s << endl;
    _errors++;
}

void
Parser::error(const string& s)
{
    error(s.c_str());
}

void
Parser::warning(const char* s)
{
    cerr << "warning: " << s << endl;
}

void
Parser::warning(const string& s)
{
    warning(s.c_str());
}

void
Parser::invalidCommand(const string& s)
{
    cerr << s << endl;
}

int
Parser::parse(FILE* file, bool debug)
{
    yydebug = debug ? 1 : 0;

    assert(!parser);
    parser = this;

    _errors = 0;
    _commands.empty();
    yyin = file;
    assert(yyin);

    _continue = false;

    int status = yyparse();
    if(_errors)
    {
        status = EXIT_FAILURE;
    }

    parser = 0;
    return status;
}

int
Parser::parse(const std::string& commands, bool debug)
{
    yydebug = debug ? 1 : 0;

    assert(!parser);
    parser = this;

    _errors = 0;
    _commands = commands;
    assert(!_commands.empty());
    yyin = 0;

    _continue = false;

    int status = yyparse();
    if(_errors)
    {
        status = EXIT_FAILURE;
    }

    parser = 0;
    return status;
}

TopicManagerPrx
Parser::findManagerById(const string& full, string& arg) const
{
    Ice::Identity id = _communicator->stringToIdentity(full);
    arg = id.name;
    if(id.category.empty())
    {
        return _defaultManager;
    }
    id.name = "TopicManager";
    map<Ice::Identity, TopicManagerPrx>::const_iterator p = _managers.find(id);
    if(p == _managers.end())
    {
        throw UnknownManagerException(id.category, __FILE__, __LINE__);
    }
    return p->second;
}

TopicManagerPrx
Parser::findManagerByCategory(const string& full) const
{
    Ice::Identity id;
    id.category = full;
    id.name = "TopicManager";
    map<Ice::Identity, TopicManagerPrx>::const_iterator p = _managers.find(id);
    if(p == _managers.end())
    {
        throw UnknownManagerException(id.category, __FILE__, __LINE__);
    }
    return p->second;
}

TopicPrx
Parser::findTopic(const string& full) const
{
    string topicName;
    TopicManagerPrx manager = findManagerById(full, topicName);
    return manager->retrieve(topicName);
}

Parser::Parser(const CommunicatorPtr& communicator, const TopicManagerPrx& admin,
               const map<Ice::Identity, TopicManagerPrx>& managers) :
    _communicator(communicator),
    _defaultManager(admin),
    _managers(managers)
{
}

void
Parser::exception(const Ice::Exception& ex, bool warn)
{
    ostringstream os;
    try
    {
        ex.ice_throw();
    }
    catch(const LinkExists& ex)
    {
        os << "link `" << ex.name << "' already exists";
    }
    catch(const NoSuchLink& ex)
    {
        os << "couldn't find link `" << ex.name << "'";
    }
    catch(const TopicExists& ex)
    {
        os << "topic `" << ex.name << "' exists";
    }
    catch(const NoSuchTopic& ex)
    {
        os << "couldn't find topic `" << ex.name << "'";
    }
    catch(const UnknownManagerException& ex)
    {
        os << "couldn't find IceStorm service `" << ex.name << "'";
    }
    catch(const IdentityParseException& ex)
    {
        os << "invalid identity `" << ex.str << "'";
    }
    catch(const Ice::LocalException& ex)
    {
        os << "couldn't reach IceStorm service:\n" << ex;
    }
    catch(const Ice::Exception& ex)
    {
        os << ex;
    }

    if(warn)
    {
        warning(os.str());
    }
    else
    {
        error(os.str());
    }
}
