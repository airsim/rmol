## test/stdair sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

MAINTAINERCLEANFILES = Makefile.in

##
SUBDIRS =

EXTRA_DIST =
##

##
# Test library
noinst_LTLIBRARIES = libstdairtest.la

libstdairtest_la_SOURCES = \
	$(stdair_test_lib_h_sources) $(stdair_test_lib_cc_sources)
libstdairtest_la_CXXFLAGS =
libstdairtest_la_LDFLAGS = \
	$(top_builddir)/stdair/libstdair.la


##
# Test binaries
check_PROGRAMS = StandardAirlineITTestSuite
TESTS = $(check_PROGRAMS)
XFAIL_TESTS = #FailingTestSuite

#
StandardAirlineITTestSuite_SOURCES = \
	$(stdair_test_bin_h_sources) $(stdair_test_bin_cc_sources)
StandardAirlineITTestSuite_CXXFLAGS = $(BOOST_CFLAGS) \
	$(CPPUNIT_CFLAGS) $(EXTRACC_CFLAGS)
StandardAirlineITTestSuite_LDADD = 
StandardAirlineITTestSuite_LDFLAGS = $(BOOST_LIBS) \
	$(CPPUNIT_LIBS) $(EXTRACC_LIBS)\
	$(top_builddir)/test/stdair/libstdairtest.la \
	$(top_builddir)/stdair/libstdair.la
