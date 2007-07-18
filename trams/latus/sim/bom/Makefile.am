## bom sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libsimbom.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libsimbom_debug.la
endif
libsimbom_la_SOURCES= $(simbom_h_sources) $(simbom_cc_sources) 
libsimbom_la_CXXFLAGS = $(CXXFLAGS_OPT) $(GSL_CFLAGS)
libsimbom_la_LIBADD = $(GSL_LIBS)

libsimbom_debug_la_SOURCES = $(simbom_h_sources) $(simbom_cc_sources)
libsimbom_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/sim/bom
#pkginclude_HEADERS = $(simbom_h_sources)
