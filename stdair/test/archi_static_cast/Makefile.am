## test/inheritance sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =

check_PROGRAMS = archi_static_cast

archi_static_cast_SOURCES = $(archi_static_cast_h_sources) $(archi_static_cast_cc_sources)
archi_static_cast_CXXFLAGS = $(BOOST_CFLAGS)
archi_static_cast_LDADD = $(BOOST_LIB)
archi_static_cast_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LIB) \
	$(top_builddir)/stdair/libstdair.la

EXTRA_DIST =
