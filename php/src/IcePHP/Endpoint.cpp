// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Endpoint.h>
#include <Util.h>

using namespace std;
using namespace IcePHP;

ZEND_EXTERN_MODULE_GLOBALS(ice)

//
// Class entries represent the PHP class implementations we have registered.
//
static zend_class_entry* endpointClassEntry = 0;

static zend_class_entry* endpointInfoClassEntry = 0;
static zend_class_entry* ipEndpointInfoClassEntry = 0;
static zend_class_entry* tcpEndpointInfoClassEntry = 0;
static zend_class_entry* udpEndpointInfoClassEntry = 0;
static zend_class_entry* opaqueEndpointInfoClassEntry = 0;

//
// Ice::Endpoint support.
//
static zend_object_handlers _endpointHandlers;
static zend_object_handlers _endpointInfoHandlers;

extern "C"
{
static zend_object_value handleEndpointAlloc(zend_class_entry* TSRMLS_DC);
static void handleEndpointFreeStorage(void* TSRMLS_DC);

static zend_object_value handleEndpointInfoAlloc(zend_class_entry* TSRMLS_DC);
static void handleEndpointInfoFreeStorage(void* TSRMLS_DC);
}

ZEND_METHOD(Ice_Endpoint, __construct)
{
    runtimeError("Endpoint cannot be instantiated" TSRMLS_CC);
}

ZEND_METHOD(Ice_Endpoint, __toString)
{
    if(ZEND_NUM_ARGS() > 0)
    {
        WRONG_PARAM_COUNT;
    }

    Ice::EndpointPtr _this = Wrapper<Ice::EndpointPtr>::value(getThis() TSRMLS_CC);
    assert(_this);

    try
    {
        string str = _this->toString();
        RETURN_STRINGL(STRCAST(str.c_str()), str.length(), 1);
    }
    catch(const IceUtil::Exception& ex)
    {
        throwException(ex TSRMLS_CC);
        RETURN_NULL();
    }
}

ZEND_METHOD(Ice_Endpoint, toString)
{
    ZEND_MN(Ice_Endpoint___toString)(INTERNAL_FUNCTION_PARAM_PASSTHRU);
}

ZEND_METHOD(Ice_Endpoint, getInfo)
{
    if(ZEND_NUM_ARGS() > 0)
    {
        WRONG_PARAM_COUNT;
    }

    Ice::EndpointPtr _this = Wrapper<Ice::EndpointPtr>::value(getThis() TSRMLS_CC);
    assert(_this);

    if(!createEndpointInfo(return_value, _this->getInfo() TSRMLS_CC))
    {
        RETURN_NULL();
    }
}

#ifdef _WIN32
extern "C"
#endif
static zend_object_value
handleEndpointAlloc(zend_class_entry* ce TSRMLS_DC)
{
    zend_object_value result;

    Wrapper<Ice::EndpointPtr>* obj = Wrapper<Ice::EndpointPtr>::create(ce TSRMLS_CC);
    assert(obj);

    result.handle = zend_objects_store_put(obj, 0, (zend_objects_free_object_storage_t)handleEndpointFreeStorage,
                                           0 TSRMLS_CC);
    result.handlers = &_endpointHandlers;

    return result;
}

#ifdef _WIN32
extern "C"
#endif
static void
handleEndpointFreeStorage(void* p TSRMLS_DC)
{
    Wrapper<Ice::EndpointPtr>* obj = static_cast<Wrapper<Ice::EndpointPtr>*>(p);
    delete obj->ptr;
    zend_object_std_dtor(static_cast<zend_object*>(p) TSRMLS_CC);
    efree(p);
}

ZEND_METHOD(Ice_EndpointInfo, __construct)
{
    runtimeError("EndpointInfo cannot be instantiated" TSRMLS_CC);
}

ZEND_METHOD(Ice_EndpointInfo, type)
{
    if(ZEND_NUM_ARGS() > 0)
    {
        WRONG_PARAM_COUNT;
    }

    Ice::EndpointInfoPtr _this = Wrapper<Ice::EndpointInfoPtr>::value(getThis() TSRMLS_CC);
    assert(_this);

    try
    {
        short type = static_cast<short>(_this->type());
        RETURN_LONG(type);
    }
    catch(const IceUtil::Exception& ex)
    {
        throwException(ex TSRMLS_CC);
        RETURN_NULL();
    }
}

