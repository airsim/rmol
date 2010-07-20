## rmol/command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

#
noinst_LTLIBRARIES = librmolcmd.la

librmolcmd_la_SOURCES = $(rmol_cmd_h_sources) $(rmol_cmd_cc_sources) 
librmolcmd_la_CXXFLAGS = $(BOOST_CFLAGS)


#pkgincludedir = $(includedir)/@PACKAGE@/command
#pkginclude_HEADERS = $(cmd_h_sources)
