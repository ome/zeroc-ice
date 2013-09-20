# **********************************************************************
#
# Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

#
# Select an installation base directory. The directory will be created
# if it does not exist.
#

prefix			?= /opt/Ice-$(VERSION)

#
# The default behavior of 'make install' is to install the Ice for .NET
# libraries in the 'bin' directory. If you would prefer to
# install these libraries in the GAC, set GACINSTALL to yes.
#

#GACINSTALL             = yes

#
# Ice invokes unmanaged code to implement the following features:
#
# - Protocol compression
# - Signal processing in the Ice.Application class (Windows only)
#
# Enable MANAGED below if you do not require these features and prefer that
# the Ice run time use only managed code.
#

#MANAGED		= yes

#
# Define DEBUG as yes if you want to build with debug information and
# assertions enabled.
#

DEBUG			= yes

#
# Define OPTIMIZE as yes if you want to build with optmization.
#

#OPTIMIZE		= yes

#
# Set the key file used to sign assemblies.
#

KEYFILE                 ?= $(top_srcdir)/../config/IceDevKey.snk

# ----------------------------------------------------------------------
# Don't change anything below this line!
# ----------------------------------------------------------------------

#
# Common definitions
#
ice_language = cs
slice_translator = slice2cs

ifeq ($(shell test -f $(top_srcdir)/config/Make.common.rules && echo 0),0)
    include $(top_srcdir)/config/Make.common.rules
else
    include $(top_srcdir)/../config/Make.common.rules
endif

DSEP = /

bindir = $(top_srcdir)/bin

assembliesdir           = $(top_srcdir)/Assemblies

install_bindir		    = $(prefix)/bin

install_assembliesdir   = $(prefix)/Assemblies

install_libdir		    = $(prefix)/lib


install_pkgconfigdir    = $(prefix)/lib/pkgconfig

ifeq ($(ice_dir),/usr)
    ref = -pkg:$(1)
else
    ifdef ice_src_dist
        ref = -r:$(assembliesdir)/$(1).dll
    else
        ifeq ($(shell test -d $(ice_dir)/lib/pkgconfig && echo 0),0)
            export PKG_CONFIG_PATH := $(ice_dir)/lib/pkgconfig:$(PKG_CONFIG_PATH)
            ref = -pkg:$(1)
        else
            ref = -r:$(ice_dir)/Assemblies/$(1).dll
        endif
    endif
endif

GACUTIL			= gacutil

# MDB files are generated only for debug builds. For debug, with a GAC
# install gacutil installs the .mdb into the GAC.
installmdb    = /bin/true

ifeq ($(GACINSTALL),yes)
    ifeq ($(GAC_ROOT),)
        installassembly = ([ -n "$(2)" ] && pkgopt="-package $(2)"; $(GACUTIL) -i $(1) -f $$pkgopt)
        installpolicy = $(GACUTIL) -i $(1).dll -f
    else
        installassembly = ([ -n "$(2)" ] && pkgopt="-package $(2)"; $(GACUTIL) -i $(1) -f $$pkgopt -root $(GAC_ROOT))
        installpolicy = $(GACUTIL) -i $(1).dll -f -root $(GAC_ROOT)
    endif
else
    installassembly 	= $(INSTALL_LIBRARY) $(1) $(install_assembliesdir); \
    			  chmod a+rx $(install_assembliesdir)/$(notdir $(1))
    installpolicy 	= $(INSTALL_LIBRARY) $(1).dll $(install_assembliesdir); \
                          $(INSTALL_LIBRARY) $(1) $(install_assembliesdir); \
    			  chmod a+rx $(install_assembliesdir)/$(notdir $(1).dll); \
    			  chmod a+r $(install_assembliesdir)/$(notdir $(1))
    ifeq ($(DEBUG),yes)
        installmdb      = $(INSTALL_LIBRARY) $(1) $(install_assembliesdir); \
                          chmod a+rx $(install_assembliesdir)/$(notdir $(1))
    endif
endif

#
# Do not generate policy files for beta (x.y.51) or minor (x.y.0) releases.
#
generate_policies = $(shell test $(VERSION_PATCH) -gt 0 -a $(VERSION_PATCH) -lt 51 && echo "yes")

ifneq ($(generate_policies),yes)
    installpolicy = /bin/true
endif

MCS			= gmcs

MCSFLAGS = -warnaserror

ifeq ($(DEBUG),yes)
    MCSFLAGS := $(MCSFLAGS) -debug -define:DEBUG
endif

ifeq ($(OPTIMIZE),yes)
    MCSFLAGS := $(MCSFLAGS) -optimize+
endif

ifdef ice_src_dist
    ifeq ($(ice_cpp_dir), $(ice_dir)/cpp)
        SLICE2CS 	= $(ice_cpp_dir)/bin/slice2cs
        SLICEPARSERLIB 	= $(ice_cpp_dir)/lib/$(call mklibfilename,Slice,$(VERSION))
    else
        SLICE2CS 	= $(ice_cpp_dir)/$(binsubdir)/slice2cs
        SLICEPARSERLIB 	= $(ice_cpp_dir)/$(libsubdir)/$(call mklibfilename,Slice,$(VERSION))
    endif
else
    SLICE2CS 		= $(ice_dir)/$(binsubdir)/slice2cs
    SLICEPARSERLIB 	= $(ice_dir)/$(libsubdir)/$(call mklibfilename,Slice,$(VERSION))
endif

AL              = al
POLICY          = policy.$(SHORT_VERSION).$(PKG)

ifeq ($(generate_policies),yes)

