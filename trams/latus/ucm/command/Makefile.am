## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libucmcmd.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libucmcmd_debug.la
endif
libucmcmd_la_SOURCES= $(ucmcmd_h_sources) $(ucmcmd_cc_sources) 
libucmcmd_la_CXXFLAGS = $(CXXFLAGS_OPT)

libucmcmd_debug_la_SOURCES = $(ucmcmd_h_sources) $(ucmcmd_cc_sources)
libucmcmd_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/ucm/command
#pkginclude_HEADERS = $(ucmcmd_h_sources)
