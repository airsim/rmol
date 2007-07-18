## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libtspcmd.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libtspcmd_debug.la
endif
libtspcmd_la_SOURCES= $(tspcmd_h_sources) $(tspcmd_cc_sources) 
libtspcmd_la_CXXFLAGS = $(CXXFLAGS_OPT)

libtspcmd_debug_la_SOURCES = $(tspcmd_h_sources) $(tspcmd_cc_sources)
libtspcmd_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/tsp/command
#pkginclude_HEADERS = $(tspcmd_h_sources)
