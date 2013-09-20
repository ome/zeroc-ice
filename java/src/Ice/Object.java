// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package Ice;

/**
 * The base interface for servants.
 **/
public interface Object
{
    /**
     * Returns a copy of the object. The cloned object contains field-for-field copies
     * of the state.
     *
     * @return The cloned object.
     **/
    java.lang.Object clone() throws java.lang.CloneNotSupportedException;

    /**
     * Tests whether this object supports a specific Slice interface.
     *
     * @param s The type ID of the Slice interface to test against.
     * @return <code>true</code> if this object has the interface
     * specified by <code>s</code> or derives from the interface
     * specified by <code>s</code>.
     **/
    boolean ice_isA(String s);

    /**
     * Tests whether this object supports a specific Slice interface.
     *
     * @param s The type ID of the Slice interface to test against.
     * @param current The {@link Current} object for the invocation.
     * @return <code>true</code> if this object has the interface
     * specified by <code>s</code> or derives from the interface
     * specified by <code>s</code>.
     **/
    boolean ice_isA(String s, Current current);

    /**
     * Tests whether this object can be reached.
     **/
    void ice_ping();

    /**
     * Tests whether this object can be reached.
     *
     * @param current The {@link Current} object for the invocation.
     **/
    void ice_ping(Current current);

    /**
     * Returns the Slice type IDs of the interfaces supported by this object.
     *
     * @return The Slice type IDs of the interfaces supported by this object, in base-to-derived
     * order. The first element of the returned array is always <code>::Ice::Object</code>.
     **/
    String[] ice_ids();

    /**
     * Returns the Slice type IDs of the interfaces supported by this object.
     *
     * @param current The {@link Current} object for the invocation.
     * @return The Slice type IDs of the interfaces supported by this object, in base-to-derived
     * order. The first element of the returned array is always <code>::Ice::Object</code>.
     **/
    String[] ice_ids(Current current);

    /**
     * Returns the Slice type ID of the most-derived interface supported by this object.
     *
     * @return The Slice type ID of the most-derived interface.
     **/
    String ice_id();

    /**
     * Returns the Slice type ID of the most-derived interface supported by this object.
     *
     * @param current The {@link Current} object for the invocation.
     * @return The Slice type ID of the most-derived interface.
     **/
    String ice_id(Current current);

    /**
     * Returns the Freeze metadata attributes for an operation.
     *
     * @param The name of the operation.
     * @return The least significant bit indicates whether the operation is a read
     * or write operation. If the bit is set, the operation is a write operation.
     * The expression <code>ice_operationAttributes("op") & 0x1</code> is true if
     * the operation has a <code>["freeze:write"]</code> metadata directive.
     * <p>
     * The second- and third least significant bit indicate the transactional mode
     * of the operation. The expression <code>ice_operationAttributes("op") & 0x6 >> 1</code>
     * indicates the transactional mode as follows:
     * <dl>
     *   <dt>0</dt>
     *   <dd><code>["freeze:read:supports"]</code></dd>
     *   <dt>1</dt>
     *   <dd><code>["freeze:read:mandatory"]</code> or <code>["freeze:write:mandatory"]</code></dd>
     *   <dt>2</dt>
     *   <dd><code>["freeze:read:required"]</code> or <code>["freeze:write:required"]</code></dd>
     *   <dt>3</dt>
     *   <dd><code>["freeze:read:never"]</code></dd>
     * </dl>
     *
     * @see Freeze.TransactionalEvictor
     **/
    int ice_operationAttributes(String operation);

    /**
     * The Ice run time invokes this method prior to marshaling an object's data members. This allows a subclass
     * to override this method in order to validate its data members.
     **/
    void ice_preMarshal();

    /**
     * The Ice run time invokes this method vafter unmarshaling an object's data members. This allows a
     * subclass to override this method in order to perform additional initialization.
     **/
    void ice_postUnmarshal();

    /**
     * Dispatches an invocation to a servant. This method is used by dispatch interceptors to forward an invocation
     * to a servant (or to another interceptor).
     *
     * @param request The details of the invocation.
     * @param cb The callback object for asynchronous dispatch. For synchronous dispatch, the callback object
     * must be <code>null</code>.
     * @return The dispatch status for the operation.
     *
     * @see DispatchInterceptor
     * @see DispatchInterceptorAsyncCallback
     * @see DispatchStatus
     **/
    DispatchStatus ice_dispatch(Request request, DispatchInterceptorAsyncCallback cb);

    /**
     * Dispatches an invocation to a servant. This method is used by dispatch interceptors to forward an invocation
     * to a servant (or to another interceptor).
     *
     * @param request The details of the invocation.
     * @return The dispatch status for the operation.
     *
     * @see DispatchInterceptor
     * @see DispatchStatus
     **/
    DispatchStatus ice_dispatch(Request request);

    DispatchStatus __dispatch(IceInternal.Incoming in, Current current);

    DispatchStatus __collocDispatch(IceInternal.Direct request);

    void __write(IceInternal.BasicStream __os);
    void __read(IceInternal.BasicStream __is);
   
    void __write(OutputStream __outS);
    void __read(InputStream __inS);
}
