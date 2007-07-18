## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libdegsvc.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libdegsvc_debug.la
endif
libdegsvc_la_SOURCES= $(degsvc_h_sources) $(degsvc_cc_sources) 
libdegsvc_la_CXXFLAGS = $(CXXFLAGS_OPT)

libdegsvc_debug_la_SOURCES = $(degsvc_h_sources) $(degsvc_cc_sources)
libdegsvc_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/deg/service
#pkginclude_HEADERS = $(degsvc_h_sources)
