## field sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libfld.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libfld_debug.la
endif
libfld_la_SOURCES= $(fld_h_sources) $(fld_cc_sources) 
libfld_la_CXXFLAGS = $(CXXFLAGS_OPT)

libfld_debug_la_SOURCES = $(fld_h_sources) $(fld_cc_sources)
libfld_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/field
#pkginclude_HEADERS = $(fld_h_sources)
