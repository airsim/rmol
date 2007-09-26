## factory sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libucmfac.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libucmfac_debug.la
endif
libucmfac_la_SOURCES= $(ucmfac_h_sources) $(ucmfac_cc_sources) 
libucmfac_la_CXXFLAGS = $(CXXFLAGS_OPT)

libucmfac_debug_la_SOURCES = $(ucmfac_h_sources) $(ucmfac_cc_sources)
libucmfac_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/ucm/factory
#pkginclude_HEADERS = $(ucmfac_h_sources)
