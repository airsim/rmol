## bom sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libtspbom.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libtspbom_debug.la
endif
libtspbom_la_SOURCES= $(tspbom_h_sources) $(tspbom_cc_sources) 
libtspbom_la_CXXFLAGS = $(CXXFLAGS_OPT) $(GSL_CFLAGS)
libtspbom_la_LIBADD = $(GSL_LIBS)

libtspbom_debug_la_SOURCES = $(tspbom_h_sources) $(tspbom_cc_sources)
libtspbom_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/tsp/bom
#pkginclude_HEADERS = $(tspbom_h_sources)
