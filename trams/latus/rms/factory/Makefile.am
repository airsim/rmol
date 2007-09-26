## factory sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libinvfac.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libinvfac_debug.la
endif
libinvfac_la_SOURCES= $(invfac_h_sources) $(invfac_cc_sources) 
libinvfac_la_CXXFLAGS = $(CXXFLAGS_OPT)

libinvfac_debug_la_SOURCES = $(invfac_h_sources) $(invfac_cc_sources)
libinvfac_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/inv/factory
#pkginclude_HEADERS = $(invfac_h_sources)
