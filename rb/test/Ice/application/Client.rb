#!/usr/bin/env ruby
# **********************************************************************
#
# Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

require 'Ice'

class Client < Ice::Application
    def interruptCallback(sig)
        puts "handling signal " + sig
    end

    def run(args)
        Ice::Application::ignoreInterrupt
        puts "Ignore CTRL+C and the like for 5 seconds (try it!)"
        sleep(5)

        Ice::Application::callbackOnInterrupt

        Ice::Application::holdInterrupt
        puts "Hold CTRL+C and the like for 5 seconds (try it!)"
        sleep(5)

        Ice::Application::releaseInterrupt
        puts "Release CTRL+C (any held signals should be released)"
        sleep(5)

        Ice::Application::holdInterrupt
        puts "Hold CTRL+C and the like for 5 seconds (try it!)"
        sleep(5)

        Ice::Application::callbackOnInterrupt
        puts "Release CTRL+C (any held signals should be released)"
        sleep(5)

        puts "ok"
        return true
    end
end

app = Client.new()
exit(app.main(ARGV))
