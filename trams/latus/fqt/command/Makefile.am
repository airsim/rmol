## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libfqtcmd.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libfqtcmd_debug.la
endif
libfqtcmd_la_SOURCES= $(fqtcmd_h_sources) $(fqtcmd_cc_sources) 
libfqtcmd_la_CXXFLAGS = $(CXXFLAGS_OPT)

libfqtcmd_debug_la_SOURCES = $(fqtcmd_h_sources) $(fqtcmd_cc_sources)
libfqtcmd_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/fqt/command
#pkginclude_HEADERS = $(fqtcmd_h_sources)
