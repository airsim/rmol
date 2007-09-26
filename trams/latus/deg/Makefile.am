include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = basic bom factory command service

lib_LTLIBRARIES = lib@PACKAGE@deg.la
if ENABLE_DEBUG
  lib_LTLIBRARIES += lib@PACKAGE@deg_debug.la
endif

lib@PACKAGE@deg_la_SOURCES = $(degservice_h_sources) $(degservice_cc_sources)
lib@PACKAGE@deg_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com.la \
			$(top_builddir)/@PACKAGE@/deg/basic/libdegbas.la \
			$(top_builddir)/@PACKAGE@/deg/bom/libdegbom.la \
			$(top_builddir)/@PACKAGE@/deg/factory/libdegfac.la \
			$(top_builddir)/@PACKAGE@/deg/command/libdegcmd.la \
			$(top_builddir)/@PACKAGE@/deg/service/libdegsvc.la
lib@PACKAGE@deg_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

lib@PACKAGE@deg_debug_la_SOURCES = $(degservice_h_sources) \
									$(degservice_cc_sources)
lib@PACKAGE@deg_debug_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com_debug.la \
			$(top_builddir)/@PACKAGE@/deg/basic/libdegbas_debug.la \
			$(top_builddir)/@PACKAGE@/deg/bom/libdegbom_debug.la \
			$(top_builddir)/@PACKAGE@/deg/factory/libdegfac_debug.la \
			$(top_builddir)/@PACKAGE@/deg/command/libdegcmd_debug.la \
			$(top_builddir)/@PACKAGE@/deg/service/libdegsvc_debug.la
lib@PACKAGE@deg_debug_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

#nobase_pkginclude_HEADERS = $(degservice_h_sources)
#nobase_nodist_pkginclude_HEADERS = $(top_builddir)/deg/config.h
