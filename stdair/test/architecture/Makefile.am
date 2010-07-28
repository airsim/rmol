## test/inheritance sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =

check_PROGRAMS = architecture

architecture_SOURCES = $(architecture_h_sources) $(architecture_cc_sources)
architecture_CXXFLAGS = $(BOOST_CFLAGS)
architecture_LDADD = $(BOOST_LIB)
architecture_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LIB) \
	$(top_builddir)/stdair/core/libstdair.la

EXTRA_DIST =
