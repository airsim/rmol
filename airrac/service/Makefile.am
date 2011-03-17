## airrac/service sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

#
noinst_LTLIBRARIES = libairracsvc.la

libairracsvc_la_SOURCES = $(airrac_svc_h_sources) $(airrac_svc_cc_sources) 
libairracsvc_la_CXXFLAGS = $(BOOST_CFLAGS) $(STDAIR_CFLAGS)
libairracsvc_la_LDFLAGS =

#
#pkgincludedir = $(includedir)/@PACKAGE@/service
#pkginclude_HEADERS = $(airrac_svc_h_sources)
