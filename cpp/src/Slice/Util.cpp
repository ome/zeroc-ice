// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Slice/Util.h>
#include <IceUtil/Unicode.h>
#include <IceUtil/FileUtil.h>
#include <IceUtil/StringUtil.h>
#include <climits>

#include <unistd.h> // For readlink()

using namespace std;
using namespace Slice;

namespace
{

string
normalizePath(const string& path)
{
    string result = path;

    replace(result.begin(), result.end(), '\\', '/');

    string::size_type startReplace = 0;
#ifdef _WIN32
    //
    // For UNC paths we need to ensure they are in the format that is
    // returned by MCPP. IE. "//MACHINE/PATH"
    //
    if(result.find("//") == 0)
    {
        startReplace = 2;
    }
#endif
    string::size_type pos;
    while((pos = result.find("//", startReplace)) != string::npos)
    {
        result.replace(pos, 2, "/");
    }
    pos = 0;
    while((pos = result.find("/./", pos)) != string::npos)
    {
        result.erase(pos, 2);
    }
    pos = 0;
    while((pos = result.find("/..", pos)) != string::npos)
    {
        string::size_type last = result.find_last_of("/", pos - 1);
        if(last != string::npos && result.substr(last, 4) != "/../")
        {
            result.erase(last, pos - last + 3);
            pos = last;
        }
        else
        {
            ++pos;
        }
    }

    if(result.size() > 1) // Remove trailing "/" or "/."
    {
        if(result[result.size() - 1] == '/')
        {
            result.erase(result.size() - 1);
        }
        else if(result[result.size() - 2] == '/' && result[result.size() - 1] == '.')
        {
            result.erase(result.size() - (result.size() == 2 ? 1 : 2));
        }
    }
    return result;
}

}

string
Slice::fullPath(const string& path)
{
    string result = path;
    if(!IceUtilInternal::isAbsolutePath(result))
    {
        string cwd;
        if(IceUtilInternal::getcwd(cwd) == 0)
        {
            result = string(cwd) + '/' + result;
        }
    }

    result = normalizePath(result);

#ifdef _WIN32
    return result;
#else

    string::size_type beg = 0;
    string::size_type next;
    do
    {
        string subpath;
        next = result.find('/', beg + 1);
        if(next == string::npos)
        {
            subpath = result;
        }
        else
        {
            subpath = result.substr(0, next);
        }

        char buf[PATH_MAX + 1];
        int len = static_cast<int>(readlink(subpath.c_str(), buf, sizeof(buf)));
        if(len > 0)
        {
            buf[len] = '\0';
            string linkpath = buf;
            if(!IceUtilInternal::isAbsolutePath(linkpath)) // Path relative to the location of the link
            {
                string::size_type pos = subpath.rfind('/');
                assert(pos != string::npos);
                linkpath = subpath.substr(0, pos + 1) + linkpath;
            }
            result = normalizePath(linkpath) + (next != string::npos ? result.substr(next) : string());
            beg = 0;
            next = 0;
        }
        else
        {
            beg = next;
        }
    }
    while(next != string::npos);
    return result;
#endif
}

string
Slice::changeInclude(const string& orig, const vector<string>& includePaths)
{
    //
    // MCPP does not follow symlinks included files so we only
    // call fullPath on the base directory and not the file itself.
    //
    string file = orig;
    string::size_type pos;
    if((pos = orig.rfind('/')) != string::npos)
    {
        string base = orig.substr(0, pos);
        file = fullPath(base) + orig.substr(pos);
    }

    //
    // Compare each include path against the included file and select
    // the path that produces the shortest relative filename.
    //
    string result = file;
    for(vector<string>::const_iterator p = includePaths.begin(); p != includePaths.end(); ++p)
    {
        if(file.compare(0, p->length(), *p) == 0)
        {
            string s = file.substr(p->length() + 1); // + 1 for the '/'
            if(s.size() < result.size())
            {
                result = s;
            }
        }
    }

    if(result == file)
    {
        //
        // Don't return a full path if we couldn't reduce the given path, instead
        // return the normalized given path.
        //
        result = normalizePath(orig);
    }

    if((pos = result.rfind('.')) != string::npos)
    {
        result.erase(pos);
    }

    return result;
}

