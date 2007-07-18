## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libcrscmd.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libcrscmd_debug.la
endif
libcrscmd_la_SOURCES= $(crscmd_h_sources) $(crscmd_cc_sources) 
libcrscmd_la_CXXFLAGS = $(CXXFLAGS_OPT)

libcrscmd_debug_la_SOURCES = $(crscmd_h_sources) $(crscmd_cc_sources)
libcrscmd_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/crs/command
#pkginclude_HEADERS = $(crscmd_h_sources)
