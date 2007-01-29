## basic sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libbas.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libbas_debug.la
endif
libbas_la_SOURCES= $(bas_h_sources) $(bas_cc_sources) 
libbas_la_CXXFLAGS = $(CXXFLAGS_OPT)

libbas_debug_la_SOURCES = $(bas_h_sources) $(bas_cc_sources)
libbas_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

pkgincludedir = $(includedir)/@PACKAGE@/basic
pkginclude_HEADERS = $(bas_h_sources)
