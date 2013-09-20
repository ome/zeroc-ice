// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

namespace IceInternal
{
    public sealed class ProcessI : Ice.ProcessDisp_
    {
        public ProcessI(Ice.Communicator communicator)
        {
            _communicator = communicator;
        }

        public override void shutdown(Ice.Current current)
        {
            _communicator.shutdown();
        }
        
        public override void writeMessage(string message, int fd, Ice.Current current)
        {
            switch(fd)
            {
                case 1:
                {
                    System.Console.Out.WriteLine(message);
                    break;
                }
                case 2:
                {
                    System.Console.Error.WriteLine(message);
                    break;
                }
            }
        }   
        
        private Ice.Communicator _communicator;
    }
}
