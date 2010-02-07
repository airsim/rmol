# core
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =


# Library
lib_LTLIBRARIES = libstdair.la

libstdair_la_SOURCES = $(service_h_sources) $(service_cc_sources)
libstdair_la_LIBADD = \
			$(top_builddir)/stdair/basic/libbas.la \
			$(top_builddir)/stdair/bom/libbom.la \
			$(top_builddir)/stdair/dbadaptor/libdba.la \
			$(top_builddir)/stdair/factory/libfac.la \
			$(top_builddir)/stdair/service/libsvc.la
libstdair_la_LDFLAGS = \
	$(BOOST_DATE_TIME_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) \
	$(BOOST_FILESYSTEM_LIB) \
	-version-info $(GENERIC_LIBRARY_VERSION)

#
pkgincludedir = $(includedir)/stdair
pkginclude_HEADERS = $(service_h_sources)
