// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#define ICE_BOX_API_EXPORTS
#include <IceBox/IceBox.h>

using namespace std;

void
IceBox::FailureException::ice_print(ostream& out) const
{
    Exception::ice_print(out);
    out << ":\nservice failure exception: " << reason;
}