ifneq ($(PUBLIC_KEY_TOKEN),)
    publicKeyToken = $(PUBLIC_KEY_TOKEN)
else
    ifneq ($(ice_src_dist),)
	publicKeyToken = $(shell sn -q -p $(KEYFILE) tmp.pub; \
			   sn -q -t tmp.pub | sed 's/^.* //'; \
			   rm tmp.pub)
    else
	publicKeyToken = $(shell sn -q -T $(assembliesdir)/Ice.dll >tmp.pub; \
	                   sed 's/^.* //' <tmp.pub; \
			   rm tmp.pub)
    endif
endif

ifneq ($(POLICY_TARGET),)

$(assembliesdir)/$(POLICY_TARGET):
	@echo -e " \
<configuration> \n \
  <runtime> \n \
    <assemblyBinding xmlns=\"urn:schemas-microsoft-com:asm.v1\"> \n \
      <dependentAssembly> \n \
        <assemblyIdentity name=\"$(PKG)\" publicKeyToken=\"$(publicKeyToken)\" culture=\"\"/> \n \
        <publisherPolicy apply=\"yes\"/> \n \
        <bindingRedirect oldVersion=\"$(SHORT_VERSION).0.0 - $(SHORT_VERSION).1.0\" newVersion=\"$(VERSION).0\"/> \n \
      </dependentAssembly> \n \
    </assemblyBinding> \n \
  </runtime> \n \
</configuration>" >$(POLICY)
	$(AL) /link:$(POLICY) /version:0.0.0.0 /out:$(POLICY_TARGET) /keyfile:$(KEYFILE)
	chmod a+r $(POLICY)
	chmod a+rx $(POLICY_TARGET)
	mv $(POLICY) $(POLICY_TARGET) $(assembliesdir)

clean::
	-rm -f $(assembliesdir)/$(POLICY) $(assembliesdir)/$(POLICY_TARGET)

endif

endif

GEN_SRCS = $(subst .ice,.cs,$(addprefix $(GDIR)/,$(notdir $(SLICE_SRCS))))
CGEN_SRCS = $(subst .ice,.cs,$(addprefix $(GDIR)/,$(notdir $(SLICE_C_SRCS))))
SGEN_SRCS = $(subst .ice,.cs,$(addprefix $(GDIR)/,$(notdir $(SLICE_S_SRCS))))
GEN_AMD_SRCS = $(subst .ice,.cs,$(addprefix $(GDIR)/,$(notdir $(SLICE_AMD_SRCS))))
SAMD_GEN_SRCS = $(subst .ice,.cs,$(addprefix $(GDIR)/,$(notdir $(SLICE_SAMD_SRCS))))


EVERYTHING		= all depend clean install

.SUFFIXES:
.SUFFIXES:		.cs .ice

%.cs: %.ice
	$(SLICE2CS) $(SLICE2CSFLAGS) $<

$(GDIR)/%.cs: $(SDIR)/%.ice
	$(SLICE2CS) --output-dir $(GDIR) $(SLICE2CSFLAGS) $<

all:: $(TARGETS)

ifeq ($(generate_policies),yes)
    ifneq ($(POLICY_TARGET),)
all:: $(assembliesdir)/$(POLICY_TARGET)
    endif
endif

ifneq ($(TARGETS_CONFIG),)
all:: $(TARGETS_CONFIG)
endif

depend:: $(SLICE_SRCS) $(SLICE_C_SRCS) $(SLICE_S_SRCS) $(SLICE_AMD_SRCS) $(SLICE_SAMD_SRCS)
	-rm -f .depend .depend.mak
	if test -n "$(SLICE_SRCS)" ; then \
	    $(SLICE2CS) --depend $(SLICE2CSFLAGS) $(SLICE_SRCS) | $(ice_dir)/config/makedepend.py; \
	fi
	if test -n "$(SLICE_C_SRCS)" ; then \
	    $(SLICE2CS) --depend $(SLICE2CSFLAGS) $(SLICE_C_SRCS) | $(ice_dir)/config/makedepend.py; \
	fi
	if test -n "$(SLICE_S_SRCS)" ; then \
	    $(SLICE2CS) --depend $(SLICE2CSFLAGS) $(SLICE_S_SRCS) | $(ice_dir)/config/makedepend.py; \
	fi
	if test -n "$(SLICE_AMD_SRCS)" ; then \
	    $(SLICE2CS) --depend $(SLICE2CSFLAGS) $(SLICE_AMD_SRCS) | $(ice_dir)/config/makedepend.py; \
	fi
	if test -n "$(SLICE_SAMD_SRCS)" ; then \
	    $(SLICE2CS) --depend $(SLICE2CSFLAGS) $(SLICE_SAMD_SRCS) | $(ice_dir)/config/makedepend.py; \
	fi

clean::
	-rm -f $(TARGETS) $(patsubst %,%.mdb,$(TARGETS)) *.bak *.dll *.pdb *.mdb

ifneq ($(SLICE_SRCS),)
clean::
	-rm -f $(GEN_SRCS)
endif
ifneq ($(SLICE_C_SRCS),)
clean::
	-rm -f $(CGEN_SRCS)
endif
ifneq ($(SLICE_S_SRCS),)
clean::
	-rm -f $(SGEN_SRCS)
endif
ifneq ($(SLICE_AMD_SRCS),)
clean::
	-rm -f $(GEN_AMD_SRCS)
endif
ifneq ($(SLICE_SAMD_SRCS),)
clean::
	-rm -f $(SAMD_GEN_SRCS)
endif

ifneq ($(TARGETS_CONFIG),)
clean::
	-rm -f $(TARGETS_CONFIG)
endif

install::
