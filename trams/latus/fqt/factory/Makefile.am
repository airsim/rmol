## factory sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libfqtfac.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libfqtfac_debug.la
endif
libfqtfac_la_SOURCES= $(fqtfac_h_sources) $(fqtfac_cc_sources) 
libfqtfac_la_CXXFLAGS = $(CXXFLAGS_OPT)

libfqtfac_debug_la_SOURCES = $(fqtfac_h_sources) $(fqtfac_cc_sources)
libfqtfac_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/fqt/factory
#pkginclude_HEADERS = $(fqtfac_h_sources)
