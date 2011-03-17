# airrac/core
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =


# Library
lib_LTLIBRARIES = libairrac.la

libairrac_la_SOURCES = $(airrac_service_h_sources) $(airrac_service_cc_sources)
libairrac_la_LIBADD = \
	$(top_builddir)/airrac/basic/libairracbas.la \
	$(top_builddir)/airrac/bom/libairracbom.la \
	$(top_builddir)/airrac/factory/libairracfac.la \
	$(top_builddir)/airrac/command/libairraccmd.la \
	$(top_builddir)/airrac/service/libairracsvc.la
libairrac_la_LDFLAGS = \
	$(BOOST_DATE_TIME_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) \
	$(STDAIR_LIBS) \
	-version-info $(GENERIC_LIBRARY_VERSION)
