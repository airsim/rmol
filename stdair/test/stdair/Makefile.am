## test sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

##
SUBDIRS =

EXTRA_DIST =
##

check_PROGRAMS = StandardAirlineITTestSuite
TESTS = $(check_PROGRAMS)
XFAIL_TESTS = #IndexBuildingTestSuite

StandardAirlineITTestSuite_SOURCES = StandardAirlineITTestSuite.hpp \
									StandardAirlineITTestSuite.cpp
StandardAirlineITTestSuite_CXXFLAGS= $(BOOST_CFLAGS) $(CPPUNIT_CFLAGS)
StandardAirlineITTestSuite_LDADD = 
StandardAirlineITTestSuite_LDFLAGS = $(BOOST_LIBS) $(CPPUNIT_LIBS) \
	$(top_builddir)/extracppunit/libextracc-extracppunit.la \
	$(top_builddir)/stdair/core/libstdair.la
