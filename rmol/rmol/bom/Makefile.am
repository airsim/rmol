## rmol/bom sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

#
noinst_LTLIBRARIES = librmolbom.la

librmolbom_la_SOURCES = $(rmol_bom_h_sources) $(rmol_bom_cc_sources) 
librmolbom_la_CXXFLAGS = $(GSL_CFLAGS) $(BOOST_CFLAGS) 
librmolbom_la_LDFLAGS = $(GSL_LIBS)


#pkgincludedir = $(includedir)/@PACKAGE@/bom
#pkginclude_HEADERS = $(bom_h_sources)
