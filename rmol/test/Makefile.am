## command sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

##
SUBDIRS = com

##
check_PROGRAMS = OptimiseTestSuite SimulateTestSuite
TESTS = $(check_PROGRAMS)
XFAIL_TESTS = #IndexBuildingTestSuite

OptimiseTestSuite_SOURCES = OptimiseTestSuite.hpp OptimiseTestSuite.cpp
OptimiseTestSuite_CXXFLAGS= $(BOOST_CFLAGS) $(CPPUNIT_CFLAGS)
OptimiseTestSuite_LDFLAGS = $(BOOST_LIBS) $(CPPUNIT_LIBS)
OptimiseTestSuite_LDADD = $(top_builddir)/test/com/libcppunitcore.la \
				$(top_builddir)/@PACKAGE@/lib@PACKAGE@.la

SimulateTestSuite_SOURCES = SimulateTestSuite.hpp SimulateTestSuite.cpp
SimulateTestSuite_CXXFLAGS = $(BOOST_CFLAGS) $(GSL_CFLAGS) $(CPPUNIT_CFLAGS)
SimulateTestSuite_LDFLAGS = $(BOOST_LIBS) $(GSL_LIBS) $(CPPUNIT_LIBS)
SimulateTestSuite_LDADD = $(top_builddir)/test/com/libcppunitcore.la


EXTRA_DIST = sample1.csv sample2.csv sample3.csv sample4.csv testLib.sh
