## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libsimsvc.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libsimsvc_debug.la
endif
libsimsvc_la_SOURCES= $(simsvc_h_sources) $(simsvc_cc_sources) 
libsimsvc_la_CXXFLAGS = $(CXXFLAGS_OPT)

libsimsvc_debug_la_SOURCES = $(simsvc_h_sources) $(simsvc_cc_sources)
libsimsvc_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/sim/service
#pkginclude_HEADERS = $(simsvc_h_sources)
