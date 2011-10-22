## test/valarrays sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

##
SUBDIRS =

##
EXTRA_TESTS = valarrays

STD_CHECKS =
check_PROGRAMS = $(STD_CHECKS) $(EXTRA_TESTS)
TESTS = $(STD_CHECKS)
XFAIL_TESTS = #valarrays


valarrays_SOURCES = valarrays.cpp
valarrays_CXXFLAGS= $(BOOST_CFLAGS) $(CPPUNIT_CFLAGS)
valarrays_LDADD = 
valarrays_LDFLAGS = $(BOOST_LIBS)

