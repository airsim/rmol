## field sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libcrsfld.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libcrsfld_debug.la
endif
libcrsfld_la_SOURCES= $(crsfld_h_sources) $(crsfld_cc_sources) 
libcrsfld_la_CXXFLAGS = $(CXXFLAGS_OPT)

libcrsfld_debug_la_SOURCES = $(crsfld_h_sources) $(crsfld_cc_sources)
libcrsfld_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/crs/field
#pkginclude_HEADERS = $(crsfld_h_sources)
