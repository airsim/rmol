## bom sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libfqtbom.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libfqtbom_debug.la
endif
libfqtbom_la_SOURCES= $(fqtbom_h_sources) $(fqtbom_cc_sources) 
libfqtbom_la_CXXFLAGS = $(CXXFLAGS_OPT)
libfqtbom_la_LIBADD = $(GSL_LIBS)

libfqtbom_debug_la_SOURCES = $(fqtbom_h_sources) $(fqtbom_cc_sources)
libfqtbom_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/fqt/bom
#pkginclude_HEADERS = $(fqtbom_h_sources)
