## bom sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libbom.la

libbom_la_SOURCES = $(bom_h_sources) $(bom_cc_sources) 
libbom_la_CXXFLAGS = $(BOOST_CFLAGS) 
libbom_la_LDFLAGS =


# Header files
pkgincludedir = $(includedir)/stdair/bom
pkginclude_HEADERS = $(bom_h_sources)
