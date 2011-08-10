## test/rmol sub-directory
include $(top_srcdir)/Makefile.common

##
SUBDIRS =

EXTRA_DIST = testLib.sh
##

##
nofail_PRG = OptimiseTestSuite ForecasterTestSuite UnconstrainerTestSuite \
	bomsforforecaster
fail_PRG =
extra_PRG =

#
MAINTAINERCLEANFILES = Makefile.in
CLEANFILES = ${nofail_PRG:%=%_utfresults.xml} ${nofail_PRG:%=%.log} \
	${extra_PRG:%=%.log}

#
check_PROGRAMS = $(nofail_PRG) $(fail_PRG) $(extra_PRG)
TESTS = $(check_PROGRAMS)
XFAIL_TESTS = $(fail_PRG)

#
OptimiseTestSuite_SOURCES = OptimiseTestSuite.cpp
OptimiseTestSuite_CXXFLAGS = $(BOOST_CFLAGS) $(STDAIR_CFLAGS)
OptimiseTestSuite_LDADD = 
OptimiseTestSuite_LDFLAGS = \
	$(BOOST_LIBS) $(BOOST_UNIT_TEST_FRAMEWORK_LIB) $(STDAIR_LIBS) \
	$(top_builddir)/rmol/core/librmol.la

ForecasterTestSuite_SOURCES = ForecasterTestSuite.cpp
ForecasterTestSuite_CXXFLAGS = $(BOOST_CFLAGS) $(STDAIR_CFLAGS)
ForecasterTestSuite_LDADD = 
ForecasterTestSuite_LDFLAGS = \
	$(BOOST_LIBS) $(BOOST_UNIT_TEST_FRAMEWORK_LIB) $(STDAIR_LIBS) \
	$(top_builddir)/rmol/core/librmol.la

UnconstrainerTestSuite_SOURCES = UnconstrainerTestSuite.cpp
UnconstrainerTestSuite_CXXFLAGS = $(BOOST_CFLAGS) $(STDAIR_CFLAGS)
UnconstrainerTestSuite_LDADD = 
UnconstrainerTestSuite_LDFLAGS = \
	$(BOOST_LIBS) $(BOOST_UNIT_TEST_FRAMEWORK_LIB) $(STDAIR_LIBS) \
	$(top_builddir)/rmol/core/librmol.la

bomsforforecaster_SOURCES = bomsforforecaster.cpp
bomsforforecaster_CXXFLAGS = $(BOOST_CFLAGS) $(STDAIR_CFLAGS)
bomsforforecaster_LDADD = 
bomsforforecaster_LDFLAGS = \
	$(BOOST_LIBS) $(BOOST_UNIT_TEST_FRAMEWORK_LIB) $(STDAIR_LIBS) \
	$(top_builddir)/rmol/core/librmol.la
