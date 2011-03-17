## airrac/command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

#
noinst_LTLIBRARIES = libairraccmd.la

libairraccmd_la_SOURCES = $(airrac_cmd_h_sources) $(airrac_cmd_cc_sources)
libairraccmd_la_CXXFLAGS = $(BOOST_CFLAGS) $(STDAIR_CFLAGS)
libairraccmd_la_LIBADD =
libairraccmd_la_LDFLAGS =

#
#pkgincludedir = $(includedir)/@PACKAGE@/command
#pkginclude_HEADERS = $(airrac_cmd_h_sources)
