## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libucmsvc.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libucmsvc_debug.la
endif
libucmsvc_la_SOURCES= $(ucmsvc_h_sources) $(ucmsvc_cc_sources) 
libucmsvc_la_CXXFLAGS = $(CXXFLAGS_OPT)

libucmsvc_debug_la_SOURCES = $(ucmsvc_h_sources) $(ucmsvc_cc_sources)
libucmsvc_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/ucm/service
#pkginclude_HEADERS = $(ucmsvc_h_sources)
