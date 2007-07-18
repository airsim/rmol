## field sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libdegfld.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libdegfld_debug.la
endif
libdegfld_la_SOURCES= $(degfld_h_sources) $(degfld_cc_sources) 
libdegfld_la_CXXFLAGS = $(CXXFLAGS_OPT)

libdegfld_debug_la_SOURCES = $(degfld_h_sources) $(degfld_cc_sources)
libdegfld_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/deg/field
#pkginclude_HEADERS = $(degfld_h_sources)
