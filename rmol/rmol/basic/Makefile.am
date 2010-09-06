## rmol/basic sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

#
noinst_LTLIBRARIES = librmolbas.la

librmolbas_la_SOURCES = $(rmol_bas_h_sources) $(rmol_bas_cc_sources) 
librmolbas_la_CXXFLAGS = $(BOOST_CFLAGS) $(STDAIR_CFLAGS)
librmolbas_la_LDFLAGS =

#
#pkgincludedir = $(includedir)/@PACKAGE@/basic
#pkginclude_HEADERS = $(rmol_bas_h_sources)

