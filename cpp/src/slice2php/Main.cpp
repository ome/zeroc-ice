// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceUtil/DisableWarnings.h>
#include <IceUtil/CtrlCHandler.h>
#include <IceUtil/IceUtil.h>
#include <IceUtil/InputUtil.h>
#include <IceUtil/Options.h>
#include <IceUtil/OutputUtil.h>
#include <IceUtil/StringUtil.h>
#include <IceUtil/Mutex.h>
#include <IceUtil/MutexPtrLock.h>
#include <Slice/Checksum.h>
#include <Slice/Preprocessor.h>
#include <Slice/FileTracker.h>
#include <Slice/PHPUtil.h>
#include <Slice/Util.h>
#include <cstring>
#include <climits>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#endif

#ifndef _WIN32
#include <unistd.h>
#endif

using namespace std;
using namespace Slice;
using namespace Slice::PHP;
using namespace IceUtil;
using namespace IceUtilInternal;

//
// CodeVisitor generates the PHP mapping for a translation unit.
//
class CodeVisitor : public ParserVisitor
{
public:

    CodeVisitor(IceUtilInternal::Output&, bool);

    virtual void visitClassDecl(const ClassDeclPtr&);
    virtual bool visitClassDefStart(const ClassDefPtr&);
    virtual bool visitExceptionStart(const ExceptionPtr&);
    virtual bool visitStructStart(const StructPtr&);
    virtual void visitSequence(const SequencePtr&);
    virtual void visitDictionary(const DictionaryPtr&);
    virtual void visitEnum(const EnumPtr&);
    virtual void visitConst(const ConstPtr&);

private:

    void startNamespace(const ContainedPtr&);
    void endNamespace();

    //
    // Return the PHP name for the given Slice type. When using namespaces,
    // this name is a relative (unqualified) name, otherwise this name is the
    // flattened absolute name.
    //
    string getName(const ContainedPtr&, const string& = string());

    //
    // Return the PHP variable for the given object's type.
    //
    string getTypeVar(const ContainedPtr&, const string& = string());

    //
    // Emit the array for a Slice type.
    //
    void writeType(const TypePtr&);

    //
    // Write a default value for a given type.
    //
    void writeDefaultValue(const TypePtr&);

    struct MemberInfo
    {
        string fixedName;
        bool inherited;
        DataMemberPtr dataMember;
    };
    typedef list<MemberInfo> MemberInfoList;

    //
    // Write a member assignment statement for a constructor.
    //
    void writeAssign(const MemberInfo&);

    //
    // Write constant value.
    //
    void writeConstantValue(const TypePtr&, const SyntaxTreeBasePtr&, const string&);

    //
    // Write constructor parameters with default values.
    //
    void writeConstructorParams(const MemberInfoList&);

    //
    // Convert an operation mode into a string.
    //
    string getOperationMode(Slice::Operation::Mode, bool);

    void collectClassMembers(const ClassDefPtr&, MemberInfoList&, bool);
    void collectExceptionMembers(const ExceptionPtr&, MemberInfoList&, bool);

    Output& _out;
    bool _ns; // Using namespaces?
    list<string> _moduleStack; // TODO: Necessary?
    set<string> _classHistory; // TODO: Necessary?
};

//
// CodeVisitor implementation.
//
CodeVisitor::CodeVisitor(Output& out, bool ns) :
    _out(out), _ns(ns)
{
}

void
CodeVisitor::visitClassDecl(const ClassDeclPtr& p)
{
    //
    // Handle forward declarations.
    //
    string scoped = p->scoped();
    string abs = getAbsolute(p, _ns);
    if(_classHistory.count(scoped) == 0)
    {
        startNamespace(p);

        string type = getTypeVar(p);
        _out << sp << nl << "if(!isset(" << type << "))";
        _out << sb;
        _out << nl << type << " = IcePHP_declareClass('" << scoped << "');";
        if(!p->isLocal())
        {
            _out << nl << type << "Prx = IcePHP_declareProxy('" << scoped << "');";
        }
        _out << eb;

        endNamespace();

        _classHistory.insert(scoped); // Avoid redundant declarations.
    }
}

