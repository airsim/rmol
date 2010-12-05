## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libcmd.la

libcmd_la_SOURCES= $(cmd_h_sources) $(cmd_cc_sources) 
libcmd_la_CXXFLAGS = $(BOOST_CFLAGS)

#pkgincludedir = $(includedir)/@PACKAGE@/command
#pkginclude_HEADERS = $(cmd_h_sources)
