## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libcomcmd.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libcomcmd_debug.la
endif
libcomcmd_la_SOURCES= $(comcmd_h_sources) $(comcmd_cc_sources) 
libcomcmd_la_CXXFLAGS = $(CXXFLAGS_OPT) $(BOOST_CPPFLAGS)

libcomcmd_debug_la_SOURCES = $(comcmd_h_sources) $(comcmd_cc_sources)
libcomcmd_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG) $(BOOST_CPPFLAGS)

#pkgincludedir = $(includedir)/@PACKAGE@/com/command
#pkginclude_HEADERS = $(comcmd_h_sources)
