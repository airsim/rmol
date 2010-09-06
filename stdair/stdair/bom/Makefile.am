## stdair/bom sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

#
noinst_LTLIBRARIES= libstdairbom.la

libstdairbom_la_SOURCES = $(stdair_bom_h_sources) $(stdair_bom_cc_sources) 
libstdairbom_la_CXXFLAGS = $(BOOST_CFLAGS) 
libstdairbom_la_LDFLAGS =


# Header files
pkgincludedir = $(includedir)/stdair/bom
pkginclude_HEADERS = $(stdair_bom_h_sources)

