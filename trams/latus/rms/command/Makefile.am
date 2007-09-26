## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libinvcmd.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libinvcmd_debug.la
endif
libinvcmd_la_SOURCES= $(invcmd_h_sources) $(invcmd_cc_sources) 
libinvcmd_la_CXXFLAGS = $(CXXFLAGS_OPT)

libinvcmd_debug_la_SOURCES = $(invcmd_h_sources) $(invcmd_cc_sources)
libinvcmd_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/inv/command
#pkginclude_HEADERS = $(invcmd_h_sources)
