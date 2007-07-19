## field sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libinvfld.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libinvfld_debug.la
endif
libinvfld_la_SOURCES= $(invfld_h_sources) $(invfld_cc_sources) 
libinvfld_la_CXXFLAGS = $(CXXFLAGS_OPT)

libinvfld_debug_la_SOURCES = $(invfld_h_sources) $(invfld_cc_sources)
libinvfld_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/inv/field
#pkginclude_HEADERS = $(invfld_h_sources)
