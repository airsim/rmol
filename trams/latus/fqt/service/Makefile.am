## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libfqtsvc.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libfqtsvc_debug.la
endif
libfqtsvc_la_SOURCES= $(fqtsvc_h_sources) $(fqtsvc_cc_sources) 
libfqtsvc_la_CXXFLAGS = $(CXXFLAGS_OPT)

libfqtsvc_debug_la_SOURCES = $(fqtsvc_h_sources) $(fqtsvc_cc_sources)
libfqtsvc_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/fqt/service
#pkginclude_HEADERS = $(fqtsvc_h_sources)
