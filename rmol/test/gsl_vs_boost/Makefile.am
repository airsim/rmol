## test/gsl_vs_boost sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

##
SUBDIRS =

##
EXTRA_TESTS = boost_vs_gsl

STD_CHECKS =
check_PROGRAMS = $(STD_CHECKS) $(EXTRA_TESTS)
TESTS = $(STD_CHECKS)
XFAIL_TESTS = #boost_vs_gsl


boost_vs_gsl_SOURCES = boost_vs_gsl.cpp
boost_vs_gsl_CXXFLAGS= $(BOOST_CFLAGS) $(GSL_CFLAGS) $(CPPUNIT_CFLAGS)
boost_vs_gsl_LDADD = 
boost_vs_gsl_LDFLAGS = $(BOOST_LIBS) $(GSL_LIBS)

