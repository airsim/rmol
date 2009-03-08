## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

MAINTAINERCLEANFILES = Makefile.in

noinst_LTLIBRARIES= libcppunitcore.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libcppunitcore_debug.la
endif

libcppunitcore_la_SOURCES = $(test_com_h_sources) $(test_com_cc_sources)
libcppunitcore_la_CXXFLAGS = $(CXXFLAGS_OPT) $(CPPUNIT_CFLAGS)

libcppunitcore_debug_la_SOURCES = $(test_com_h_sources) $(test_com_cc_sources)
libcppunitcore_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG) $(CPPUNIT_CFLAGS)

EXTRA_DIST =
