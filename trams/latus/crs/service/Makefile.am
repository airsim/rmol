## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libcrssvc.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libcrssvc_debug.la
endif
libcrssvc_la_SOURCES= $(crssvc_h_sources) $(crssvc_cc_sources) 
libcrssvc_la_CXXFLAGS = $(CXXFLAGS_OPT)

libcrssvc_debug_la_SOURCES = $(crssvc_h_sources) $(crssvc_cc_sources)
libcrssvc_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/crs/service
#pkginclude_HEADERS = $(crssvc_h_sources)
