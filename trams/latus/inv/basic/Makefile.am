## basic sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libinvbas.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libinvbas_debug.la
endif
libinvbas_la_SOURCES= $(invbas_h_sources) $(invbas_cc_sources) 
libinvbas_la_CXXFLAGS = $(CXXFLAGS_OPT)

libinvbas_debug_la_SOURCES = $(invbas_h_sources) $(invbas_cc_sources)
libinvbas_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/inv/basic
#pkginclude_HEADERS = $(invbas_h_sources)
