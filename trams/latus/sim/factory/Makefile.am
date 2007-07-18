## factory sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libsimfac.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libsimfac_debug.la
endif
libsimfac_la_SOURCES= $(simfac_h_sources) $(simfac_cc_sources) 
libsimfac_la_CXXFLAGS = $(CXXFLAGS_OPT)

libsimfac_debug_la_SOURCES = $(simfac_h_sources) $(simfac_cc_sources)
libsimfac_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/sim/factory
#pkginclude_HEADERS = $(simfac_h_sources)
