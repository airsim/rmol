include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = basic field bom factory command

EXTRA_DIST = config_msvc.h

lib_LTLIBRARIES = lib@PACKAGE@.la
if ENABLE_DEBUG
  lib_LTLIBRARIES += lib@PACKAGE@_debug.la
endif
lib@PACKAGE@_la_SOURCES = $(svc_h_sources) $(svc_cc_sources)
lib@PACKAGE@_la_LIBADD = $(top_builddir)/@PACKAGE@/basic/libbas.la \
			$(top_builddir)/@PACKAGE@/field/libfld.la \
			$(top_builddir)/@PACKAGE@/bom/libbom.la \
			$(top_builddir)/@PACKAGE@/factory/libfac.la \
			$(top_builddir)/@PACKAGE@/command/libcmd.la
lib@PACKAGE@_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

lib@PACKAGE@_debug_la_SOURCES = 
lib@PACKAGE@_debug_la_LIBADD = $(top_builddir)/@PACKAGE@/base/libbas_debug.la \
			$(top_builddir)/@PACKAGE@/field/libfld_debug.la \
			$(top_builddir)/@PACKAGE@/bom/libbom_debug.la \
			$(top_builddir)/@PACKAGE@/factory/libfac_debug.la \
			$(top_builddir)/@PACKAGE@/command/libcmd_debug.la
lib@PACKAGE@_debug_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

nobase_pkginclude_HEADERS = $(svc_h_sources)
nobase_nodist_pkginclude_HEADERS = $(top_builddir)/@PACKAGE@/config.h
