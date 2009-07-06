## command sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = book

check_PROGRAMS = mpl

mpl_SOURCES = mpl.cpp
mpl_CXXFLAGS = $(BOOST_CFLAGS)
mpl_LDADD = $(BOOST_LIB)

EXTRA_DIST = test_mpl.sh
