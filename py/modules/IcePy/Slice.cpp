// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifdef _WIN32
#   include <IceUtil/Config.h>
#endif
#include <Slice.h>
#include <Util.h>
#include <Slice/Preprocessor.h>
#include <Slice/PythonUtil.h>
#include <IceUtil/Options.h>

//
// Python headers needed for PyEval_EvalCode.
//
#include <compile.h>
#include <eval.h>

using namespace std;
using namespace IcePy;
using namespace Slice;
using namespace Slice::Python;

extern "C"
PyObject*
IcePy_loadSlice(PyObject* /*self*/, PyObject* args)
{
    char* cmd;
    PyObject* list = 0;
    if(!PyArg_ParseTuple(args, STRCAST("s|O!"), &cmd, &PyList_Type, &list))
    {
        return 0;
    }

    vector<string> argSeq;
    try
    {
        argSeq = IceUtilInternal::Options::split(cmd);
    }
    catch(const IceUtilInternal::BadOptException& ex)
    {
        PyErr_Format(PyExc_RuntimeError, "error in Slice options: %s", ex.reason.c_str());
        return 0;
    }
    catch(const IceUtilInternal::APIException& ex)
    {
        PyErr_Format(PyExc_RuntimeError, "error in Slice options: %s", ex.reason.c_str());
        return 0;
    }

    if(list)
    {
        if(!listToStringSeq(list, argSeq))
        {
            return 0;
        }
    }

    IceUtilInternal::Options opts;
    opts.addOpt("D", "", IceUtilInternal::Options::NeedArg, "", IceUtilInternal::Options::Repeat);
    opts.addOpt("U", "", IceUtilInternal::Options::NeedArg, "", IceUtilInternal::Options::Repeat);
    opts.addOpt("I", "", IceUtilInternal::Options::NeedArg, "", IceUtilInternal::Options::Repeat);
    opts.addOpt("d", "debug");
    opts.addOpt("", "ice");
    opts.addOpt("", "underscore");
    opts.addOpt("", "checksum");
    opts.addOpt("", "all");

    vector<string> files;
    try
    {
        argSeq.insert(argSeq.begin(), ""); // dummy argv[0]
        files = opts.parse(argSeq);
        if(files.empty())
        {
            PyErr_Format(PyExc_RuntimeError, "no Slice files specified in `%s'", cmd);
            return 0;
        }
    }
    catch(const IceUtilInternal::BadOptException& ex)
    {
        PyErr_Format(PyExc_RuntimeError, "error in Slice options: %s", ex.reason.c_str());
        return 0;
    }
    catch(const IceUtilInternal::APIException& ex)
    {
        PyErr_Format(PyExc_RuntimeError, "error in Slice options: %s", ex.reason.c_str());
        return 0;
    }

    vector<string> cppArgs;
    Ice::StringSeq includePaths;
    bool debug = false;
    bool ice = true; // This must be true so that we can create Ice::Identity when necessary.
    bool underscore = opts.isSet("underscore");
    bool all = false;
    bool checksum = false;
    if(opts.isSet("D"))
    {
        vector<string> optargs = opts.argVec("D");
        for(vector<string>::const_iterator i = optargs.begin(); i != optargs.end(); ++i)
        {
            cppArgs.push_back("-D" + *i);
        }
    }
    if(opts.isSet("U"))
    {
        vector<string> optargs = opts.argVec("U");
        for(vector<string>::const_iterator i = optargs.begin(); i != optargs.end(); ++i)
        {
            cppArgs.push_back("-U" + *i);
        }
    }
    if(opts.isSet("I"))
    {
        includePaths = opts.argVec("I");
        for(vector<string>::const_iterator i = includePaths.begin(); i != includePaths.end(); ++i)
        {
            cppArgs.push_back("-I" + *i);
        }
    }
    debug = opts.isSet("d") || opts.isSet("debug");
    all = opts.isSet("all");
    checksum = opts.isSet("checksum");

    bool ignoreRedefs = false;
    bool keepComments = true;

    for(vector<string>::const_iterator p = files.begin(); p != files.end(); ++p)
    {
        string file = *p;
        Slice::PreprocessorPtr icecpp = Slice::Preprocessor::create("icecpp", file, cppArgs);
        FILE* cppHandle = icecpp->preprocess(keepComments, "-D__SLICE2PY__");

        if(cppHandle == 0)
        {
            PyErr_Format(PyExc_RuntimeError, "Slice preprocessing failed for `%s'", cmd);
            return 0;
        }

        UnitPtr u = Slice::Unit::createUnit(ignoreRedefs, all, ice, underscore);
        int parseStatus = u->parse(file, cppHandle, debug);

        if(!icecpp->close() || parseStatus == EXIT_FAILURE)
        {
            PyErr_Format(PyExc_RuntimeError, "Slice parsing failed for `%s'", cmd);
            u->destroy();
            return 0;
        }

        //
        // Generate the Python code into a string stream.
        //
        ostringstream codeStream;
        IceUtilInternal::Output out(codeStream);
        out.setUseTab(false);
        generate(u, all, checksum, includePaths, out);
        u->destroy();

        string code = codeStream.str();

        //
        // We need to invoke Ice.updateModules() so that all of the types we've just generated
        // are made "public".
        //
        code += "\nIce.updateModules()\n";

        PyObjectHandle src = Py_CompileString(const_cast<char*>(code.c_str()), const_cast<char*>(file.c_str()),
                                              Py_file_input);
        if(!src.get())
        {
            return 0;
        }

        PyObjectHandle globals = PyDict_New();
        if(!globals.get())
        {
            return 0;
        }
        PyDict_SetItemString(globals.get(), "__builtins__", PyEval_GetBuiltins());

#if PY_VERSION_HEX >= 0x03000000
        PyObjectHandle val = PyEval_EvalCode(src.get(), globals.get(), 0);
#else
        PyObjectHandle val = PyEval_EvalCode(reinterpret_cast<PyCodeObject*>(src.get()), globals.get(), 0);
#endif
        if(!val.get())
        {
            return 0;
        }
    }

    Py_INCREF(Py_None);
    return Py_None;
}
