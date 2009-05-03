## test/com sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

MAINTAINERCLEANFILES = Makefile.in

EXTRA_DIST =

noinst_LTLIBRARIES= libcppunitcore.la

libcppunitcore_la_SOURCES = $(test_com_h_sources) $(test_com_cc_sources)
libcppunitcore_la_CXXFLAGS = $(CPPUNIT_CFLAGS)
