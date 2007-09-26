## bom sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libucmbom.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libucmbom_debug.la
endif
libucmbom_la_SOURCES= $(ucmbom_h_sources) $(ucmbom_cc_sources) 
libucmbom_la_CXXFLAGS = $(CXXFLAGS_OPT)
libucmbom_la_LIBADD = $(GSL_LIBS)

libucmbom_debug_la_SOURCES = $(ucmbom_h_sources) $(ucmbom_cc_sources)
libucmbom_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/ucm/bom
#pkginclude_HEADERS = $(ucmbom_h_sources)
