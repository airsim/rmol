## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libsvc.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libsvc_debug.la
endif
libsvc_la_SOURCES= $(svc_h_sources) $(svc_cc_sources) 
libsvc_la_CXXFLAGS = $(CXXFLAGS_OPT)

libsvc_debug_la_SOURCES = $(svc_h_sources) $(svc_cc_sources)
libsvc_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/service
#pkginclude_HEADERS = $(cmd_h_sources)
