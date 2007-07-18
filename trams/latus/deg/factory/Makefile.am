## factory sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libdegfac.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libdegfac_debug.la
endif
libdegfac_la_SOURCES= $(degfac_h_sources) $(degfac_cc_sources) 
libdegfac_la_CXXFLAGS = $(CXXFLAGS_OPT)

libdegfac_debug_la_SOURCES = $(degfac_h_sources) $(degfac_cc_sources)
libdegfac_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/deg/factory
#pkginclude_HEADERS = $(degfac_h_sources)
