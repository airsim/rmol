## command sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

#
SUBDIRS = contrib

EXTRA_DIST =

#
check_PROGRAMS = mpl_book_ch_01

#
mpl_book_ch_01_SOURCES = mpl_book_ch_01.cpp
mpl_book_ch_01_CXXFLAGS = $(BOOST_CFLAGS)
mpl_book_ch_01_LDADD = $(BOOST_LIBS)
