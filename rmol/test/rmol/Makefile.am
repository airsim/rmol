## test/rmol sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

##
SUBDIRS =

EXTRA_DIST = testLib.sh
##

EXTRA_TESTS = bomsforforecaster

STD_CHECKS = OptimiseTestSuite SimulateTestSuite \
	ForecasterTestSuite UnconstrainerTestSuite
check_PROGRAMS = $(STD_CHECKS) $(EXTRA_TESTS)
TESTS = $(STD_CHECKS)
XFAIL_TESTS = #OptimiseTestSuite

OptimiseTestSuite_SOURCES = OptimiseTestSuite.hpp OptimiseTestSuite.cpp
OptimiseTestSuite_CXXFLAGS= $(BOOST_CFLAGS) $(CPPUNIT_CFLAGS)
OptimiseTestSuite_LDADD = 
OptimiseTestSuite_LDFLAGS = $(BOOST_LIBS) $(CPPUNIT_LIBS) \
	$(top_builddir)/extracppunit/libextracc-extracppunit.la \
	$(top_builddir)/stdair/core/libstdair.la \
	$(top_builddir)/rmol/core/librmol.la

SimulateTestSuite_SOURCES = SimulateTestSuite.hpp SimulateTestSuite.cpp
SimulateTestSuite_CXXFLAGS = $(BOOST_CFLAGS) $(GSL_CFLAGS) $(CPPUNIT_CFLAGS)
SimulateTestSuite_LDADD =
SimulateTestSuite_LDFLAGS = $(BOOST_LIBS) $(GSL_LIBS) $(CPPUNIT_LIBS) \
	$(top_builddir)/extracppunit/libextracc-extracppunit.la

ForecasterTestSuite_SOURCES = ForecasterTestSuite.hpp ForecasterTestSuite.cpp
ForecasterTestSuite_CXXFLAGS= $(BOOST_CFLAGS) $(CPPUNIT_CFLAGS)
ForecasterTestSuite_LDADD = 
ForecasterTestSuite_LDFLAGS = $(BOOST_LIBS) $(CPPUNIT_LIBS) \
	$(top_builddir)/extracppunit/libextracc-extracppunit.la \
	$(top_builddir)/stdair/core/libstdair.la \
	$(top_builddir)/rmol/core/librmol.la

UnconstrainerTestSuite_SOURCES = UnconstrainerTestSuite.hpp \
							UnconstrainerTestSuite.cpp
UnconstrainerTestSuite_CXXFLAGS= $(CPPUNIT_CFLAGS)
UnconstrainerTestSuite_LDADD = 
UnconstrainerTestSuite_LDFLAGS = $(CPPUNIT_LIBS) \
	$(top_builddir)/extracppunit/libextracc-extracppunit.la \
	$(top_builddir)/stdair/core/libstdair.la \
	$(top_builddir)/rmol/core/librmol.la

bomsforforecaster_SOURCES = bomsforforecaster.cpp
bomsforforecaster_CXXFLAGS= $(BOOST_CFLAGS) $(CPPUNIT_CFLAGS)
bomsforforecaster_LDADD = 
bomsforforecaster_LDFLAGS = $(BOOST_LIBS) \
	$(top_builddir)/rmol/core/librmol.la \
	$(top_builddir)/rmol/service/libsvc.la

