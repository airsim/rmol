## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libtspsvc.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libtspsvc_debug.la
endif
libtspsvc_la_SOURCES= $(tspsvc_h_sources) $(tspsvc_cc_sources) 
libtspsvc_la_CXXFLAGS = $(CXXFLAGS_OPT)

libtspsvc_debug_la_SOURCES = $(tspsvc_h_sources) $(tspsvc_cc_sources)
libtspsvc_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/tsp/service
#pkginclude_HEADERS = $(tspsvc_h_sources)
