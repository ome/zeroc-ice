﻿// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************


//
// Check that UTF-8 BOM is rejected when not at start of file
//
﻿

//
// Check that 'œ' is properly rejected in identifiers
//

module Test
{
   interface Œuvre
   {
      void cœur();
   };  
};
