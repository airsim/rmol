## field sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libtspfld.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libtspfld_debug.la
endif
libtspfld_la_SOURCES= $(tspfld_h_sources) $(tspfld_cc_sources) 
libtspfld_la_CXXFLAGS = $(CXXFLAGS_OPT)

libtspfld_debug_la_SOURCES = $(tspfld_h_sources) $(tspfld_cc_sources)
libtspfld_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/tsp/field
#pkginclude_HEADERS = $(tspfld_h_sources)