bool
CodeVisitor::visitClassDefStart(const ClassDefPtr& p)
{
    string scoped = p->scoped();
    string name = getName(p);
    string type = getTypeVar(p);
    string abs = getAbsolute(p, _ns);
    string prxName = getName(p, "Prx");
    string prxType = getTypeVar(p, "Prx");
    string prxAbs = getAbsolute(p, _ns, "", "Prx");
    ClassList bases = p->bases();
    ClassDefPtr base;
    OperationList ops = p->operations();
    DataMemberList members = p->dataMembers();
    bool isInterface = p->isInterface();
    bool isAbstract = isInterface || p->allOperations().size() > 0; // Don't use isAbstract() - see bug 3739

    startNamespace(p);

    //
    // Define the class.
    //
    if(isInterface)
    {
        _out << sp << nl << "if(!interface_exists('" << escapeName(abs) << "'))";
        _out << sb;
        _out << nl << "interface " << name;
        if(!bases.empty())
        {
            _out << " extends ";
            for(ClassList::const_iterator q = bases.begin(); q != bases.end(); ++q)
            {
                if(q != bases.begin())
                {
                    _out << ", ";
                }
                _out << getAbsolute(*q, _ns);
            }
        }
        _out << sb;
        for(OperationList::iterator oli = ops.begin(); oli != ops.end(); ++oli)
        {
            _out << nl << "public function " << fixIdent((*oli)->name()) << '(';
            ParamDeclList params = (*oli)->parameters();
            for(ParamDeclList::iterator q = params.begin(); q != params.end(); ++q)
            {
                if(q != params.begin())
                {
                    _out << ", ";
                }
                _out << '$' << fixIdent((*q)->name());
            }
            _out << ");";
        }
        _out << eb;
    }
    else
    {
        _out << sp << nl << "if(!class_exists('" << escapeName(abs) << "'))";
        _out << sb;
        _out << nl;
        if(isAbstract)
        {
            _out << "abstract ";
        }
        _out << "class " << name;
        if(!bases.empty() && !bases.front()->isInterface())
        {
            base = bases.front();
            bases.pop_front();
        }
        if(base)
        {
            _out << " extends " << getAbsolute(base, _ns);
        }
        else
        {
            if(!p->isLocal())
            {
                _out << " extends " << scopedToName("::Ice::ObjectImpl", _ns);
            }
        }
        if(!bases.empty())
        {
            _out << " implements ";
            for(ClassList::const_iterator q = bases.begin(); q != bases.end(); ++q)
            {
                if(q != bases.begin())
                {
                    _out << ", ";
                }
                _out << getAbsolute(*q, _ns);
            }
        }

        _out << sb;

        //
        // __construct
        //
        _out << nl << "public function __construct(";
        MemberInfoList allMembers;
        collectClassMembers(p, allMembers, false);
        writeConstructorParams(allMembers);
        _out << ")";
        _out << sb;
        if(base)
        {
            _out << nl << "parent::__construct(";
            int count = 0;
            for(MemberInfoList::iterator q = allMembers.begin(); q != allMembers.end(); ++q)
            {
                if(q->inherited)
                {
                    if(count)
                    {
                        _out << ", ";
                    }
                    _out << '$' << q->fixedName;
                    ++count;
                }
            }
            _out << ");";
        }
        {
            for(MemberInfoList::iterator q = allMembers.begin(); q != allMembers.end(); ++q)
            {
                if(!q->inherited)
                {
                    writeAssign(*q);
                }
            }
        }
        _out << eb;

        if(!ops.empty())
        {
            _out << sp;
            for(OperationList::iterator oli = ops.begin(); oli != ops.end(); ++oli)
            {
                _out << nl << "abstract public function " << fixIdent((*oli)->name()) << '(';
                ParamDeclList params = (*oli)->parameters();
                for(ParamDeclList::iterator q = params.begin(); q != params.end(); ++q)
                {
                    if(q != params.begin())
                    {
                        _out << ", ";
                    }
                    _out << '$' << fixIdent((*q)->name());
                }
                _out << ");";
            }
        }

        if(!p->isLocal())
        {
            //
            // ice_staticId
            //
            _out << sp << nl << "public static function ice_staticId()";
            _out << sb;
            _out << nl << "return '" << scoped << "';";
            _out << eb;
        }

        //
        // __toString
        //
        _out << sp << nl << "public function __toString()";
        _out << sb;
        _out << nl << "global " << type << ';';
        _out << nl << "return IcePHP_stringify($this, " << type << ");";
        _out << eb;

        if(!members.empty())
        {
            _out << sp;
            bool isProtected = p->hasMetaData("protected");
            for(DataMemberList::iterator q = members.begin(); q != members.end(); ++q)
            {
                _out << nl;
                if(isProtected || (*q)->hasMetaData("protected"))
                {
                    _out << "protected ";
                }
                else
                {
                    _out << "public ";
                }
                _out << "$" << fixIdent((*q)->name()) << ";";
            }
        }

        _out << eb; // End of class.
    }

    //
    // Define the proxy class.
    //
    if(!p->isLocal())
    {
        _out << sp << nl << "class " << prxName << "Helper";
        _out << sb;

        _out << sp << nl << "public static function checkedCast($proxy, $facetOrCtx=null, $ctx=null)";
        _out << sb;
        _out << nl << "return $proxy->ice_checkedCast('" << scoped << "', $facetOrCtx, $ctx);";
        _out << eb;

        _out << sp << nl << "public static function uncheckedCast($proxy, $facet=null)";
        _out << sb;
        _out << nl << "return $proxy->ice_uncheckedCast('" << scoped << "', $facet);";
        _out << eb;

        _out << eb;
    }

    if(_classHistory.count(scoped) == 0 && p->canBeCyclic())
    {
        //
        // Emit a forward declaration for the class in case a data member refers to this type.
        //
        _out << sp << nl << type << " = IcePHP_declareClass('" << scoped << "');";
        if(!p->isLocal())
        {
            _out << nl << prxType << " = IcePHP_declareProxy('" << scoped << "');";
        }
    }

    //
    // Emit the type information.
    //
    const bool preserved = p->hasMetaData("preserve-slice") || p->inheritsMetaData("preserve-slice");
    _out << sp << nl << type << " = IcePHP_defineClass('" << scoped << "', '" << escapeName(abs) << "', "
         << p->compactId() << ", " << (isAbstract ? "true" : "false") << ", " << (preserved ? "true" : "false") << ", ";
    if(!base)
    {
        _out << "$Ice__t_Object";
    }
    else
    {
        _out << getTypeVar(base);
    }
    _out << ", ";
    //
    // Interfaces
    //
    if(!bases.empty())
    {
        _out << "array(";
        for(ClassList::const_iterator q = bases.begin(); q != bases.end(); ++q)
        {
            if(q != bases.begin())
            {
                _out << ", ";
            }
            _out << getTypeVar(*q);
        }
        _out << ')';
    }
    else
    {
        _out << "null";
    }
    _out << ", ";
    //
    // Members
    //
    // Data members are represented as an array:
    //
    //   ('MemberName', MemberType, Optional, Tag)
    //
    // where MemberType is either a primitive type constant (T_INT, etc.) or the id of a constructed type.
    //
    if(!members.empty())
    {
        _out << "array(";
        for(DataMemberList::iterator q = members.begin(); q != members.end(); ++q)
        {
            if(q != members.begin())
            {
                _out << ',';
            }
            _out.inc();
            _out << nl << "array('" << fixIdent((*q)->name()) << "', ";
            writeType((*q)->type());
            _out << ", " << ((*q)->optional() ? "true" : "false") << ", "
                 << ((*q)->optional() ? (*q)->tag() : 0) << ')';
            _out.dec();
        }
        _out << ')';
    }
    else
    {
        _out << "null";
    }
    _out << ");";

    if(!p->isLocal())
    {
        _out << sp << nl << prxType << " = IcePHP_defineProxy(" << type << ");";

        //
        // Define each operation. The arguments to IcePHP_defineOperation are:
        //
        // $ClassType, 'opName', Mode, SendMode, FormatType, (InParams), (OutParams), ReturnParam, (Exceptions)
        //
        // where InParams and OutParams are arrays of type descriptions, and Exceptions
        // is an array of exception type ids.
        //
        if(!ops.empty())
        {
            _out << sp;
            for(OperationList::iterator oli = ops.begin(); oli != ops.end(); ++oli)
            {
                ParamDeclList params = (*oli)->parameters();
                ParamDeclList::iterator t;
                int count;

                _out << nl << "IcePHP_defineOperation(" << type << ", '" << (*oli)->name() << "', "
                     << getOperationMode((*oli)->mode(), _ns) << ", " << getOperationMode((*oli)->sendMode(), _ns)
                     << ", " << static_cast<int>((*oli)->format()) << ", ";
                for(t = params.begin(), count = 0; t != params.end(); ++t)
                {
                    if(!(*t)->isOutParam())
                    {
                        if(count == 0)
                        {
                            _out << "array(";
                        }
                        else if(count > 0)
                        {
                            _out << ", ";
                        }
                        _out << "array(";
                        writeType((*t)->type());
                        _out << ", " << ((*t)->optional() ? "true" : "false") << ", "
                             << ((*t)->optional() ? (*t)->tag() : 0) << ')';
                        ++count;
                    }
                }
                if(count > 0)
                {
                    _out << ')';
                }
                else
                {
                    _out << "null";
                }
                _out << ", ";
                for(t = params.begin(), count = 0; t != params.end(); ++t)
                {
                    if((*t)->isOutParam())
                    {
                        if(count == 0)
                        {
                            _out << "array(";
                        }
                        else if(count > 0)
                        {
                            _out << ", ";
                        }
                        _out << "array(";
                        writeType((*t)->type());
                        _out << ", " << ((*t)->optional() ? "true" : "false") << ", "
                             << ((*t)->optional() ? (*t)->tag() : 0) << ')';
                        ++count;
                    }
                }
                if(count > 0)
                {
                    _out << ')';
                }
                else
                {
                    _out << "null";
                }
                _out << ", ";
                TypePtr returnType = (*oli)->returnType();
                if(returnType)
                {
                    //
                    // The return type has the same format as an in/out parameter:
                    //
                    // Type, Optional?, OptionalTag
                    //
                    _out << "array(";
                    writeType(returnType);
                    _out << ", " << ((*oli)->returnIsOptional() ? "true" : "false") << ", "
                         << ((*oli)->returnIsOptional() ? (*oli)->returnTag() : 0) << ')';
                }
                else
                {
                    _out << "null";
                }
                _out << ", ";
                ExceptionList exceptions = (*oli)->throws();
                if(!exceptions.empty())
                {
                    _out << "array(";
                    for(ExceptionList::iterator u = exceptions.begin(); u != exceptions.end(); ++u)
                    {
                        if(u != exceptions.begin())
                        {
                            _out << ", ";
                        }
                        _out << getTypeVar(*u);
                    }
                    _out << ')';
                }
                else
                {
                    _out << "null";
                }
                _out << ");";
            }
        }
    }

    _out << eb;

    endNamespace();

    if(_classHistory.count(scoped) == 0)
    {
        _classHistory.insert(scoped); // Avoid redundant declarations.
    }

    return false;
}

