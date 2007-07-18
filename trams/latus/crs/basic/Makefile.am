## basic sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libcrsbas.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libcrsbas_debug.la
endif
libcrsbas_la_SOURCES= $(crsbas_h_sources) $(crsbas_cc_sources) 
libcrsbas_la_CXXFLAGS = $(CXXFLAGS_OPT)

libcrsbas_debug_la_SOURCES = $(crsbas_h_sources) $(crsbas_cc_sources)
libcrsbas_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/crs/basic
#pkginclude_HEADERS = $(crsbas_h_sources)
