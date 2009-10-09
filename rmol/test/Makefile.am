## test sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

##
SUBDIRS = com 

EXTRA_DIST = testLib.sh
##

EXTRA_TESTS = valarrays bomsforforecaster
STD_CHECKS = OptimiseTestSuite SimulateTestSuite ForecasterTestSuite UnconstrainerTestSuite
check_PROGRAMS = $(STD_CHECKS) $(EXTRA_TESTS)
TESTS = $(STD_CHECKS)
XFAIL_TESTS = #IndexBuildingTestSuite

OptimiseTestSuite_SOURCES = OptimiseTestSuite.hpp OptimiseTestSuite.cpp
OptimiseTestSuite_CXXFLAGS= $(BOOST_CFLAGS) $(CPPUNIT_CFLAGS)
OptimiseTestSuite_LDADD = 
OptimiseTestSuite_LDFLAGS = $(BOOST_LIBS) $(CPPUNIT_LIBS) \
	$(top_builddir)/test/com/libcppunitcore.la \
	$(top_builddir)/@PACKAGE@/core/lib@PACKAGE@.la

SimulateTestSuite_SOURCES = SimulateTestSuite.hpp SimulateTestSuite.cpp
SimulateTestSuite_CXXFLAGS = $(BOOST_CFLAGS) $(GSL_CFLAGS) $(CPPUNIT_CFLAGS)
SimulateTestSuite_LDADD =
SimulateTestSuite_LDFLAGS = $(BOOST_LIBS) $(GSL_LIBS) $(CPPUNIT_LIBS) \
	$(top_builddir)/test/com/libcppunitcore.la

ForecasterTestSuite_SOURCES = ForecasterTestSuite.hpp ForecasterTestSuite.cpp
ForecasterTestSuite_CXXFLAGS= $(BOOST_CFLAGS) $(CPPUNIT_CFLAGS)
ForecasterTestSuite_LDADD = 
ForecasterTestSuite_LDFLAGS = $(BOOST_LIBS) $(CPPUNIT_LIBS) \
	$(top_builddir)/test/com/libcppunitcore.la \
	$(top_builddir)/@PACKAGE@/core/lib@PACKAGE@.la

UnconstrainerTestSuite_SOURCES = UnconstrainerTestSuite.hpp UnconstrainerTestSuite.cpp
UnconstrainerTestSuite_CXXFLAGS= $(CPPUNIT_CFLAGS)
UnconstrainerTestSuite_LDADD = 
UnconstrainerTestSuite_LDFLAGS = $(CPPUNIT_LIBS) \
	$(top_builddir)/test/com/libcppunitcore.la \
	$(top_builddir)/@PACKAGE@/core/lib@PACKAGE@.la

valarrays_SOURCES = valarrays.cpp
valarrays_CXXFLAGS= $(BOOST_CFLAGS) $(CPPUNIT_CFLAGS)
valarrays_LDADD = 
valarrays_LDFLAGS = $(BOOST_LIBS)

bomsforforecaster_SOURCES = bomsforforecaster.cpp
bomsforforecaster_CXXFLAGS= $(BOOST_CFLAGS) $(CPPUNIT_CFLAGS)
bomsforforecaster_LDADD = 
bomsforforecaster_LDFLAGS = $(BOOST_LIBS) \
	$(top_builddir)/@PACKAGE@/core/lib@PACKAGE@.la \
	$(top_builddir)/@PACKAGE@/service/libsvc.la