bool
CodeVisitor::visitExceptionStart(const ExceptionPtr& p)
{
    string scoped = p->scoped();
    string name = getName(p);
    string type = getTypeVar(p);
    string abs = getAbsolute(p, _ns);

    startNamespace(p);

    _out << sp << nl << "if(!class_exists('" << escapeName(abs) << "'))";
    _out << sb;
    _out << nl << "class " << name << " extends ";
    ExceptionPtr base = p->base();
    string baseName;
    if(base)
    {
        baseName = getAbsolute(base, _ns);
        _out << baseName;
    }
    else if(p->isLocal())
    {
        _out << scopedToName("::Ice::LocalException", _ns);
    }
    else
    {
        _out << scopedToName("::Ice::UserException", _ns);
    }
    _out << sb;

    DataMemberList members = p->dataMembers();

    //
    // __construct
    //
    _out << nl << "public function __construct(";
    MemberInfoList allMembers;
    collectExceptionMembers(p, allMembers, false);
    writeConstructorParams(allMembers);
    _out << ")";
    _out << sb;
    if(base)
    {
        _out << nl << "parent::__construct(";
        int count = 0;
        for(MemberInfoList::iterator q = allMembers.begin(); q != allMembers.end(); ++q)
        {
            if(q->inherited)
            {
                if(count)
                {
                    _out << ", ";
                }
                _out << '$' << q->fixedName;
                ++count;
            }
        }
        _out << ");";
    }
    for(MemberInfoList::iterator q = allMembers.begin(); q != allMembers.end(); ++q)
    {
        if(!q->inherited)
        {
            writeAssign(*q);
        }
    }
    _out << eb;

    //
    // ice_name
    //
    _out << sp << nl << "public function ice_name()";
    _out << sb;
    _out << nl << "return '" << scoped.substr(2) << "';";
    _out << eb;

    //
    // __toString
    //
    _out << sp << nl << "public function __toString()";
    _out << sb;
    _out << nl << "global " << type << ';';
    _out << nl << "return IcePHP_stringifyException($this, " << type << ");";
    _out << eb;

    if(!members.empty())
    {
        _out << sp;
        for(DataMemberList::iterator dmli = members.begin(); dmli != members.end(); ++dmli)
        {
            _out << nl << "public $" << fixIdent((*dmli)->name()) << ";";
        }
    }

    _out << eb;

    //
    // Emit the type information.
    //
    const bool preserved = p->hasMetaData("preserve-slice") || p->inheritsMetaData("preserve-slice");
    _out << sp << nl << type << " = IcePHP_defineException('" << scoped << "', '" << escapeName(abs) << "', "
         << (preserved ? "true" : "false") << ", ";
    if(!base)
    {
        _out << "null";
    }
    else
    {
         _out << getTypeVar(base);
    }
    _out << ", ";
    //
    // Data members are represented as an array:
    //
    //   ('MemberName', MemberType, Optional, Tag)
    //
    // where MemberType is either a primitive type constant (T_INT, etc.) or the id of a constructed type.
    //
    if(!members.empty())
    {
        _out << "array(";
        for(DataMemberList::iterator dmli = members.begin(); dmli != members.end(); ++dmli)
        {
            if(dmli != members.begin())
            {
                _out << ',';
            }
            _out.inc();
            _out << nl << "array('" << fixIdent((*dmli)->name()) << "', ";
            writeType((*dmli)->type());
            _out << ", " << ((*dmli)->optional() ? "true" : "false") << ", "
                 << ((*dmli)->optional() ? (*dmli)->tag() : 0) << ')';
            _out.dec();
        }
        _out << ')';
    }
    else
    {
        _out << "null";
    }
    _out << ");";

    _out << eb;

    endNamespace();

    return false;
}

