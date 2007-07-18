## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libdegcmd.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libdegcmd_debug.la
endif
libdegcmd_la_SOURCES= $(degcmd_h_sources) $(degcmd_cc_sources) 
libdegcmd_la_CXXFLAGS = $(CXXFLAGS_OPT) $(BOOST_CPPFLAGS)

libdegcmd_debug_la_SOURCES = $(degcmd_h_sources) $(degcmd_cc_sources)
libdegcmd_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG) $(BOOST_CPPFLAGS)

#pkgincludedir = $(includedir)/@PACKAGE@/deg/command
#pkginclude_HEADERS = $(degcmd_h_sources)
