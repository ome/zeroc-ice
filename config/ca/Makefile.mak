# **********************************************************************
#
# Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

top_srcdir	= ..\..

!include $(top_srcdir)/config/Make.rules.mak

CA_FILES =  initca.py \
	    req.py \
	    cautil.py  \
	    import.py \
	    sign.py \
	    ImportKey.class

install::
	@if not exist $(prefix)\config\ca \
	    @echo "Creating $(prefix)\config\ca..." & \
	    mkdir $(prefix)\config\ca
	@for %i in ( $(CA_FILES) ) do \
	    @echo "Installing %i" & \
	    copy %i $(prefix)\config\ca
	copy README $(prefix)\config\ca