bool
CodeVisitor::visitStructStart(const StructPtr& p)
{
    string scoped = p->scoped();
    string name = getName(p);
    string type = getTypeVar(p);
    string abs = getAbsolute(p, _ns);
    MemberInfoList memberList;

    {
        DataMemberList members = p->dataMembers();
        for(DataMemberList::iterator q = members.begin(); q != members.end(); ++q)
        {
            memberList.push_back(MemberInfo());
            memberList.back().fixedName = fixIdent((*q)->name());
            memberList.back().inherited = false;
            memberList.back().dataMember = *q;
        }
    }

    startNamespace(p);

    _out << sp << nl << "if(!class_exists('" << escapeName(abs) << "'))";
    _out << sb;

    _out << nl << "class " << name;
    _out << sb;
    _out << nl << "public function __construct(";
    writeConstructorParams(memberList);
    _out << ")";
    _out << sb;
    for(MemberInfoList::iterator r = memberList.begin(); r != memberList.end(); ++r)
    {
        writeAssign(*r);
    }
    _out << eb;

    //
    // __toString
    //
    _out << sp << nl << "public function __toString()";
    _out << sb;
    _out << nl << "global " << type << ';';
    _out << nl << "return IcePHP_stringify($this, " << type << ");";
    _out << eb;

    if(!memberList.empty())
    {
        _out << sp;
        for(MemberInfoList::iterator r = memberList.begin(); r != memberList.end(); ++r)
        {
            _out << nl << "public $" << r->fixedName << ';';
        }
    }

    _out << eb;

    //
    // Emit the type information.
    //
    _out << sp << nl << type << " = IcePHP_defineStruct('" << scoped << "', '" << escapeName(abs) << "', array(";
    //
    // Data members are represented as an array:
    //
    //   ('MemberName', MemberType)
    //
    // where MemberType is either a primitive type constant (T_INT, etc.) or the id of a constructed type.
    //
    for(MemberInfoList::iterator r = memberList.begin(); r != memberList.end(); ++r)
    {
        if(r != memberList.begin())
        {
            _out << ", ";
        }
        _out.inc();
        _out << nl << "array('" << r->fixedName << "', ";
        writeType(r->dataMember->type());
        _out << ')';
        _out.dec();
    }
    _out << "));";

    _out << eb;

    endNamespace();

    return false;
}

void
CodeVisitor::visitSequence(const SequencePtr& p)
{
    string type = getTypeVar(p);
    TypePtr content = p->type();

    startNamespace(p);

    //
    // Emit the type information.
    //
    string scoped = p->scoped();
    _out << sp << nl << "if(!isset(" << type << "))";
    _out << sb;
    _out << nl << type << " = IcePHP_defineSequence('" << scoped << "', ";
    writeType(content);
    _out << ");";
    _out << eb;

    endNamespace();
}

void
CodeVisitor::visitDictionary(const DictionaryPtr& p)
{
    TypePtr keyType = p->keyType();
    BuiltinPtr b = BuiltinPtr::dynamicCast(keyType);
    if(b)
    {
        switch(b->kind())
        {
        case Slice::Builtin::KindBool:
        case Slice::Builtin::KindByte:
        case Slice::Builtin::KindShort:
        case Slice::Builtin::KindInt:
        case Slice::Builtin::KindLong:
        case Slice::Builtin::KindString:
            //
            // These types are acceptable as dictionary keys.
            //
            break;

        case Slice::Builtin::KindFloat:
        case Slice::Builtin::KindDouble:
            emitWarning(p->file(), p->line(), "dictionary key type not supported in PHP");
            break;

        case Slice::Builtin::KindObject:
        case Slice::Builtin::KindObjectProxy:
        case Slice::Builtin::KindLocalObject:
            assert(false);
        }
    }
    else if(!EnumPtr::dynamicCast(keyType))
    {
        emitWarning(p->file(), p->line(), "dictionary key type not supported in PHP");
    }

    string type = getTypeVar(p);

    startNamespace(p);

    //
    // Emit the type information.
    //
    string scoped = p->scoped();
    _out << sp << nl << "if(!isset(" << type << "))";
    _out << sb;
    _out << nl << type << " = IcePHP_defineDictionary('" << scoped << "', ";
    writeType(p->keyType());
    _out << ", ";
    writeType(p->valueType());
    _out << ");";
    _out << eb;

    endNamespace();
}

