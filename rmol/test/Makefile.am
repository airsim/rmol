## command sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

check_PROGRAMS = optimise
optimise_SOURCES = optimise.cpp
optimise_LDADD = $(top_builddir)/@PACKAGE@/librmol.la

#simulate_SOURCES = simulate.cpp
#simulate_LDADD = $(BOOST_LIBS)

EXTRA_DIST = sample1.csv sample2.csv sample3.csv sample4.csv testLib.sh