// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/Options.h>
#include <IceUtil/StringUtil.h>
#include <Ice/Application.h>
#include <IcePatch2/Util.h>
#include <IcePatch2/ClientUtil.h>

#ifdef _WIN32
#   include <conio.h>
#else
#   include <fcntl.h>
#   include <termios.h>
#endif

using namespace std;
using namespace Ice;
using namespace IcePatch2;

class TextPatcherFeedback : public PatcherFeedback
{
public:

    TextPatcherFeedback() :
        _pressAnyKeyMessage(false)
    {
#ifndef _WIN32
        tcgetattr(0, &_savedTerm);
        _savedFlags = fcntl(0, F_GETFL);
        _block = true;
#endif
    }

    virtual ~TextPatcherFeedback()
    {
#ifndef _WIN32
        tcsetattr(0, TCSANOW, &_savedTerm);
        fcntl(0, F_SETFL, _savedFlags);
#endif
    }

    virtual bool
    noFileSummary(const string& reason)
    {
        cout << "Cannot load file summary:\n" << reason << endl;
        string answer;
        do
        {
            cout << "Do a thorough patch? (yes/no)" << endl;
            cin >> answer;
            answer = IceUtilInternal::toLower(answer);
            if(answer == "no")
            {
                return false;
            }
        }
        while(answer != "yes");
        return true;
    }

    virtual bool
    checksumStart()
    {
        if(!_pressAnyKeyMessage)
        {
            cout << "[Press any key to abort]" << endl;
            _pressAnyKeyMessage = true;
        }

        return !keyPressed();
    }

    virtual bool
    checksumProgress(const string& path)
    {
        cout << "Calculating checksum for " << getBasename(path) << endl;
        return !keyPressed();
    }

    virtual bool
    checksumEnd()
    {
        return !keyPressed();
    }

    virtual bool
    fileListStart()
    {
        if(!_pressAnyKeyMessage)
        {
            cout << "[Press any key to abort]" << endl;
            _pressAnyKeyMessage = true;
        }

        _lastProgress = "0%";
        cout << "Getting list of files to patch: " << _lastProgress << flush;
        return !keyPressed();
    }

    virtual bool
    fileListProgress(Int percent)
    {
        for(unsigned int i = 0; i < _lastProgress.size(); ++i)
        {
            cout << '\b';
        }
        ostringstream s;
        s << percent << '%';
        _lastProgress = s.str();
        cout << _lastProgress << flush;
        return !keyPressed();
    }

    virtual bool
    fileListEnd()
    {
        cout << endl;
        return !keyPressed();
    }

    virtual bool
    patchStart(const string& path, Long size, Long totalProgress, Long totalSize)
    {
        if(!_pressAnyKeyMessage)
        {
            cout << "[Press any key to abort]" << endl;
            _pressAnyKeyMessage = true;
        }

        ostringstream s;
        s << "0/" << size << " (" << totalProgress << '/' << totalSize << ')';
        _lastProgress = s.str();
        cout << getBasename(path) << ' ' << _lastProgress << flush;
        return !keyPressed();
    }

    virtual bool
    patchProgress(Long progress, Long size, Long totalProgress, Long totalSize)
    {
        for(unsigned int i = 0; i < _lastProgress.size(); ++i)
        {
            cout << '\b';
        }
        ostringstream s;
        s << progress << '/' << size << " (" << totalProgress << '/' << totalSize << ')';
        _lastProgress = s.str();
        cout << _lastProgress << flush;
        return !keyPressed();
    }

    virtual bool
    patchEnd()
    {
        cout << endl;
        return !keyPressed();
    }

private:

#ifdef _WIN32

    bool
    keyPressed()
    {
        bool pressed = false;
        while(_kbhit())
        {
            pressed = true;
            _getch();
        }
        return pressed;
    }

#else

    bool
    keyPressed()
    {
        if(_block)
        {
            termios term;
            memcpy(&term, &_savedTerm, sizeof(termios));
            term.c_lflag &= ~(ECHO | ICANON);
            term.c_cc[VTIME] = 0;
            term.c_cc[VMIN] = 1;
            tcsetattr(0, TCSANOW, &term);
            
            int flags = _savedFlags;
            flags |= O_NONBLOCK;
            fcntl(0, F_SETFL, flags);

            _block = false;
        }

        bool pressed = false;
        char c;
        while(read(0, &c, 1) > 0)
        {
            pressed = true;
        }
        return pressed;
    }

    termios _savedTerm;
    int _savedFlags;
    bool _block;

#endif

    string _lastProgress;
    bool _pressAnyKeyMessage;
};

class Client : public Application
{
public:

    virtual int run(int, char*[]);

private:

    void usage(const std::string&);
};

int
Client::run(int argc, char* argv[])
{
    PropertiesPtr properties = communicator()->getProperties();

    IceUtilInternal::Options opts;
    opts.addOpt("h", "help");
    opts.addOpt("v", "version");
    opts.addOpt("t", "thorough");
    
    vector<string> args;
    try
    {
        args = opts.parse(argc, (const char**)argv);
    }
    catch(const IceUtilInternal::BadOptException& e)
    {
        cerr << e.reason << endl;
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    if(opts.isSet("help"))
    {
        usage(argv[0]);
        return EXIT_SUCCESS;
    }
    if(opts.isSet("version"))
    {
        cout << ICE_STRING_VERSION << endl;
        return EXIT_SUCCESS;
    }
    if(opts.isSet("thorough"))
    {
        properties->setProperty("IcePatch2Client.Thorough", "1");
    }

    if(args.size() > 1)
    {
        cerr << argv[0] << ": too many arguments" << endl;
        usage(argv[0]);
        return EXIT_FAILURE;
    }
    if(args.size() == 1)
    {
        properties->setProperty("IcePatch2Client.Directory", simplify(args[0]));
    }

    bool aborted = false;

    try
    {
        PatcherFeedbackPtr feedback = new TextPatcherFeedback;
        PatcherPtr patcher = new Patcher(communicator(), feedback);

        aborted = !patcher->prepare();

        if(!aborted)
        {
            aborted = !patcher->patch("");
        }

        if(!aborted)
        {
            patcher->finish();
        }
    }
    catch(const string& ex)
    {
        cerr << argv[0] << ": " << ex << endl;
        return EXIT_FAILURE;
    }

    if(aborted)
    {
        cout << "\n[Aborted]" << endl;
        return EXIT_FAILURE;
    }
    else
    {
        return EXIT_SUCCESS;
    }
}

void
Client::usage(const string& appName)
{
    string options =
        "Options:\n"
        "-h, --help           Show this message.\n"
        "-v, --version        Display the Ice version.\n"
        "-t, --thorough       Recalculate all checksums.";

    cerr << "Usage: " << appName << " [options] [DIR]" << endl;
    cerr << options << endl;
}

#ifdef _WIN32

int
wmain(int argc, wchar_t* argv[])

#else

int
main(int argc, char* argv[])

#endif
{
    Client app;
    return app.main(argc, argv);
}