void
CodeVisitor::visitEnum(const EnumPtr& p)
{
    string scoped = p->scoped();
    string name = getName(p);
    string type = getTypeVar(p);
    string abs = getAbsolute(p, _ns);
    EnumeratorList enums = p->getEnumerators();

    startNamespace(p);

    _out << sp << nl << "if(!class_exists('" << escapeName(abs) << "'))";
    _out << sb;
    _out << nl << "class " << name;
    _out << sb;
    
    {
        long i = 0;
        for(EnumeratorList::iterator q = enums.begin(); q != enums.end(); ++q, ++i)
        {
            _out << nl << "const " << fixIdent((*q)->name()) << " = " << (*q)->value() << ';';
        }
    }

    _out << eb;

    //
    // Emit the type information.
    //
    _out << sp << nl << type << " = IcePHP_defineEnum('" << scoped << "', array(";
    for(EnumeratorList::iterator q = enums.begin(); q != enums.end(); ++q)
    {
        if(q != enums.begin())
        {
            _out << ", ";
        }
        _out << "'" << (*q)->name() << "', " << (*q)->value();
    }
    _out << "));";

    _out << eb;

    endNamespace();
}

void
CodeVisitor::visitConst(const ConstPtr& p)
{
    string name = getName(p);
    string type = getTypeVar(p);
    string abs = getAbsolute(p, _ns);

    startNamespace(p);

    _out << sp << nl << "if(!defined('" << escapeName(abs) << "'))";
    _out << sb;
    if(_ns)
    {
        _out << sp << nl << "define(__NAMESPACE__ . '\\\\" << name << "', ";
    }
    else
    {
        _out << sp << nl << "define('" << name << "', ";
    }

    writeConstantValue(p->type(), p->valueType(), p->value());

    _out << ");";
    _out << eb;

    endNamespace();
}

void
CodeVisitor::startNamespace(const ContainedPtr& cont)
{
    if(_ns)
    {
        string scope = cont->scope();
        scope = scope.substr(2); // Removing leading '::'
        scope = scope.substr(0, scope.length() - 2); // Removing trailing '::'
        _out << sp << nl << "namespace " << scopedToName(scope, true);
        _out << sb;
    }
}

void
CodeVisitor::endNamespace()
{
    if(_ns)
    {
        _out << eb;
    }
}

string
CodeVisitor::getTypeVar(const ContainedPtr& p, const string& suffix)
{
    return "$" + getAbsolute(p, false, "_t_", suffix);
}

string
CodeVisitor::getName(const ContainedPtr& p, const string& suffix)
{
    if(_ns)
    {
        return fixIdent(p->name() + suffix);
    }
    else
    {
        return getAbsolute(p, false, "", suffix);
    }
}

void
CodeVisitor::writeType(const TypePtr& p)
{
    BuiltinPtr builtin = BuiltinPtr::dynamicCast(p);
    if(builtin)
    {
        switch(builtin->kind())
        {
            case Builtin::KindBool:
            {
                _out << "$IcePHP__t_bool";
                break;
            }
            case Builtin::KindByte:
            {
                _out << "$IcePHP__t_byte";
                break;
            }
            case Builtin::KindShort:
            {
                _out << "$IcePHP__t_short";
                break;
            }
            case Builtin::KindInt:
            {
                _out << "$IcePHP__t_int";
                break;
            }
            case Builtin::KindLong:
            {
                _out << "$IcePHP__t_long";
                break;
            }
            case Builtin::KindFloat:
            {
                _out << "$IcePHP__t_float";
                break;
            }
            case Builtin::KindDouble:
            {
                _out << "$IcePHP__t_double";
                break;
            }
            case Builtin::KindString:
            {
                _out << "$IcePHP__t_string";
                break;
            }
            case Builtin::KindObject:
            {
                _out << "$Ice__t_Object";
                break;
            }
            case Builtin::KindObjectProxy:
            {
                _out << "$Ice__t_ObjectPrx";
                break;
            }
            case Builtin::KindLocalObject:
            {
                _out << "$Ice__t_LocalObject";
                break;
            }
        }
        return;
    }

    ProxyPtr prx = ProxyPtr::dynamicCast(p);
    if(prx)
    {
        _out << getTypeVar(prx->_class(), "Prx");
        return;
    }

    ContainedPtr cont = ContainedPtr::dynamicCast(p);
    assert(cont);
    _out << getTypeVar(cont);
}

void
CodeVisitor::writeDefaultValue(const TypePtr& p)
{
    BuiltinPtr builtin = BuiltinPtr::dynamicCast(p);
    if(builtin)
    {
        switch(builtin->kind())
        {
            case Builtin::KindBool:
            {
                _out << "false";
                break;
            }
            case Builtin::KindByte:
            case Builtin::KindShort:
            case Builtin::KindInt:
            case Builtin::KindLong:
            {
                _out << "0";
                break;
            }
            case Builtin::KindFloat:
            case Builtin::KindDouble:
            {
                _out << "0.0";
                break;
            }
            case Builtin::KindString:
            {
                _out << "''";
                break;
            }
            case Builtin::KindObject:
            case Builtin::KindObjectProxy:
            case Builtin::KindLocalObject:
            {
                _out << "null";
                break;
            }
        }
        return;
    }

    EnumPtr en = EnumPtr::dynamicCast(p);
    if(en)
    {
        EnumeratorList enums = en->getEnumerators();
        _out << getAbsolute(en, _ns) << "::" << fixIdent(enums.front()->name());
        return;
    }

    //
    // PHP does not allow the following construct:
    //
    // function foo($theStruct=new MyStructType)
    //
    // Instead we use null as the default value and allocate an instance in
    // the constructor.
    //
    StructPtr st = StructPtr::dynamicCast(p);
    if(st)
    {
        _out << "null";
        return;
    }

    _out << "null";
}

