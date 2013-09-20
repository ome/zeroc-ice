﻿// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

#include "App.g.h"

namespace chat
{
        /// <summary>
        /// Provides application-specific behavior to supplement the default Application class.
        /// </summary>
        ref class App sealed
        {
        public:
                App();
                virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ pArgs) override;

        private:
                void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);
        };
}