ZEND_METHOD(Ice_EndpointInfo, datagram)
{
    if(ZEND_NUM_ARGS() > 0)
    {
        WRONG_PARAM_COUNT;
    }

    Ice::EndpointInfoPtr _this = Wrapper<Ice::EndpointInfoPtr>::value(getThis() TSRMLS_CC);
    assert(_this);

    try
    {
        RETURN_BOOL(_this->datagram() ? 1 : 0);
    }
    catch(const IceUtil::Exception& ex)
    {
        throwException(ex TSRMLS_CC);
        RETURN_NULL();
    }
}

ZEND_METHOD(Ice_EndpointInfo, secure)
{
    if(ZEND_NUM_ARGS() > 0)
    {
        WRONG_PARAM_COUNT;
    }

    Ice::EndpointInfoPtr _this = Wrapper<Ice::EndpointInfoPtr>::value(getThis() TSRMLS_CC);
    assert(_this);

    try
    {
        RETURN_BOOL(_this->secure() ? 1 : 0);
    }
    catch(const IceUtil::Exception& ex)
    {
        throwException(ex TSRMLS_CC);
        RETURN_NULL();
    }
}

#ifdef _WIN32
extern "C"
#endif
static zend_object_value
handleEndpointInfoAlloc(zend_class_entry* ce TSRMLS_DC)
{
    zend_object_value result;

    Wrapper<Ice::EndpointPtr>* obj = Wrapper<Ice::EndpointPtr>::create(ce TSRMLS_CC);
    assert(obj);

    result.handle = zend_objects_store_put(obj, 0, (zend_objects_free_object_storage_t)handleEndpointInfoFreeStorage,
                                           0 TSRMLS_CC);
    result.handlers = &_endpointInfoHandlers;

    return result;
}

#ifdef _WIN32
extern "C"
#endif
static void
handleEndpointInfoFreeStorage(void* p TSRMLS_DC)
{
    Wrapper<Ice::EndpointInfoPtr>* obj = static_cast<Wrapper<Ice::EndpointInfoPtr>*>(p);
    delete obj->ptr;
    zend_object_std_dtor(static_cast<zend_object*>(p) TSRMLS_CC);
    efree(p);
}

static zend_function_entry _interfaceMethods[] =
{
    {0, 0, 0}
};

//
// Necessary to suppress warnings from zend_function_entry in php-5.2.
//
#if defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wwrite-strings"
#endif