void
CodeVisitor::writeAssign(const MemberInfo& info)
{
    StructPtr st = StructPtr::dynamicCast(info.dataMember->type());
    if(st)
    {
        _out << nl << "$this->" << info.fixedName << " = is_null($" << info.fixedName << ") ? new "
             << getAbsolute(st, _ns) << " : $" << info.fixedName << ';';
    }
    else
    {
        _out << nl << "$this->" << info.fixedName << " = $" << info.fixedName << ';';
    }
}

void
CodeVisitor::writeConstantValue(const TypePtr& type, const SyntaxTreeBasePtr& valueType, const string& value)
{
    ConstPtr constant = ConstPtr::dynamicCast(valueType);
    if(constant)
    {
        _out << getAbsolute(constant, _ns);
    }
    else
    {
        Slice::BuiltinPtr b = Slice::BuiltinPtr::dynamicCast(type);
        Slice::EnumPtr en = Slice::EnumPtr::dynamicCast(type);
        if(b)
        {
            switch(b->kind())
            {
            case Slice::Builtin::KindBool:
            case Slice::Builtin::KindByte:
            case Slice::Builtin::KindShort:
            case Slice::Builtin::KindInt:
            case Slice::Builtin::KindFloat:
            case Slice::Builtin::KindDouble:
            {
                _out << value;
                break;
            }
            case Slice::Builtin::KindLong:
            {
                IceUtil::Int64 l;
                IceUtilInternal::stringToInt64(value, l);
                //
                // The platform's 'long' type may not be 64 bits, so we store 64-bit
                // values as a string.
                //
                if(sizeof(IceUtil::Int64) > sizeof(long) && (l < LONG_MIN || l > LONG_MAX))
                {
                    _out << "'" << value << "'";
                }
                else
                {
                    _out << value;
                }
                break;
            }
            case Slice::Builtin::KindString:
            {
                //
                // Expand strings into the basic source character set. We can't use isalpha() and the like
                // here because they are sensitive to the current locale.
                //
                static const string basicSourceChars = "abcdefghijklmnopqrstuvwxyz"
                                                       "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                       "0123456789"
                                                       "_{}[]#()<>%:;.?*+-/^&|~!=, '";
                static const set<char> charSet(basicSourceChars.begin(), basicSourceChars.end());

                _out << "\"";                                       // Opening "

                for(string::const_iterator c = value.begin(); c != value.end(); ++c)
                {
                    switch(*c)
                    {
                    case '$':
                    {
                        _out << "\\$";
                        break;
                    }
                    case '"':
                    {
                        _out << "\\\"";
                        break;
                    }
                    case '\\':
                    {
                        _out << "\\\\";
                        break;
                    }
                    case '\r':
                    {
                        _out << "\\r";
                        break;
                    }
                    case '\n':
                    {
                        _out << "\\n";
                        break;
                    }
                    case '\t':
                    {
                        _out << "\\t";
                        break;
                    }
                    case '\b':
                    {
                        _out << "\\b";
                        break;
                    }
                    case '\f':
                    {
                        _out << "\\f";
                        break;
                    }
                    default:
                    {
                        if(charSet.find(*c) == charSet.end())
                        {
                            unsigned char uc = *c;              // Char may be signed, so make it positive.
                            stringstream s;
                            s << "\\";                          // Print as octal if not in basic source character set.
                            s.flags(ios_base::oct);
                            s.width(3);
                            s.fill('0');
                            s << static_cast<unsigned>(uc);
                            _out << s.str();
                        }
                        else
                        {
                            _out << *c;                         // Print normally if in basic source character set.
                        }
                        break;
                    }
                    }
                }

                _out << "\"";                                   // Closing "
                break;
            }
            case Slice::Builtin::KindObject:
            case Slice::Builtin::KindObjectProxy:
            case Slice::Builtin::KindLocalObject:
                assert(false);
            }
        }
        else if(en)
        {
            string val = value;
            string::size_type colon = val.rfind(':');
            if(colon != string::npos)
            {
                val = val.substr(colon + 1);
            }
            Slice::EnumeratorList l = en->getEnumerators();
            for(Slice::EnumeratorList::iterator q = l.begin(); q != l.end(); ++q)
            {
                if((*q)->name() == val)
                {
                    _out << getAbsolute(en, _ns) << "::" << fixIdent(val);
                    break;
                }
            }
        }
        else
        {
            assert(false); // Unknown const type.
        }
    }
}

void
CodeVisitor::writeConstructorParams(const MemberInfoList& members)
{
    for(MemberInfoList::const_iterator p = members.begin(); p != members.end(); ++p)
    {
        if(p != members.begin())
        {
            _out << ", ";
        }
        _out << '$' << p->fixedName << "=";

        const DataMemberPtr member = p->dataMember;
        if(member->defaultValueType())
        {
            writeConstantValue(member->type(), member->defaultValueType(), member->defaultValue());
        }
        else if(member->optional())
        {
            _out << "Ice_Unset";
        }
        else
        {
            writeDefaultValue(member->type());
        }
    }
}

string
CodeVisitor::getOperationMode(Slice::Operation::Mode mode, bool /*ns*/)
{
    ostringstream ostr;
    ostr << static_cast<int>(mode);
    return ostr.str();
}

void
CodeVisitor::collectClassMembers(const ClassDefPtr& p, MemberInfoList& allMembers, bool inherited)
{
    ClassList bases = p->bases();
    if(!bases.empty() && !bases.front()->isInterface())
    {
        collectClassMembers(bases.front(), allMembers, true);
    }

    DataMemberList members = p->dataMembers();

    for(DataMemberList::iterator q = members.begin(); q != members.end(); ++q)
    {
        MemberInfo m;
        m.fixedName = fixIdent((*q)->name());
        m.inherited = inherited;
        m.dataMember = *q;
        allMembers.push_back(m);
    }
}

