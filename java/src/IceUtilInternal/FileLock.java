// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package IceUtilInternal;

import java.io.File;
import java.io.RandomAccessFile;
import java.io.FileWriter;
import java.nio.channels.FileChannel;
import java.nio.channels.OverlappingFileLockException;
import java.lang.management.ManagementFactory;

public final class FileLock
{
    //
    // The constructor opens the given file (eventually creating it)
    // and acquires a lock on the file or throws FileLockException if
    // the file couldn't be locked.
    //
    // If the lock can be acquired, the Java VM name is written to the
    // file.
    //
    public FileLock(String path)
    {
        _file = new File(path);

        FileChannel channel;
        try
        {
            _randFile = new RandomAccessFile(_file, "rw");
            channel = _randFile.getChannel();
        }
        catch(java.io.FileNotFoundException e)
        {
            throw new IceUtil.FileLockException(path);
        }
        
        java.nio.channels.FileLock lock;
        try
        {
            lock = channel.tryLock();
        }
        catch(Exception ex)
        {
            throw new IceUtil.FileLockException(path, ex);
        }
        
        if(lock == null)
        {
            throw new IceUtil.FileLockException(path);
        }

        //
        // In Windows we don't write the process pid to the file, as is  not posible
        // to read the file from other process while it is locked here.
        //
        if(!System.getProperty("os.name").startsWith("Windows"))
        {
            try
            {
                //
                // Java doesn't provide get pid operation. This code
                // writes the Java VM name instead of the pid.
                //
                // The output is JVM dependent. With the Sun
                // implementation it's `pid@hostname'
                //
                _randFile.writeUTF(ManagementFactory.getRuntimeMXBean().getName());

                //
                // Don't close _randFile here or the lock will be released. It is called
                // during release see comments there.
                //
            }
            catch(java.io.IOException ex)
            {
                release();
                throw new IceUtil.FileLockException(path);
            }
        }
    }

    //
    // Remove the lock if it is owned by the class instance.
    //
    public void release()
    {
        if(System.getProperty("os.name").startsWith("Windows"))
        {
            if(_randFile != null)
            {
                //
                // In Windows we need to close the file handler before
                // we try to delete the file. Note that the call to close
                // also release the file lock.
                //
                try
                {
                    _randFile.close();
                }
                catch(java.io.IOException ex)
                {
                }
                _randFile = null;
            }
        }
        //
        // on UNIX the call to delete remove the file and that
        // release the lock.
        //
        // In Windows the call to delete will success if at that point
        // the file has not been opened by any process.
        //
        if(_file != null)
        {
            _file.delete();
            _file = null;
        }
    }

    //
    // We need to keep these refrences to delete the lock file during release
    //
    private File _file;
    private RandomAccessFile _randFile;

}