//
// Predefined methods for Endpoint.
//
static zend_function_entry _endpointMethods[] =
{
    ZEND_ME(Ice_Endpoint, __construct, NULL, ZEND_ACC_PRIVATE|ZEND_ACC_CTOR)
    ZEND_ME(Ice_Endpoint, __toString, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(Ice_Endpoint, toString, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(Ice_Endpoint, getInfo, NULL, ZEND_ACC_PUBLIC)
    {0, 0, 0}
};

//
// Predefined methods for EndpointInfo.
//
static zend_function_entry _endpointInfoMethods[] =
{
    ZEND_ME(Ice_EndpointInfo, __construct, NULL, ZEND_ACC_PRIVATE|ZEND_ACC_CTOR)
    ZEND_ME(Ice_EndpointInfo, type, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(Ice_EndpointInfo, datagram, NULL, ZEND_ACC_PUBLIC)
    ZEND_ME(Ice_EndpointInfo, secure, NULL, ZEND_ACC_PUBLIC)
    {0, 0, 0}
};

//
// enable warning again
//
#if defined(__GNUC__)
#  pragma GCC diagnostic error "-Wwrite-strings"
#endif

bool
IcePHP::endpointInit(TSRMLS_D)
{
    //
    // We register an interface and a class that implements the interface. This allows
    // applications to safely include the Slice-generated code for the type.
    //

    //
    // Register the Endpoint interface.
    //
    zend_class_entry ce;
#ifdef ICEPHP_USE_NAMESPACES
    INIT_NS_CLASS_ENTRY(ce, "Ice", "Endpoint", _interfaceMethods);
#else
    INIT_CLASS_ENTRY(ce, "Ice_Endpoint", _interfaceMethods);
#endif
    zend_class_entry* endpointInterface = zend_register_internal_interface(&ce TSRMLS_CC);

    //
    // Register the Endpoint class.
    //
    INIT_CLASS_ENTRY(ce, "IcePHP_Endpoint", _endpointMethods);
    ce.create_object = handleEndpointAlloc;
    endpointClassEntry = zend_register_internal_class(&ce TSRMLS_CC);
    memcpy(&_endpointHandlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    zend_class_implements(endpointClassEntry TSRMLS_CC, 1, endpointInterface);

    //
    // Register the EndpointInfo class.
    //
#ifdef ICEPHP_USE_NAMESPACES
    INIT_NS_CLASS_ENTRY(ce, "Ice", "EndpointInfo", _endpointInfoMethods);
#else
    INIT_CLASS_ENTRY(ce, "Ice_EndpointInfo", _endpointInfoMethods);
#endif
    ce.create_object = handleEndpointInfoAlloc;
    endpointInfoClassEntry = zend_register_internal_class(&ce TSRMLS_CC);
    memcpy(&_endpointInfoHandlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    zend_declare_property_long(endpointInfoClassEntry, STRCAST("timeout"), sizeof("timeout") - 1, 0,
                               ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_bool(endpointInfoClassEntry, STRCAST("compress"), sizeof("compress") - 1, 0,
                               ZEND_ACC_PUBLIC TSRMLS_CC);

    //
    // Register the IPEndpointInfo class.
    //
#ifdef ICEPHP_USE_NAMESPACES
    INIT_NS_CLASS_ENTRY(ce, "Ice", "IPEndpointInfo", NULL);
#else
    INIT_CLASS_ENTRY(ce, "Ice_IPEndpointInfo", NULL);
#endif
    ce.create_object = handleEndpointInfoAlloc;
    ipEndpointInfoClassEntry = zend_register_internal_class_ex(&ce, endpointInfoClassEntry, NULL TSRMLS_CC);
    zend_declare_property_string(ipEndpointInfoClassEntry, STRCAST("host"), sizeof("host") - 1, STRCAST(""),
                                 ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_long(ipEndpointInfoClassEntry, STRCAST("port"), sizeof("port") - 1, 0,
                               ZEND_ACC_PUBLIC TSRMLS_CC);

    //
    // Register the TCPEndpointInfo class.
    //
#ifdef ICEPHP_USE_NAMESPACES
    INIT_NS_CLASS_ENTRY(ce, "Ice", "TCPEndpointInfo", NULL);
#else
    INIT_CLASS_ENTRY(ce, "Ice_TCPEndpointInfo", NULL);
#endif
    ce.create_object = handleEndpointInfoAlloc;
    tcpEndpointInfoClassEntry = zend_register_internal_class_ex(&ce, ipEndpointInfoClassEntry, NULL TSRMLS_CC);

    //
    // Register the UDPEndpointInfo class.
    //
#ifdef ICEPHP_USE_NAMESPACES
    INIT_NS_CLASS_ENTRY(ce, "Ice", "UDPEndpointInfo", NULL);
#else
    INIT_CLASS_ENTRY(ce, "Ice_UDPEndpointInfo", NULL);
#endif
    ce.create_object = handleEndpointInfoAlloc;
    udpEndpointInfoClassEntry = zend_register_internal_class_ex(&ce, ipEndpointInfoClassEntry, NULL TSRMLS_CC);
    zend_declare_property_string(udpEndpointInfoClassEntry, STRCAST("mcastInterface"), sizeof("mcastInterface") - 1,
                                 STRCAST(""), ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_long(udpEndpointInfoClassEntry, STRCAST("mcastTtl"), sizeof("mcastTtl") - 1, 0,
                               ZEND_ACC_PUBLIC TSRMLS_CC);

    //
    // Register the OpaqueEndpointInfo class.
    //
#ifdef ICEPHP_USE_NAMESPACES
    INIT_NS_CLASS_ENTRY(ce, "Ice", "OpaqueEndpointInfo", NULL);
#else
    INIT_CLASS_ENTRY(ce, "Ice_OpaqueEndpointInfo", NULL);
#endif
    ce.create_object = handleEndpointInfoAlloc;
    opaqueEndpointInfoClassEntry = zend_register_internal_class_ex(&ce, endpointInfoClassEntry, NULL TSRMLS_CC);
    zend_declare_property_null(opaqueEndpointInfoClassEntry, STRCAST("rawEncoding"), sizeof("rawEncoding") - 1,
                               ZEND_ACC_PUBLIC TSRMLS_CC);
    zend_declare_property_null(opaqueEndpointInfoClassEntry, STRCAST("rawBytes"), sizeof("rawBytes") - 1,
                               ZEND_ACC_PUBLIC TSRMLS_CC);

    return true;
}

bool
IcePHP::createEndpoint(zval* zv, const Ice::EndpointPtr& p TSRMLS_DC)
{
    if(object_init_ex(zv, endpointClassEntry) != SUCCESS)
    {
        runtimeError("unable to initialize endpoint" TSRMLS_CC);
        return false;
    }

    Wrapper<Ice::EndpointPtr>* obj = Wrapper<Ice::EndpointPtr>::extract(zv TSRMLS_CC);
    assert(obj);
    assert(!obj->ptr);
    obj->ptr = new Ice::EndpointPtr(p);

    return true;
}

bool
IcePHP::fetchEndpoint(zval* zv, Ice::EndpointPtr& endpoint TSRMLS_DC)
{
    if(ZVAL_IS_NULL(zv))
    {
        endpoint = 0;
    }
    else
    {
        if(Z_TYPE_P(zv) != IS_OBJECT || !checkClass(Z_OBJCE_P(zv), endpointClassEntry))
        {
            invalidArgument("value is not an endpoint" TSRMLS_CC);
            return false;
        }
        Wrapper<Ice::EndpointPtr>* obj = Wrapper<Ice::EndpointPtr>::extract(zv TSRMLS_CC);
        if(!obj)
        {
            return false;
        }
        endpoint = *obj->ptr;
    }
    return true;
}

bool
IcePHP::createEndpointInfo(zval* zv, const Ice::EndpointInfoPtr& p TSRMLS_DC)
{
    int status;
    if(Ice::TCPEndpointInfoPtr::dynamicCast(p))
    {
        status = object_init_ex(zv, tcpEndpointInfoClassEntry);
    }
    else if(Ice::UDPEndpointInfoPtr::dynamicCast(p))
    {
        Ice::UDPEndpointInfoPtr info = Ice::UDPEndpointInfoPtr::dynamicCast(p);
        if((status = object_init_ex(zv, udpEndpointInfoClassEntry)) == SUCCESS)
        {
            add_property_string(zv, STRCAST("mcastInterface"), const_cast<char*>(info->mcastInterface.c_str()), 1);
            add_property_long(zv, STRCAST("mcastTtl"), static_cast<long>(info->mcastTtl));
        }
    }
    else if(Ice::OpaqueEndpointInfoPtr::dynamicCast(p))
    {
        Ice::OpaqueEndpointInfoPtr info = Ice::OpaqueEndpointInfoPtr::dynamicCast(p);
        if((status = object_init_ex(zv, opaqueEndpointInfoClassEntry)) == SUCCESS)
        {
            zval* rawEncoding;
            MAKE_STD_ZVAL(rawEncoding);
            createEncodingVersion(rawEncoding, info->rawEncoding TSRMLS_CC);
            add_property_zval(zv, STRCAST("rawEncoding"), rawEncoding);
            zval_ptr_dtor(&rawEncoding); // add_property_zval increased the refcount of rawEncoding

            zval* rawBytes;
            MAKE_STD_ZVAL(rawBytes);
            array_init(rawBytes);
            for(Ice::ByteSeq::iterator i = info->rawBytes.begin(); i != info->rawBytes.end(); ++i)
            {
                add_next_index_long(rawBytes, *i & 0xff);
            }
            add_property_zval(zv, STRCAST("rawBytes"), rawBytes);
            zval_ptr_dtor(&rawBytes); // add_property_zval increased the refcount of rawBytes
        }
    }
    else if(Ice::IPEndpointInfoPtr::dynamicCast(p))
    {
        status = object_init_ex(zv, ipEndpointInfoClassEntry);
    }
    else
    {
        status = object_init_ex(zv, endpointInfoClassEntry);
    }

    if(status != SUCCESS)
    {
        runtimeError("unable to initialize endpoint info" TSRMLS_CC);
        return false;
    }

    if(Ice::IPEndpointInfoPtr::dynamicCast(p))
    {
        Ice::IPEndpointInfoPtr info = Ice::IPEndpointInfoPtr::dynamicCast(p);
        add_property_string(zv, STRCAST("host"), const_cast<char*>(info->host.c_str()), 1);
        add_property_long(zv, STRCAST("port"), static_cast<long>(info->port));
    }

    add_property_long(zv, STRCAST("timeout"), static_cast<long>(p->timeout));
    add_property_bool(zv, STRCAST("compress"), static_cast<long>(p->compress));

    Wrapper<Ice::EndpointInfoPtr>* obj = Wrapper<Ice::EndpointInfoPtr>::extract(zv TSRMLS_CC);
    assert(obj);
    assert(!obj->ptr);
    obj->ptr = new Ice::EndpointInfoPtr(p);

    return true;
}