namespace
{

ostream* errorStream = &cerr;

}

void
Slice::setErrorStream(ostream& stream)
{
    errorStream = &stream;
}

ostream&
Slice::getErrorStream()
{
    return *errorStream;
}

void
Slice::emitError(const string& file, int line, const string& message)
{
    if(!file.empty())
    {
        *errorStream << file;
        if(line != -1)
        {
            *errorStream << ':' << line;
        }
        *errorStream << ": ";
    }
    *errorStream << message << endl;
}

void
Slice::emitWarning(const string& file, int line, const string& message)
{
    if(!file.empty())
    {
        *errorStream << file;
        if(line != -1)
        {
            *errorStream << ':' << line;
        }
        *errorStream << ": ";
    }
    *errorStream << "warning: " << message << endl;
}

void
Slice::emitError(const string& file, const std::string& line, const string& message)
{
    if(!file.empty())
    {
        *errorStream << file;
        if(!line.empty())
        {
            *errorStream << ':' << line;
        }
        *errorStream << ": ";
    }
    *errorStream << message << endl;
}

void
Slice::emitWarning(const string& file, const std::string& line, const string& message)
{
    if(!file.empty())
    {
        *errorStream << file;
        if(!line.empty())
        {
            *errorStream << ':' << line;
        }
        *errorStream << ": ";
    }
    *errorStream << "warning: " << message << endl;
}

void
Slice::emitRaw(const char* message)
{
    *errorStream << message << flush;
}

vector<string>
Slice::filterMcppWarnings(const string& message)
{
    static const char* messages[] =
    {
        "Converted [CR+LF] to [LF]",
        "no newline, supplemented newline",
        0
    };

    static const string warningPrefix = "warning:";
    static const string fromPrefix = "from";
    static const string separators = "\n\t ";

    vector<string> in;
    string::size_type start = 0;
    string::size_type end;
    while((end = message.find('\n', start)) != string::npos)
    {
        in.push_back(message.substr(start, end - start));
        start = end + 1;
    }
    vector<string> out;
    bool skipped;
    for(vector<string>::const_iterator i = in.begin(); i != in.end(); i++)
    {
        skipped = false;

        if(i->find(warningPrefix) != string::npos)
        {
            for(int j = 0; messages[j] != 0; ++j)
            {
                if(i->find(messages[j]) != string::npos)
                {
                    // This line should be skipped it contains the unwanted mcpp warning
                    // next line should also be skipped it contains the slice line that
                    // produces the skipped warning
                    i++;
                    skipped = true;
                    //
                    // Check if next lines are still the same warning
                    //
                    i++;
                    while(i != in.end())
                    {
                        string token = *i;
                        string::size_type index = token.find_first_not_of(separators);
                        if(index != string::npos)
                        {
                            token = token.substr(index);
                        }
                        if(token.find(fromPrefix) != 0)
                        {
                            //
                            // First line not of this warning
                            //
                            i--;
                            break;
                        }
                        else
                        {
                            i++;
                        }
                    }
                    break;
                }
            }
            if(i == in.end())
            {
                break;
            }
        }
        if(!skipped)
        {
            out.push_back(*i + "\n");
        }
    }
    return out;
}

void
Slice::printGeneratedHeader(IceUtilInternal::Output& out, const string& path, const string& comment)
{
    //
    // Get only the file name part of the given path.
    //
    string file = path;
    size_t pos = file.find_last_of("/\\");
    if(string::npos != pos)
    {
        file = file.substr(pos + 1);
    }

    out << comment << " <auto-generated>\n";
    out << comment << "\n";
    out << comment << " Generated from file `" << file << "'" << "\n";
    out << comment << "\n";
    out << comment << " Warning: do not edit this file." << "\n";
    out << comment << "\n";
    out << comment << " </auto-generated>\n";
    out << comment << "\n";
}