void
CodeVisitor::collectExceptionMembers(const ExceptionPtr& p, MemberInfoList& allMembers, bool inherited)
{
    ExceptionPtr base = p->base();
    if(base)
    {
        collectExceptionMembers(base, allMembers, true);
    }

    DataMemberList members = p->dataMembers();

    for(DataMemberList::iterator q = members.begin(); q != members.end(); ++q)
    {
        MemberInfo m;
        m.fixedName = fixIdent((*q)->name());
        m.inherited = inherited;
        m.dataMember = *q;
        allMembers.push_back(m);
    }
}

static void
generate(const UnitPtr& un, bool all, bool checksum, bool ns, const vector<string>& includePaths, Output& out)
{
    if(!all)
    {
        vector<string> paths = includePaths;
        for(vector<string>::iterator p = paths.begin(); p != paths.end(); ++p)
        {
            *p = fullPath(*p);
        }

        StringList includes = un->includeFiles();
        if(!includes.empty())
        {
            if(ns)
            {
                out << sp;
                out << nl << "namespace";
                out << sb;
            }
            for(StringList::const_iterator q = includes.begin(); q != includes.end(); ++q)
            {
                string file = changeInclude(*q, paths);
                out << nl << "require_once '" << file << ".php';";
            }
            if(ns)
            {
                out << eb;
            }
        }
    }

    CodeVisitor codeVisitor(out, ns);
    un->visit(&codeVisitor, false);

    if(checksum)
    {
        ChecksumMap checksums = createChecksums(un);
        if(!checksums.empty())
        {
            out << sp;
            if(ns)
            {
                out << "namespace"; // Global namespace.
                out << sb;
            }
            for(ChecksumMap::const_iterator p = checksums.begin(); p != checksums.end(); ++p)
            {
                out << nl << "$Ice_sliceChecksums[\"" << p->first << "\"] = \"";
                ostringstream str;
                str.flags(ios_base::hex);
                str.fill('0');
                for(vector<unsigned char>::const_iterator q = p->second.begin(); q != p->second.end(); ++q)
                {
                    str << (int)(*q);
                }
                out << str.str() << "\";";
            }
            if(ns)
            {
                out << eb;
            }
        }
    }

    out << nl; // Trailing newline.
}

static void
printHeader(IceUtilInternal::Output& out)
{
    static const char* header =
"// **********************************************************************\n"
"//\n"
"// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.\n"
"//\n"
"// This copy of Ice is licensed to you under the terms described in the\n"
"// ICE_LICENSE file included in this distribution.\n"
"//\n"
"// **********************************************************************\n"
        ;

    out << header;
    out << "//\n";
    out << "// Ice version " << ICE_STRING_VERSION << "\n";
    out << "//\n";
}

namespace
{

IceUtil::Mutex* globalMutex = 0;
bool interrupted = false;

class Init
{
public:

    Init()
    {
        globalMutex = new IceUtil::Mutex;
    }

    ~Init()
    {
        delete globalMutex;
        globalMutex = 0;
    }
};

Init init;

}

static void
interruptedCallback(int /*signal*/)
{
    IceUtilInternal::MutexPtrLock<IceUtil::Mutex> sync(globalMutex);

    interrupted = true;
}

static void
usage(const char* n)
{
    getErrorStream() << "Usage: " << n << " [options] slice-files...\n";
    getErrorStream() <<        
        "Options:\n"
        "-h, --help           Show this message.\n"
        "-v, --version        Display the Ice version.\n"
        "-DNAME               Define NAME as 1.\n"
        "-DNAME=DEF           Define NAME as DEF.\n"
        "-UNAME               Remove any definition for NAME.\n"
        "-IDIR                Put DIR in the include file search path.\n"
        "-E                   Print preprocessor output on stdout.\n"
        "--output-dir DIR     Create files in the directory DIR.\n"
        "--depend             Generate Makefile dependencies.\n"
        "-d, --debug          Print debug messages.\n"
        "--ice                Permit `Ice' prefix (for building Ice source code only).\n"
        "--underscore         Permit underscores in Slice identifiers.\n"
        "--all                Generate code for Slice definitions in included files.\n"
        "--checksum           Generate checksums for Slice definitions.\n"
        "-n, --namespace      Use PHP namespaces (requires PHP 5.3 or later).\n"
        ;
}

