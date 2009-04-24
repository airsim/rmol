## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libcmd.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libcmd_debug.la
endif
libcmd_la_SOURCES= $(cmd_h_sources) $(cmd_cc_sources) 
libcmd_la_CXXFLAGS = $(CXXFLAGS_OPT) $(BOOST_CFLAGS)

libcmd_debug_la_SOURCES = $(cmd_h_sources) $(cmd_cc_sources)
libcmd_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG) $(BOOST_CFLAGS)

#pkgincludedir = $(includedir)/@PACKAGE@/command
#pkginclude_HEADERS = $(cmd_h_sources)
