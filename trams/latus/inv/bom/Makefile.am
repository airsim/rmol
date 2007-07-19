## bom sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libinvbom.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libinvbom_debug.la
endif
libinvbom_la_SOURCES= $(invbom_h_sources) $(invbom_cc_sources) 
libinvbom_la_CXXFLAGS = $(CXXFLAGS_OPT) $(GSL_CFLAGS)
libinvbom_la_LIBADD = $(GSL_LIBS)

libinvbom_debug_la_SOURCES = $(invbom_h_sources) $(invbom_cc_sources)
libinvbom_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/inv/bom
#pkginclude_HEADERS = $(invbom_h_sources)
