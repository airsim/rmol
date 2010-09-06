## stdair/dbadaptor sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

#
noinst_LTLIBRARIES= libstdairdba.la

libstdairdba_la_SOURCES= $(stdair_dba_h_sources) $(stdair_dba_cc_sources) 
libstdairdba_la_CXXFLAGS = $(SOCI_CFLAGS)
libstdairdba_la_LIBADD =
libstdairdba_la_LDFLAGS = $(SOCI_LIBS)


# Header files
pkgincludedir = $(includedir)/stdair/dbadaptor
pkginclude_HEADERS = $(stdair_dba_h_sources)

