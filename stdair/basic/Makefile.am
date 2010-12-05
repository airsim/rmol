## stdair/basic sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

#
noinst_LTLIBRARIES= libstdairbas.la

libstdairbas_la_SOURCES = $(stdair_bas_h_sources) $(stdair_bas_cc_sources) 
libstdairbas_la_CXXFLAGS = $(BOOST_CFLAGS) 
libstdairbas_la_LDFLAGS =


# Header files
pkgincludedir = $(includedir)/stdair/basic
pkginclude_HEADERS = $(stdair_bas_h_sources)

