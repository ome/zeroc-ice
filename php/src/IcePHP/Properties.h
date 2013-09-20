// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICEPHP_PROPERTIES_H
#define ICEPHP_PROPERTIES_H

#include <Config.h>

//
// Global functions.
//
extern "C"
{
ZEND_FUNCTION(Ice_createProperties);
}

namespace IcePHP
{

bool propertiesInit(TSRMLS_D);

bool createProperties(zval*, const Ice::PropertiesPtr& TSRMLS_DC);
bool fetchProperties(zval*, Ice::PropertiesPtr& TSRMLS_DC);

//
// Class entry.
//
extern zend_class_entry* propertiesClassEntry;

} // End of namespace IcePHP

#endif
