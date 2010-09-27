## rmol/bom sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

#
noinst_LTLIBRARIES = librmolbom.la

librmolbom_la_SOURCES = $(rmol_bom_h_sources) $(rmol_bom_cc_sources) 
librmolbom_la_CXXFLAGS = $(BOOST_CFLAGS) $(STDAIR_CFLAGS)
librmolbom_la_LDFLAGS =

#
#pkgincludedir = $(includedir)/@PACKAGE@/bom
#pkginclude_HEADERS = $(rmol_bom_h_sources)

