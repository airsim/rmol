## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libdegcmd.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libdegcmd_debug.la
endif

# Even the Optimised library is compiled in debug mode, as there seems
# to be a bug with GCC in the optimisation mode on the DemandParserHelper.cpp
# program: the compilation is very very long (several minutes at 100% CPU).
libdegcmd_la_SOURCES= $(degcmd_h_sources) $(degcmd_cc_sources) 
libdegcmd_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

libdegcmd_debug_la_SOURCES = $(degcmd_h_sources) $(degcmd_cc_sources)
libdegcmd_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/deg/command
#pkginclude_HEADERS = $(degcmd_h_sources)
