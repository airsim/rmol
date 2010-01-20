include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =


# Library
lib_LTLIBRARIES = librmol.la

librmol_la_SOURCES = $(service_h_sources) $(service_cc_sources)
librmol_la_LIBADD = \
	$(top_builddir)/rmol/basic/libbas.la \
	$(top_builddir)/rmol/field/libfld.la \
	$(top_builddir)/rmol/bom/libbom.la \
	$(top_builddir)/rmol/factory/libfac.la \
	$(top_builddir)/rmol/command/libcmd.la \
	$(top_builddir)/rmol/service/libsvc.la
librmol_la_LDFLAGS = \
	$(BOOST_DATE_TIME_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_FILESYSTEM_LIB) \
	$(top_builddir)/stdair/core/libstdair.la \
	$(GSL_LIBS) -version-info $(GENERIC_LIBRARY_VERSION)
