include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = basic field bom factory command service

EXTRA_DIST = config_msvc.h

lib_LTLIBRARIES = lib@PACKAGE@.la
if ENABLE_DEBUG
  lib_LTLIBRARIES += lib@PACKAGE@_debug.la
endif
lib@PACKAGE@_la_SOURCES = $(service_h_sources) $(service_cc_sources)
lib@PACKAGE@_la_LIBADD = $(top_builddir)/@PACKAGE@/basic/libbas.la \
			$(top_builddir)/@PACKAGE@/field/libfld.la \
			$(top_builddir)/@PACKAGE@/bom/libbom.la \
			$(top_builddir)/@PACKAGE@/factory/libfac.la \
			$(top_builddir)/@PACKAGE@/command/libcmd.la \
			$(top_builddir)/@PACKAGE@/service/libsvc.la
lib@PACKAGE@_la_LDFLAGS = \
			$(BOOST_LIBS) $(BOOST_DATE_TIME_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) \
			$(GSL_LIBS) -version-info $(GENERIC_LIBRARY_VERSION)

lib@PACKAGE@_debug_la_SOURCES = $(service_h_sources) $(service_cc_sources)
lib@PACKAGE@_debug_la_LIBADD =$(top_builddir)/@PACKAGE@/basic/libbas_debug.la \
			$(top_builddir)/@PACKAGE@/field/libfld_debug.la \
			$(top_builddir)/@PACKAGE@/bom/libbom_debug.la \
			$(top_builddir)/@PACKAGE@/factory/libfac_debug.la \
			$(top_builddir)/@PACKAGE@/command/libcmd_debug.la \
			$(top_builddir)/@PACKAGE@/service/libsvc_debug.la
lib@PACKAGE@_debug_la_LDFLAGS = \
			$(BOOST_LIBS) $(BOOST_DATE_TIME_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) \
			$(GSL_LIBS) -version-info $(GENERIC_LIBRARY_VERSION)

bin_PROGRAMS = rmol
if ENABLE_DEBUG
  bin_PROGRAMS += rmol_debug
endif

rmol_SOURCES = $(bin_h_sources) $(bin_cc_sources)
rmol_CXXFLAGS = $(BOOST_CFLAGS)
rmol_LDADD = lib@PACKAGE@.la
rmol_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LIB)

rmol_debug_SOURCES = $(rmol_SOURCES)
rmol_debug_CXXFLAGS = $(BOOST_CFLAGS)
rmol_debug_LDFLAGS = $(rmol_LDFLAGS)
rmol_debug_LDADD = lib@PACKAGE@_debug.la

nobase_pkginclude_HEADERS = $(service_h_sources)
nobase_nodist_pkginclude_HEADERS = $(top_builddir)/@PACKAGE@/config.h