int
compile(int argc, char* argv[])
{
    IceUtilInternal::Options opts;
    opts.addOpt("h", "help");
    opts.addOpt("v", "version");
    opts.addOpt("D", "", IceUtilInternal::Options::NeedArg, "", IceUtilInternal::Options::Repeat);
    opts.addOpt("U", "", IceUtilInternal::Options::NeedArg, "", IceUtilInternal::Options::Repeat);
    opts.addOpt("I", "", IceUtilInternal::Options::NeedArg, "", IceUtilInternal::Options::Repeat);
    opts.addOpt("E");
    opts.addOpt("", "output-dir", IceUtilInternal::Options::NeedArg);
    opts.addOpt("", "depend");
    opts.addOpt("d", "debug");
    opts.addOpt("", "ice");
    opts.addOpt("", "underscore");
    opts.addOpt("", "all");
    opts.addOpt("", "checksum");
    opts.addOpt("n", "namespace");
     
    vector<string> args;
    try
    {
        args = opts.parse(argc, (const char**)argv);
    }
    catch(const IceUtilInternal::BadOptException& e)
    {
        getErrorStream() << argv[0] << ": error: " << e.reason << endl;
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
        getErrorStream() << ICE_STRING_VERSION << endl;
        return EXIT_SUCCESS;
    }

    vector<string> cppArgs;
    vector<string> optargs = opts.argVec("D");
    for(vector<string>::const_iterator i = optargs.begin(); i != optargs.end(); ++i)
    {
        cppArgs.push_back("-D" + *i);
    }

    optargs = opts.argVec("U");
    for(vector<string>::const_iterator i = optargs.begin(); i != optargs.end(); ++i)
    {
        cppArgs.push_back("-U" + *i);
    }

    vector<string> includePaths = opts.argVec("I");
    for(vector<string>::const_iterator i = includePaths.begin(); i != includePaths.end(); ++i)
    {
        cppArgs.push_back("-I" + Preprocessor::normalizeIncludePath(*i));
    }

    bool preprocess = opts.isSet("E");

    string output = opts.optArg("output-dir");

    bool depend = opts.isSet("depend");

    bool debug = opts.isSet("debug");

    bool ice = opts.isSet("ice");

    bool underscore = opts.isSet("underscore");

    bool all = opts.isSet("all");

    bool checksum = opts.isSet("checksum");

    bool ns = opts.isSet("namespace");

    if(args.empty())
    {
        getErrorStream() << argv[0] << ": error: no input file" << endl;
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    int status = EXIT_SUCCESS;

    IceUtil::CtrlCHandler ctrlCHandler;
    ctrlCHandler.setCallback(interruptedCallback);

    for(vector<string>::const_iterator i = args.begin(); i != args.end(); ++i)
    {
        //
        // Ignore duplicates.
        //
        vector<string>::iterator p = find(args.begin(), args.end(), *i);
        if(p != i)
        {
            continue;
        }

        if(depend)
        {
            PreprocessorPtr icecpp = Preprocessor::create(argv[0], *i, cppArgs);
            FILE* cppHandle = icecpp->preprocess(false, "-D__SLICE2PHP__");

            if(cppHandle == 0)
            {
                return EXIT_FAILURE;
            }

            UnitPtr u = Unit::createUnit(false, false, ice, underscore);
            int parseStatus = u->parse(*i, cppHandle, debug);
            u->destroy();

            if(parseStatus == EXIT_FAILURE)
            {
                return EXIT_FAILURE;
            }

            if(!icecpp->printMakefileDependencies(Preprocessor::PHP, includePaths, "-D__SLICE2PHP__"))
            {
                return EXIT_FAILURE;
            }

            if(!icecpp->close())
            {
                return EXIT_FAILURE;
            }
        }
        else
        {
            PreprocessorPtr icecpp = Preprocessor::create(argv[0], *i, cppArgs);
            FILE* cppHandle = icecpp->preprocess(false, "-D__SLICE2PHP__");

            if(cppHandle == 0)
            {
                return EXIT_FAILURE;
            }

            if(preprocess)
            {
                char buf[4096];
                while(fgets(buf, static_cast<int>(sizeof(buf)), cppHandle) != NULL)
                {
                    if(fputs(buf, stdout) == EOF)
                    {
                        return EXIT_FAILURE;
                    }
                }
                if(!icecpp->close())
                {
                    return EXIT_FAILURE;
                }
            }
            else
            {
                UnitPtr u = Unit::createUnit(false, all, ice, underscore);
                int parseStatus = u->parse(*i, cppHandle, debug);

                if(!icecpp->close())
                {
                    u->destroy();
                    return EXIT_FAILURE;
                }

                if(parseStatus == EXIT_FAILURE)
                {
                    status = EXIT_FAILURE;
                }
                else
                {
                    string base = icecpp->getBaseName();
                    string::size_type pos = base.find_last_of("/\\");
                    if(pos != string::npos)
                    {
                        base.erase(0, pos + 1);
                    }

                    string file = base + ".php";
                    if(!output.empty())
                    {
                        file = output + '/' + file;
                    }

                    try
                    {
                        IceUtilInternal::Output out;
                        out.open(file.c_str());
                        if(!out)
                        {
                            ostringstream os;
                            os << "cannot open`" << file << "': " << strerror(errno);
                            throw FileException(__FILE__, __LINE__, os.str());
                        }
                        FileTracker::instance()->addFile(file);

                        out << "<?php\n";
                        printHeader(out);
                        printGeneratedHeader(out, base + ".ice");

                        //
                        // Generate the PHP mapping.
                        //
                        generate(u, all, checksum, ns, includePaths, out);

                        out << "?>\n";
                        out.close();
                    }
                    catch(const Slice::FileException& ex)
                    {
                        // If a file could not be created, then cleanup any
                        // created files.
                        FileTracker::instance()->cleanup();
                        u->destroy();
                        getErrorStream() << argv[0] << ": error: " << ex.reason() << endl;
                        return EXIT_FAILURE;
                    }
                    catch(const string& err)
                    {
                        FileTracker::instance()->cleanup();
                        getErrorStream() << argv[0] << ": error: " << err << endl;
                        status = EXIT_FAILURE;
                    }
                }

                u->destroy();
            }
        }

        {
            IceUtilInternal::MutexPtrLock<IceUtil::Mutex> sync(globalMutex);

            if(interrupted)
            {
                FileTracker::instance()->cleanup();
                return EXIT_FAILURE;
            }
        }
    }

    return status;
}

int
main(int argc, char* argv[])
{
    try
    {
        return compile(argc, argv);
    }
    catch(const std::exception& ex)
    {
        getErrorStream() << argv[0] << ": error:" << ex.what() << endl;
        return EXIT_FAILURE;
    }
    catch(const std::string& msg)
    {
        getErrorStream() << argv[0] << ": error:" << msg << endl;
        return EXIT_FAILURE;
    }
    catch(const char* msg)
    {
        getErrorStream() << argv[0] << ": error:" << msg << endl;
        return EXIT_FAILURE;
    }
    catch(...)
    {
        getErrorStream() << argv[0] << ": error:" << "unknown exception" << endl;
        return EXIT_FAILURE;
    }
}
