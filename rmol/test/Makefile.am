## command sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

check_PROGRAMS = optimise simulate testGSL
optimise_SOURCES = optimise.cpp
optimise_LDADD = $(top_builddir)/@PACKAGE@/librmol.la

simulate_SOURCES = simulate.cpp
simulate_CXXFLAGS = $(BOOST_CPPFLAGS) $(GSL_CFLAGS) 
simulate_LDADD = $(BOOST_LIBS) $(GSL_LIBS)

testGSL_SOURCES = testGSL.cpp
testGSL_LDADD = $(top_builddir)/@PACKAGE@/librmol.la

EXTRA_DIST = sample1.csv sample2.csv sample3.csv sample4.csv testLib.sh

