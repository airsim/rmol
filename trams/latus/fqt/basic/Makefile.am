## basic sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libfqtbas.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libfqtbas_debug.la
endif
libfqtbas_la_SOURCES= $(fqtbas_h_sources) $(fqtbas_cc_sources) 
libfqtbas_la_CXXFLAGS = $(CXXFLAGS_OPT)

libfqtbas_debug_la_SOURCES = $(fqtbas_h_sources) $(fqtbas_cc_sources)
libfqtbas_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/fqt/basic
#pkginclude_HEADERS = $(fqtbas_h_sources)
