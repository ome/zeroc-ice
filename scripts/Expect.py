# **********************************************************************
#
# Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

import threading
import subprocess
import string
import time
import re
import traceback
import sys
import os
import signal
import sys

__all__ = ["Expect", "EOF", "TIMEOUT" ]

win32 = (sys.platform == "win32")
if win32:
    # We use this to remove the reliance on win32api. Unfortunately,
    # python 2.5 under 64 bit versions of windows doesn't have ctypes,
    # hence we have to be prepared for that module not to be present.
    try:
        import ctypes
    except ImportError:
        pass

class EOF:
    """Raised when EOF is read from a child.
    """
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return str(self.value)

class TIMEOUT(Exception):
    """Raised when a read time exceeds the timeout.
    """
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return str(self.value)

def getStringIO():
    if sys.version_info[0] == 2:
        import StringIO
        return StringIO.StringIO()
    else:
        import io
        return io.StringIO()

def escape(s, escapeNewlines = True):
    if s == TIMEOUT:
        return "<TIMEOUT>"
    o = getStringIO()
    for c in s:
        if c == '\\':
            o.write('\\\\')
        elif c == '\'':
            o.write("\\'")
        elif c == '\"':
            o.write('\\"')
        elif c == '\b':
            o.write('\\b')
        elif c == '\f':
            o.write('\\f')
        elif c == '\n':
            if escapeNewlines:
                o.write('\\n')
            else:
                o.write('\n')
        elif c == '\r':
            o.write('\\r')
        elif c == '\t':
            o.write('\\t')
        else:
            if c in string.printable:
                o.write(c)
            else:
                o.write('\\%03o' % ord(c))
    return o.getvalue()

