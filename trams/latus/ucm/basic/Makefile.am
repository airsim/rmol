## basic sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libucmbas.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libucmbas_debug.la
endif
libucmbas_la_SOURCES= $(ucmbas_h_sources) $(ucmbas_cc_sources) 
libucmbas_la_CXXFLAGS = $(CXXFLAGS_OPT)

libucmbas_debug_la_SOURCES = $(ucmbas_h_sources) $(ucmbas_cc_sources)
libucmbas_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/ucm/basic
#pkginclude_HEADERS = $(ucmbas_h_sources)
