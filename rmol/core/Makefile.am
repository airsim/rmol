# rmol/core sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =


# Library
lib_LTLIBRARIES = librmol.la

librmol_la_SOURCES = $(rmol_service_h_sources) $(rmol_service_cc_sources)
librmol_la_LIBADD = \
	$(top_builddir)/rmol/basic/librmolbas.la \
	$(top_builddir)/rmol/bom/librmolbom.la \
	$(top_builddir)/rmol/factory/librmolfac.la \
	$(top_builddir)/rmol/command/librmolcmd.la \
	$(top_builddir)/rmol/service/librmolsvc.la
librmol_la_LDFLAGS = \
	$(BOOST_DATE_TIME_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) \
	$(BOOST_FILESYSTEM_LIB) $(STDAIR_LIBS) \
	-version-info $(GENERIC_LIBRARY_VERSION)