class reader(threading.Thread):
    def __init__(self, desc, p, logfile):
        self.desc = desc
        self.buf = getStringIO()
        self.cv = threading.Condition()
        self.p = p
        self._trace = False
        self._tbuf = getStringIO()
        self._tracesuppress = None
        self.logfile = logfile
        threading.Thread.__init__(self)

    def run(self):
        try:
            while True:
                c = self.p.stdout.read(1)
                if not c: break
                if c == '\r': continue

                self.cv.acquire()
                try:
                    # Depending on Python version and platform, the value c could be a
                    # string or a bytes object.
                    if type(c) != str:
                        c = c.decode()
                    self.trace(c)
                    self.buf.write(c)
                    self.cv.notify()
                finally:
                    self.cv.release()
        except IOError as e:
            print(e)

    def trace(self, c):
        if self._trace:
            if self._tracesuppress:
                self._tbuf.write(c)
                if c == '\n':
                    content = self._tbuf.getvalue()
                    suppress = False
                    for p in self._tracesuppress:
                        if p.search(content):
                            suppress = True
                            break
                    if not suppress:
                        sys.stdout.write(content)
                    self._tbuf.truncate(0)
                    self._tbuf.seek(0)
            else:
                sys.stdout.write(c)
                sys.stdout.flush()

    def enabletrace(self, suppress = None):
        self.cv.acquire()
        try:
            if not self._trace:
                self._trace = True
                self._tracesuppress = suppress
                for c in self.buf.getvalue():
                    self.trace(c)
        finally:
            self.cv.release()

    def getbuf(self):
        self.cv.acquire()
        try:
            buf = self.buf.getvalue()
        finally:
            self.cv.release()
        return buf

    def match(self, pattern, timeout, matchall = False):
        """pattern is a list of string, regexp duples.
        """

        if timeout is not None:
            end = time.time() + timeout
        start = time.time()

        # Trace the match
        if self.logfile:
            if timeout is None:
                tdesc = "<infinite>"
            else:
                tdesc = "%.2fs" % timeout
            p = [ escape(s) for (s, r) in pattern ]
            pdesc = getStringIO()
            if len(p) == 1:
                pdesc.write(escape(p[0]))
            else:
                pdesc.write('[');
                for pat in p:
                    if pat != p[0]:
                        pdesc.write(',');
                    pdesc.write(escape(pat))
                pdesc.write(']');
            self.logfile.write('%s: expect: "%s" timeout: %s\n' % (self.desc, pdesc.getvalue(), tdesc))
            self.logfile.flush()

        maxend = None
        self.cv.acquire()
        try:
            try: # This second try/except block is necessary because of python 2.3
                while True:
                    buf = self.buf.getvalue()

                    # Try to match on the current buffer.
                    olen = len(pattern)
                    for index, p in enumerate(pattern):
                        s, regexp = p
                        if s == TIMEOUT:
                            continue
                        m = regexp.search(buf)
                        if m is not None:
                            before = buf[:m.start()]
                            matched = buf[m.start():m.end()]
                            after = buf[m.end():]

                            if maxend is None or m.end() > maxend:
                                maxend = m.end()

                            # Trace the match
                            if self.logfile:
                                if len(pattern) > 1:
                                    self.logfile.write('%s: match found in %.2fs.\npattern: "%s"\nbuffer: "%s||%s||%s"\n'%
                                                       (self.desc, time.time() - start, escape(s), escape(before),
                                                        escape(matched), escape(after)))
                                else:
                                    self.logfile.write('%s: match found in %.2fs.\nbuffer: "%s||%s||%s"\n' %
                                                       (self.desc, time.time() - start, escape(before), escape(matched),
                                                        escape(after)))

                            if matchall:
                                del pattern[index]
                                # If all patterns have been found then
                                # truncate the buffer to the longest match,
                                # and then return.
                                if len(pattern) == 0:
                                    self.buf.truncate(0)
                                    self.buf.seek(0)
                                    self.buf.write(buf[maxend:])
                                    return buf
                                break

                            # Consume matched portion of the buffer.
                            self.buf.truncate(0)
                            self.buf.seek(0)
                            self.buf.write(after)

                            return buf, before, after, m, index

                    # If a single match was found then the match.
                    if len(pattern) != olen:
                        continue

                    if timeout is None:
                        self.cv.wait()
                    else:
                        self.cv.wait(end - time.time())
                        if time.time() >= end:
                            # Log the failure
                            if self.logfile:
                                self.logfile.write('%s: match failed.\npattern: "%s"\nbuffer: "%s"\n"' %
                                                   (self.desc, escape(s), escape(buf)))
                                self.logfile.flush()
                            raise TIMEOUT ('timeout exceeded in match\npattern: "%s"\nbuffer: "%s"\n' %
                                           (escape(s), escape(buf, False)))
            except TIMEOUT as e:
                if (TIMEOUT, None) in pattern:
                    return buf, buf, TIMEOUT, None, pattern.index((TIMEOUT, None))
                raise e
        finally:
            self.cv.release()

def splitCommand(command_line):
    arg_list = []
    arg = ''

    state_basic = 0
    state_esc = 1
    state_singlequote = 2
    state_doublequote = 3
    state_whitespace = 4
    state = state_basic
    pre_esc_state = state_basic

    for c in command_line:
        if state != state_esc and c == '\\':
            pre_esc_state = state
            state = state_esc
        elif state == state_basic or state == state_whitespace:
            if c == r"'":
                state = state_singlequote
            elif c == r'"':
                state = state_doublequote
            elif c.isspace():
                if state == state_whitespace:
                    None
                else:
                    arg_list.append(arg)
                    arg = ''
                    state = state_whitespace
            else:
                arg = arg + c
                state = state_basic
        elif state == state_esc:
            arg = arg + c
            state = pre_esc_state
        elif state == state_singlequote:
            if c == r"'":
                state = state_basic
            else:
                arg = arg + c
        elif state == state_doublequote:
            if c == r'"':
                state = state_basic
            else:
                arg = arg + c

    if arg != '':
        arg_list.append(arg)

    return arg_list

