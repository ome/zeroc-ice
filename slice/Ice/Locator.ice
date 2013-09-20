// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

[["cpp:header-ext:h"]]

#include <Ice/Identity.ice>
#include <Ice/ProcessF.ice>

module Ice
{

/**
 *
 * This exception is raised if an adapter cannot be found.
 *
 **/
exception AdapterNotFoundException
{
};

/**
 *
 * This exception is raised if the replica group provided by the
 * server is invalid.
 *
 **/
exception InvalidReplicaGroupIdException
{
};

/**
 *
 * This exception is raised if a server tries to set endpoints for
 * an adapter that is already active.
 *
 **/
exception AdapterAlreadyActiveException
{
};

/**
 *
 * This exception is raised if an object cannot be found.
 *
 **/
exception ObjectNotFoundException
{
};

/**
 *
 * This exception is raised if a server cannot be found.
 *
 **/
exception ServerNotFoundException
{
};

interface LocatorRegistry;

/**
 *
 * The Ice locator interface. This interface is used by clients to
 * lookup adapters and objects. It is also used by servers to get the
 * locator registry proxy.
 *
 * <p class="Note">The {@link Locator} interface is intended to be used by
 * Ice internals and by locator implementations. Regular user code
 * should not attempt to use any functionality of this interface
 * directly.
 *
 **/
interface Locator
{
    /**
     *
     * Find an object by identity and return its proxy.
     *
     * @param id The identity.
     *
     * @return The proxy, or null if the object is not active.
     *
     * @throws ObjectNotFoundException Raised if the object cannot
     * be found.
     *
     **/
    ["amd", "nonmutating", "cpp:const"] idempotent Object* findObjectById(Ice::Identity id)
        throws ObjectNotFoundException;

    /**
     *
     * Find an adapter by id and return its proxy (a dummy direct
     * proxy created by the adapter).
     *
     * @param id The adapter id.
     *
     * @return The adapter proxy, or null if the adapter is not active.
     * 
     * @throws AdapterNotFoundException Raised if the adapter cannot be
     * found.
     *
     **/
    ["amd", "nonmutating", "cpp:const"] idempotent Object* findAdapterById(string id)
        throws AdapterNotFoundException;

    /**
     *
     * Get the locator registry.
     *
     * @return The locator registry.
     *
     **/
    ["nonmutating", "cpp:const"] idempotent LocatorRegistry* getRegistry();
};

/**
 *
 * The Ice locator registry interface. This interface is used by
 * servers to register adapter endpoints with the locator.
 *
 * <p class="Note"> The {@link LocatorRegistry} interface is intended to be used
 * by Ice internals and by locator implementations. Regular user
 * code should not attempt to use any functionality of this interface
 * directly.
 *
 **/
interface LocatorRegistry
{
    /**
     *
     * Set the adapter endpoints with the locator registry.
     *
     * @param id The adapter id.
     *
     * @param proxy The adapter proxy (a dummy direct proxy created
     * by the adapter). The direct proxy contains the adapter
     * endpoints.
     *
     * @throws AdapterNotFoundException Raised if the adapter cannot
     * be found, or if the locator only allows
     * registered adapters to set their active proxy and the
     * adapter is not registered with the locator.
     *
     * @throws AdapterAlreadyActiveException Raised if an adapter with the same
     * id is already active.
     *
     **/
    ["amd"] idempotent void setAdapterDirectProxy(string id, Object* proxy)
        throws AdapterNotFoundException, AdapterAlreadyActiveException;

    /**
     *
     * Set the adapter endpoints with the locator registry.
     *
     * @param adapterId The adapter id.
     *
     * @param replicaGroupId The replica group id.
     *
     * @param p The adapter proxy (a dummy direct proxy created
     * by the adapter). The direct proxy contains the adapter
     * endpoints.
     *
     * @throws AdapterNotFoundException Raised if the adapter cannot
     * be found, or if the locator only allows registered adapters to
     * set their active proxy and the adapter is not registered with
     * the locator.
     *
     * @throws AdapterAlreadyActiveException Raised if an adapter with the same
     * id is already active.
     *
     * @throws InvalidReplicaGroupIdException Raised if the given
     * replica group doesn't match the one registered with the
     * locator registry for this object adapter.
     *
     **/
    ["amd"] idempotent void setReplicatedAdapterDirectProxy(string adapterId, string replicaGroupId, Object* p)
        throws AdapterNotFoundException, AdapterAlreadyActiveException, InvalidReplicaGroupIdException;

    /**
     *
     * Set the process proxy for a server.
     *
     * @param id The server id.
     *
     * @param proxy The process proxy.
     *
     * @throws ServerNotFoundException Raised if the server cannot
     * be found.
     *
     **/
    ["amd"] idempotent void setServerProcessProxy(string id, Process* proxy)
        throws ServerNotFoundException;
};

};

