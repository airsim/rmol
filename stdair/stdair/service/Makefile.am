## stdair/service sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

#
noinst_LTLIBRARIES= libstdairsvc.la

libstdairsvc_la_SOURCES = $(stdair_svc_h_sources) $(stdair_svc_cc_sources) 
libstdairsvc_la_CXXFLAGS = $(SOCI_CFLAGS) $(MYSQL_CFLAGS)
libstdairsvc_la_LDFLAGS = $(SOCI_LIBS) $(MYSQL_LIBS)


# Header files
pkgincludedir = $(includedir)/stdair/service
pkginclude_HEADERS = $(stdair_svc_h_sources)