class Expect (object):
    def __init__(self, command, startReader = True, timeout=30, logfile=None, mapping = None, desc = None, cwd = None, env = None):
        self.buf = "" # The part before the match
        self.before = "" # The part before the match
        self.after = "" # The part after the match
        self.matchindex = 0 # the index of the matched pattern
        self.match = None # The last match
        self.mapping = mapping # The mapping of the test.
        self.exitstatus = None # The exitstatus, either -signal or, if positive, the exit code.
        self.killed = None # If killed, the signal that was sent.
        self.desc = desc
        self.logfile = logfile
        self.timeout = timeout
        self.p = None

        if self.logfile:
            self.logfile.write('spawn: "%s"\n' % command)
            self.logfile.flush()

        if win32:
            # Don't rely on win32api
            #import win32process
            #creationflags = win32process.CREATE_NEW_PROCESS_GROUP)
            #
            # universal_newlines = True is necessary for Python 3 on Windows
            #
            # We can't use shell=True because terminate() wouldn't
            # work. This means the PATH isn't searched for the
            # command.
            #
            CREATE_NEW_PROCESS_GROUP = 512
            self.p = subprocess.Popen(command, env = env, cwd = cwd, shell=False, bufsize=0, stdin=subprocess.PIPE,
                                      stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                      creationflags = CREATE_NEW_PROCESS_GROUP, universal_newlines=True)
        else:
            self.p = subprocess.Popen(splitCommand(command), env = env, cwd = cwd, shell=False, bufsize=0,
                                      stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        self.r = reader(desc, self.p, logfile)

        # The thread is marked as a daemon thread. This is done so that if
        # an expect script runs off the end of main without kill/wait on each
        # spawned process the script will not hang tring to join with the
        # reader thread. Instead __del__ (below) will be called which
        # terminates and joins with the reader thread.
        self.r.setDaemon(True)

        if startReader:
            self.startReader()

    def startReader(self):
        self.r.start()

    def __del__(self):
        # Terminate and clean up.
        if self.p is not None:
            self.terminate()

    def expect(self, pattern, timeout = 20):
        """pattern is either a string, or a list of string regexp patterns.

           timeout == None expect can block indefinitely.

           timeout == -1 then the default is used.
        """
        if timeout == -1:
            timeout = self.timeout

        if type(pattern) != list:
            pattern = [ pattern ]
        def compile(s):
            if type(s) == str:
                return re.compile(s, re.S)
            return None
        pattern = [ ( p, compile(p) ) for p in pattern ]
        try:
            self.buf, self.before, self.after, self.match, self.matchindex = self.r.match(pattern, timeout)
        except TIMEOUT as e:
            self.buf = ""
            self.before = ""
            self.after = ""
            self.match = None
            self.matchindex = 0
            raise e
        return self.matchindex

    def expectall(self, pattern, timeout = 10):
        """pattern is a list of string regexp patterns.

           timeout == None expect can block indefinitely.

           timeout == -1 then the default is used.
        """
        if timeout == -1:
            timeout = self.timeout

        pattern = [ ( p, re.compile(p, re.S) ) for p in pattern ]
        try:
            self.buf = self.r.match(pattern, timeout, matchall = True)
            self.before = ""
            self.after = ""
            self.matchindex = 0
            self.match = None
        except TIMEOUT as e:
            self.buf = ""
            self.before = ""
            self.after = ""
            self.matchindex = 0
            self.match = None
            raise e

    def sendline(self, data):
        """send data to the application.
        """
        if self.logfile:
            self.logfile.write('%s: sendline: "%s"\n' % (self.desc, escape(data)))
            self.logfile.flush()
        data = data + "\n"
        if win32 or sys.version_info[0] == 2:
            self.p.stdin.write(data)
        else:
            self.p.stdin.write(data.encode("utf-8"))

    def wait(self, timeout = None):
        """Wait for the application to terminate for up to timeout seconds, or
           raises a TIMEOUT exception. If timeout is None, the wait is
           indefinite.

           The exit status is returned. A negative exit status means
           the application was killed by a signal.
        """
        if self.p is not None:

            # Unfortunately, with the subprocess module there is no
            # better method of doing a timed wait.
            if timeout is not None:
                end = time.time() + timeout
                while time.time() < end and self.p.poll() is None:
                    time.sleep(0.1)
                if self.p.poll() is None:
                    raise TIMEOUT ('timedwait exceeded timeout')

            self.exitstatus = self.p.wait()

            # A Windows application killed with CTRL_BREAK. Fudge the exit status.
            if win32 and self.exitstatus != 0 and self.killed is not None:
                self.exitstatus = -self.killed
            self.p = None
            self.r.join()
            # Simulate a match on EOF
            self.buf = self.r.getbuf()
            self.before = self.buf
            self.after = ""
            self.r = None
        return self.exitstatus

    def terminate(self):
        """Terminate the process."""
        # First try to break the app. Don't bother if this is win32
        # and we're using java. It won't break (BREAK causes a stack
        # trace).
        if self.hasInterruptSupport():
            try:
                if win32:
                    # We BREAK since CTRL_C doesn't work (the only way to make
                    # that work is with remote code injection).
                    #
                    # Using the ctypes module removes the reliance on the
                    # python win32api
                    try:
                        #win32console.GenerateConsoleCtrlEvent(win32console.CTRL_BREAK_EVENT, self.p.pid)
                        ctypes.windll.kernel32.GenerateConsoleCtrlEvent(1, self.p.pid) # 1 is CTRL_BREAK_EVENT
                    except NameError:
                        pass
                else:
                   os.kill(self.p.pid, signal.SIGINT)
            except:
                traceback.print_exc(file=sys.stdout)

            # If the break does not terminate the process within 5
            # seconds, then terminate the process.
            try:
                self.wait(timeout = 5)
                return
            except TIMEOUT as e:
                pass

        try:
            if win32:
                # Next kill the app.
                if self.hasInterruptSupport():
                    print("%s: did not respond to break. terminating: %d" % (self.desc, self.p.pid))
                self.p.terminate()
            else:
               os.kill(self.p.pid, signal.SIGKILL)
            self.wait()
        except:
            traceback.print_exc(file=sys.stdout)

    def kill(self, sig):
        """Send the signal to the process."""
        self.killed = sig # Save the sent signal.
        if win32:
            # Signals under windows are all turned into CTRL_BREAK_EVENT,
            # except with Java since CTRL_BREAK_EVENT generates a stack
            # trace.
            #
            # We BREAK since CTRL_C doesn't work (the only way to make
            # that work is with remote code injection).
            if self.hasInterruptSupport():
                try:
                    #
                    # Using the ctypes module removes the reliance on the
                    # python win32api
                    try:
                        #win32console.GenerateConsoleCtrlEvent(win32console.CTRL_BREAK_EVENT, self.p.pid)
                        ctypes.windll.kernel32.GenerateConsoleCtrlEvent(1, self.p.pid) # 1 is CTRL_BREAK_EVENT
                    except NameError:
                        pass
                except:
                    traceback.print_exc(file=sys.stdout)
            else:
                self.p.terminate()
        else:
            os.kill(self.p.pid, sig)

    # status == 0 is normal exit status for C++
    #
    # status == 130 is normal exit status for a Java app that was
    # SIGINT interrupted.
    #
    def waitTestSuccess(self, exitstatus = 0, timeout = None):
        """Wait for the process to terminate for up to timeout seconds, and
           validate the exit status is as expected."""

        def test(result, expected):
            if expected != result:
                print("unexpected exit status: expected: %d, got %d" % (expected, result))
                assert False

        self.wait(timeout)
        if self.mapping == "java":
            if self.killed is not None:
                if win32:
                    test(self.exitstatus, -self.killed)
                else:
                    if self.killed == signal.SIGINT:
                        test(130, self.exitstatus)
                    else:
                        assert False
            else:
                assert self.exitstatus == exitstatus
        else:
            test(self.exitstatus, exitstatus)

    def waitTestFail(self, timeout = None):
        """Wait for the process to terminate for up to timeout seconds, and
           validate the exit status is as expected."""

        self.wait(timeout)
        if self.exitstatus == 0:
            print("unexpected non-zero exit status")
            assert False

    def trace(self, suppress = None):
        self.r.enabletrace(suppress)

    def hasInterruptSupport(self):
        """Return True if the application gracefully terminated, False otherwise."""
        if win32 and self.mapping == "java":
            return False
        return True
