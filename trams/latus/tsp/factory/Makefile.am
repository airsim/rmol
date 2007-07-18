## factory sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libtspfac.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libtspfac_debug.la
endif
libtspfac_la_SOURCES= $(tspfac_h_sources) $(tspfac_cc_sources) 
libtspfac_la_CXXFLAGS = $(CXXFLAGS_OPT)

libtspfac_debug_la_SOURCES = $(tspfac_h_sources) $(tspfac_cc_sources)
libtspfac_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/tsp/factory
#pkginclude_HEADERS = $(tspfac_h_sources)
