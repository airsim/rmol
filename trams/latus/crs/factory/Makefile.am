## factory sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libcrsfac.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libcrsfac_debug.la
endif
libcrsfac_la_SOURCES= $(crsfac_h_sources) $(crsfac_cc_sources) 
libcrsfac_la_CXXFLAGS = $(CXXFLAGS_OPT)

libcrsfac_debug_la_SOURCES = $(crsfac_h_sources) $(crsfac_cc_sources)
libcrsfac_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/crs/factory
#pkginclude_HEADERS = $(crsfac_h_sources)
