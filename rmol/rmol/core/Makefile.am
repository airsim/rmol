include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =


# Library
lib_LTLIBRARIES = lib@PACKAGE@.la

lib@PACKAGE@_la_SOURCES = $(service_h_sources) $(service_cc_sources)
lib@PACKAGE@_la_LIBADD = \
	$(top_builddir)/@PACKAGE@/basic/libbas.la \
	$(top_builddir)/@PACKAGE@/field/libfld.la \
	$(top_builddir)/@PACKAGE@/bom/libbom.la \
	$(top_builddir)/@PACKAGE@/factory/libfac.la \
	$(top_builddir)/@PACKAGE@/command/libcmd.la \
	$(top_builddir)/@PACKAGE@/service/libsvc.la
lib@PACKAGE@_la_LDFLAGS = \
	$(BOOST_DATE_TIME_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) \
	$(GSL_LIBS) -version-info $(GENERIC_LIBRARY_VERSION)
