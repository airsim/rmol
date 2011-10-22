## basic sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libbas.la

libbas_la_SOURCES= $(bas_h_sources) $(bas_cc_sources) 
libbas_la_CXXFLAGS = $(BOOST_CFLAGS)

#pkgincludedir = $(includedir)/@PACKAGE@/basic
#pkginclude_HEADERS = $(bas_h_sources)
