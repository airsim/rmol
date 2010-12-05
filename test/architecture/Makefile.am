## test/architecture sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

#
MAINTAINERCLEANFILES = Makefile.in

EXTRA_DIST =

SUBDIRS =

#
check_PROGRAMS = architecture

architecture_SOURCES = 	$(stdair_archi_h_sources) $(stdair_archi_cc_sources)
architecture_CXXFLAGS = $(BOOST_CFLAGS)
architecture_LDADD =
architecture_LDFLAGS = $(BOOST_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB) \
	$(top_builddir)/stdair/libstdair.la
