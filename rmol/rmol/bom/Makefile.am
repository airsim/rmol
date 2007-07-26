## bom sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libbom.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libbom_debug.la
endif
libbom_la_SOURCES= $(bom_h_sources) $(bom_cc_sources) 
libbom_la_CXXFLAGS = $(CXXFLAGS_OPT) $(GSL_CFLAGS)
libbom_la_LIBADD = $(GSL_LIBS)

libbom_debug_la_SOURCES = $(bom_h_sources) $(bom_cc_sources)
libbom_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG) $(GSL_CFLAGS)
libbom_debug_la_LIBADD = $(GSL_LIBS)

#pkgincludedir = $(includedir)/@PACKAGE@/bom
#pkginclude_HEADERS = $(bom_h_sources)
