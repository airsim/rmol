## stdair/command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

#
noinst_LTLIBRARIES = libstdaircmd.la

libstdaircmd_la_SOURCES = $(stdair_cmd_h_sources) $(stdair_cmd_cc_sources) 
libstdaircmd_la_CXXFLAGS = $(BOOST_CFLAGS) $(SOCI_CFLAGS)
libstdaircmd_la_LIBADD =
libstdaircmd_la_LDFLAGS = $(BOOST_LIBS) $(SOCI_LIBS)


# Header files
pkgincludedir = $(includedir)/stdair/command
pkginclude_HEADERS = $(stdair_cmd_h_sources)

