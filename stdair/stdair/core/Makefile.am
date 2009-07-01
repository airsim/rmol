include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =


# Library
lib_LTLIBRARIES = libstdair.la

libstdair_la_SOURCES = $(service_h_sources) $(service_cc_sources)
libstdair_la_LIBADD = \
			$(top_builddir)/stdair/bom/libbom.la \
			$(top_builddir)/stdair/factory/libfac.la
libstdair_la_LDFLAGS = \
	$(BOOST_DATE_TIME_LIB) -version-info $(GENERIC_LIBRARY_VERSION)
