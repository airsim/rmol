## basic sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libtspbas.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libtspbas_debug.la
endif
libtspbas_la_SOURCES= $(tspbas_h_sources) $(tspbas_cc_sources) 
libtspbas_la_CXXFLAGS = $(CXXFLAGS_OPT)

libtspbas_debug_la_SOURCES = $(tspbas_h_sources) $(tspbas_cc_sources)
libtspbas_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/tsp/basic
#pkginclude_HEADERS = $(tspbas_h_sources)
