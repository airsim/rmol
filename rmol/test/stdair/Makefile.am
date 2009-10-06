## test sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

##
SUBDIRS =

EXTRA_DIST =
##

check_PROGRAMS = stdair

stdair_SOURCES = stdair.cpp
stdair_CXXFLAGS= $(BOOST_CFLAGS)
stdair_LDADD = 
stdair_LDFLAGS = $(BOOST_LIBS) \
	$(top_builddir)/stdair/core/libstdair.la
	$(top_builddir)/@PACKAGE@/core/lib@PACKAGE@.la

