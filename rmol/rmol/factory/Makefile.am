## factory sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libfac.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libfac_debug.la
endif
libfac_la_SOURCES= $(fac_h_sources) $(fac_cc_sources) 
libfac_la_CXXFLAGS = $(CXXFLAGS_OPT)

libfac_debug_la_SOURCES = $(fac_h_sources) $(fac_cc_sources)
libfac_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

pkgincludedir = $(includedir)/@PACKAGE@/factory
pkginclude_HEADERS = $(fac_h_sources)
