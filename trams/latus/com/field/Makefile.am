## field sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libcomfld.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libcomfld_debug.la
endif
libcomfld_la_SOURCES= $(comfld_h_sources) $(comfld_cc_sources) 
libcomfld_la_CXXFLAGS = $(CXXFLAGS_OPT)

libcomfld_debug_la_SOURCES = $(comfld_h_sources) $(comfld_cc_sources)
libcomfld_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/com/field
#pkginclude_HEADERS = $(comfld_h_sources)
