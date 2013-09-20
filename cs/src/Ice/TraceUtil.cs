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

    using System.Collections.Generic;
    using System.Diagnostics;
    using System.Globalization;

    sealed class TraceUtil
    {
        internal static void traceSend(BasicStream str, Ice.Logger logger, TraceLevels tl)
        {
            if(tl.protocol >= 1)
            {
                int p = str.pos();
                str.pos(0);

                using(System.IO.StringWriter s = new System.IO.StringWriter(CultureInfo.CurrentCulture))
                {
                    byte type = printMessage(s, str);

                    logger.trace(tl.protocolCat, "sending " + getMessageTypeAsString(type) + " " + s.ToString());
                }
                str.pos(p);
            }
        }

        internal static void traceRecv(BasicStream str, Ice.Logger logger, TraceLevels tl)
        {
            if(tl.protocol >= 1)
            {
                int p = str.pos();
                str.pos(0);

                using(System.IO.StringWriter s = new System.IO.StringWriter(CultureInfo.CurrentCulture))
                {
                    byte type = printMessage(s, str);

                    logger.trace(tl.protocolCat, "received " + getMessageTypeAsString(type) + " " + s.ToString());
                }
                str.pos(p);
            }
        }

        internal static void trace(string heading, BasicStream str, Ice.Logger logger, TraceLevels tl)
        {
            if(tl.protocol >= 1)
            {
                int p = str.pos();
                str.pos(0);

                using(System.IO.StringWriter s = new System.IO.StringWriter(CultureInfo.CurrentCulture))
                {
                    s.Write(heading);
                    printMessage(s, str);

                    logger.trace(tl.protocolCat, s.ToString());
                }
                str.pos(p);
            }
        }

        private static HashSet<string> slicingIds = new HashSet<string>();

        internal static void traceSlicing(string kind, string typeId, string slicingCat, Ice.Logger logger)
        {
            lock(typeof(IceInternal.TraceUtil))
            {
                if(slicingIds.Add(typeId))
                {
                    using(System.IO.StringWriter s = new System.IO.StringWriter(CultureInfo.CurrentCulture))
                    {
                        s.Write("unknown " + kind + " type `" + typeId + "'");
                        logger.trace(slicingCat, s.ToString());
                    }
                }
            }
        }

        public static void dumpStream(BasicStream stream)
        {       
            int pos = stream.pos();
            stream.pos(0);

            byte[] data = new byte[stream.size()];
            stream.readBlob(data);
            dumpOctets(data);

            stream.pos(pos);
        }

        public static void dumpOctets(byte[] data)
        {
            const int inc = 8;

            for(int i = 0; i < data.Length; i += inc)
            {
                for(int j = i; j - i < inc; j++)
                {
                    if(j < data.Length)
                    {
                        int n = (int)data[j];
                        if(n < 0)
                        {
                            n += 256;
                        }
                        string s;
                        if(n < 10)
                        {
                            s = "  " + n;
                        }
                        else if(n < 100)
                        {
                            s = " " + n;
                        }
                        else
                        {
                            s = "" + n;
                        }
                        System.Console.Out.Write(s + " ");
                    }
                    else
                    {
                        System.Console.Out.Write("    ");
                    }
                }

                System.Console.Out.Write('"');

                for(int j = i; j < data.Length && j - i < inc; j++)
                {
                    // TODO: this needs fixing
                    if(data[j] >= (byte)32 && data[j] < (byte)127)
                    {
                        System.Console.Out.Write((char) data[j]);
                    }
                    else
                    {
                        System.Console.Out.Write('.');
                    }
                }

                System.Console.Out.WriteLine('"');
            }
        }

        private static void printIdentityFacetOperation(System.IO.StringWriter s, BasicStream str)
        {
            try
            {
                Ice.Identity identity = new Ice.Identity();
                identity.read__(str);
                s.Write("\nidentity = " + str.instance().identityToString(identity));

                string[] facet = str.readStringSeq();
                s.Write("\nfacet = ");
                if(facet.Length > 0)
                {
                    s.Write(IceUtilInternal.StringUtil.escapeString(facet[0], ""));
                }

                string operation = str.readString();
                s.Write("\noperation = " + operation);
            }
            catch(System.IO.IOException)
            {
                Debug.Assert(false);
            }
        }

        private static void printRequest(System.IO.StringWriter s, BasicStream str)
        {
            int requestId = str.readInt();
            s.Write("\nrequest id = " + requestId);
            if(requestId == 0)
            {
                s.Write(" (oneway)");
            }

            printRequestHeader(s, str);
        }

        private static void printBatchRequest(System.IO.StringWriter s, BasicStream str)
        {
            int batchRequestNum = str.readInt();
            s.Write("\nnumber of requests = " + batchRequestNum);

            for(int i = 0; i < batchRequestNum; ++i)
            {
                s.Write("\nrequest #" + i + ':');
                printRequestHeader(s, str);
            }
        }

        private static void printReply(System.IO.StringWriter s, BasicStream str)
        {
            int requestId = str.readInt();
            s.Write("\nrequest id = " + requestId);

            byte replyStatus = str.readByte();
            s.Write("\nreply status = " + (int)replyStatus + ' ');

            switch(replyStatus)
            {
            case ReplyStatus.replyOK: 
            {
                s.Write("(ok)");
                break;
            }

            case ReplyStatus.replyUserException: 
            {
                s.Write("(user exception)");
                break;
            }

            case ReplyStatus.replyObjectNotExist: 
            case ReplyStatus.replyFacetNotExist: 
            case ReplyStatus.replyOperationNotExist: 
            {
                switch(replyStatus)
                {
                case ReplyStatus.replyObjectNotExist: 
                {
                    s.Write("(object not exist)");
                    break;
                }

                case ReplyStatus.replyFacetNotExist: 
                {
                    s.Write("(facet not exist)");
                    break;
                }

                case ReplyStatus.replyOperationNotExist: 
                {
                    s.Write("(operation not exist)");
                    break;
                }

                default: 
                {
                    Debug.Assert(false);
                    break;
                }
                }

                printIdentityFacetOperation(s, str);
                break;
            }

            case ReplyStatus.replyUnknownException: 
            case ReplyStatus.replyUnknownLocalException: 
            case ReplyStatus.replyUnknownUserException: 
            {
                switch(replyStatus)
                {
                case ReplyStatus.replyUnknownException: 
                {
                    s.Write("(unknown exception)");
                    break;
                }

                case ReplyStatus.replyUnknownLocalException: 
                {
                    s.Write("(unknown local exception)");
                    break;
                }

                case ReplyStatus.replyUnknownUserException: 
                {
                    s.Write("(unknown user exception)");
                    break;
                }

                default: 
                {
                    Debug.Assert(false);
                    break;
                }
                }

                string unknown = str.readString();
                s.Write("\nunknown = " + unknown);
                break;
            }

            default: 
            {
                s.Write("(unknown)");
                break;
            }
            }
        }

        private static void printRequestHeader(System.IO.StringWriter s, BasicStream str)
        {
            printIdentityFacetOperation(s, str);

            try
            {
                byte mode = str.readByte();
                s.Write("\nmode = " + (int)mode + ' ');
                switch((Ice.OperationMode)mode)
                {
                case Ice.OperationMode.Normal:
                {
                    s.Write("(normal)");
                    break;
                }

                case Ice.OperationMode.Nonmutating:
                {
                    s.Write("(nonmutating)");
                    break;
                }

                case Ice.OperationMode.Idempotent:
                {
                    s.Write("(idempotent)");
                    break;
                }

                default:
                {
                    s.Write("(unknown)");
                    break;
                }
                }

                int sz = str.readSize();
                s.Write("\ncontext = ");
                while(sz-- > 0)
                {
                    string key = str.readString();
                    string val = str.readString();
                    s.Write(key + '/' + val);
                    if(sz > 0)
                    {
                        s.Write(", ");
                    }
                }

                Ice.EncodingVersion v = str.skipEncaps();
                if(!v.Equals(Ice.Util.Encoding_1_0))
                {
                    s.Write("\nencoding = ");
                    s.Write(Ice.Util.encodingVersionToString(v));
                }
            }
            catch(System.IO.IOException)
            {
                Debug.Assert(false);
            }
        }

        private static byte printHeader(System.IO.StringWriter s, BasicStream str)
        {
            try
            {
                str.readByte(); // Don't bother printing the magic number
                str.readByte();
                str.readByte();
                str.readByte();

                /* byte pMajor = */ str.readByte();
                /* byte pMinor = */ str.readByte();
                //s.Write("\nprotocol version = " + (int)pMajor + "." + (int)pMinor);

                /* byte eMajor = */ str.readByte();
                /* byte eMinor = */ str.readByte();
                //s.Write("\nencoding version = " + (int)eMajor + "." + (int)eMinor);

                byte type = str.readByte();
                s.Write("\nmessage type = " + (int)type + " (" + getMessageTypeAsString(type) + ')');

                byte compress = str.readByte();
                s.Write("\ncompression status = " + (int)compress + ' ');
                switch(compress)
                {
                case (byte)0: 
                {
                    s.Write("(not compressed; do not compress response, if any)");
                    break;
                }

                case (byte)1: 
                {
                    s.Write("(not compressed; compress response, if any)");
                    break;
                }

                case (byte)2: 
                {
                    s.Write("(compressed; compress response, if any)");
                    break;
                }

                default: 
                {
                    s.Write("(unknown)");
                    break;
                }
                }

                int size = str.readInt();
                s.Write("\nmessage size = " + size);
                return type;
            }
            catch(System.IO.IOException)
            {
                Debug.Assert(false);
                return 0;
            }
        }

        private static byte printMessage(System.IO.StringWriter s, BasicStream str)
        {
            byte type = printHeader(s, str);

            switch(type)
            {
            case Protocol.closeConnectionMsg: 
            case Protocol.validateConnectionMsg: 
            {
                // We're done.
                break;
            }

            case Protocol.requestMsg: 
            {
                printRequest(s, str);
                break;
            }

            case Protocol.requestBatchMsg: 
            {
                printBatchRequest(s, str);
                break;
            }

            case Protocol.replyMsg: 
            {
                printReply(s, str);
                break;
            }

            default: 
            {
                s.Write("(unknown)");
                break;
            }
            }

            return type;
        }

        internal static void traceHeader(string heading, BasicStream str, Ice.Logger logger, TraceLevels tl)
        {
            if(tl.protocol >= 1)
            {
                int p = str.pos();
                str.pos(0);

                using(System.IO.StringWriter s = new System.IO.StringWriter(CultureInfo.CurrentCulture))
                {
                    s.Write(heading);
                    printHeader(s, str);

                    logger.trace(tl.protocolCat, s.ToString());
                }
                str.pos(p);
            }
        }

        private static string getMessageTypeAsString(byte type)
        {   
            switch(type)
            {
            case Protocol.requestMsg:
                return "request";
            case Protocol.requestBatchMsg:
                return "batch request";
            case Protocol.replyMsg:
                return "reply";
            case Protocol.closeConnectionMsg:
                return "close connection";
            case Protocol.validateConnectionMsg:
                return  "validate connection";
            default:
                return "unknown";
            }
        }
    }

}
