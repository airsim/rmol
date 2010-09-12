## test/archi_intru sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

MAINTAINERCLEANFILES = Makefile.in

##
SUBDIRS =

EXTRA_DIST =
##

##
# Test library
noinst_LTLIBRARIES = libarchiintru.la

libarchiintru_la_SOURCES = $(archi_intru_h_sources) $(archi_intru_cc_sources)
libarchiintru_la_CXXFLAGS = $(BOOST_CFLAGS)
libarchiintru_la_LDFLAGS = $(BOOST_LIBS)

##
# Test binary
check_PROGRAMS = archi
#TESTS = $(check_PROGRAMS)
TESTS =
XFAIL_TESTS = #IndexBuildingTestSuite

archi_SOURCES = archi.cpp
archi_CXXFLAGS =
archi_LDADD = 
archi_LDFLAGS = $(top_builddir)/test/archi_intru/libarchiintru.la
