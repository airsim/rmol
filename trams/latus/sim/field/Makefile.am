## field sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libsimfld.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libsimfld_debug.la
endif
libsimfld_la_SOURCES= $(simfld_h_sources) $(simfld_cc_sources) 
libsimfld_la_CXXFLAGS = $(CXXFLAGS_OPT)

libsimfld_debug_la_SOURCES = $(simfld_h_sources) $(simfld_cc_sources)
libsimfld_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/sim/field
#pkginclude_HEADERS = $(simfld_h_sources)
