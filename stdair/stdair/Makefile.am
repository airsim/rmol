# stdair
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = basic bom dbadaptor factory command config service

#EXTRA_DIST = config_msvc.h
EXTRA_DIST =

# Library
lib_LTLIBRARIES = libstdair.la

libstdair_la_SOURCES = $(stdair_service_h_sources) $(stdair_service_cc_sources)
libstdair_la_LIBADD = \
			$(top_builddir)/stdair/basic/libstdairbas.la \
			$(top_builddir)/stdair/bom/libstdairbom.la \
			$(top_builddir)/stdair/dbadaptor/libstdairdba.la \
			$(top_builddir)/stdair/factory/libstdairfac.la \
			$(top_builddir)/stdair/command/libstdaircmd.la \
			$(top_builddir)/stdair/service/libstdairsvc.la
libstdair_la_LDFLAGS = \
	$(BOOST_DATE_TIME_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) \
	$(BOOST_FILESYSTEM_LIB) $(SOCI_LIBS) \
	-version-info $(GENERIC_LIBRARY_VERSION)

# Header files
pkgincludedir = $(includedir)/stdair
pkginclude_HEADERS = $(stdair_service_h_sources)

