## bom sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libbom.la

libbom_la_SOURCES= $(bom_h_sources) $(bom_cc_sources) 
libbom_la_CXXFLAGS = $(GSL_CFLAGS) $(BOOST_CFLAGS) 
libbom_la_LDFLAGS = $(GSL_LIBS)

#pkgincludedir = $(includedir)/@PACKAGE@/bom
#pkginclude_HEADERS = $(bom_h_sources)
