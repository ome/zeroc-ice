// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

//
// The main definitions for our simple Warehouse application
//
module Warehouse
{

exception OutOfStock {};

interface Item
{
    idempotent string getDescription();
    void setDescription(string newDescription);

    idempotent float getUnitPrice();
    void setUnitPrice(float newUnitPrice);

    idempotent int quantityInStock();
    void adjustStock(int value) throws OutOfStock;
};

};

