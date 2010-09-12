## test/archi_intru sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

MAINTAINERCLEANFILES = Makefile.in

##
SUBDIRS =

EXTRA_DIST =
##

check_PROGRAMS = archi
#TESTS = $(check_PROGRAMS)
TESTS =
XFAIL_TESTS = #IndexBuildingTestSuite

archi_SOURCES = $(archi_intru_h_sources) $(archi_intru_cc_sources)
archi_CXXFLAGS = $(BOOST_CFLAGS)
archi_LDFLAGS = $(BOOST_LIBS)
archi_LDADD = 
