## basic sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libsimbas.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libsimbas_debug.la
endif
libsimbas_la_SOURCES= $(simbas_h_sources) $(simbas_cc_sources) 
libsimbas_la_CXXFLAGS = $(CXXFLAGS_OPT)

libsimbas_debug_la_SOURCES = $(simbas_h_sources) $(simbas_cc_sources)
libsimbas_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/sim/basic
#pkginclude_HEADERS = $(simbas_h_sources)
