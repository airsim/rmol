## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libsimcmd.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libsimcmd_debug.la
endif
libsimcmd_la_SOURCES= $(simcmd_h_sources) $(simcmd_cc_sources) 
libsimcmd_la_CXXFLAGS = $(CXXFLAGS_OPT) $(BOOST_CPPFLAGS)

libsimcmd_debug_la_SOURCES = $(simcmd_h_sources) $(simcmd_cc_sources)
libsimcmd_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG) $(BOOST_CPPFLAGS)

#pkgincludedir = $(includedir)/@PACKAGE@/sim/command
#pkginclude_HEADERS = $(simcmd_h_sources)
