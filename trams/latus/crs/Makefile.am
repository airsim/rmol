include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = basic field bom factory command service

lib_LTLIBRARIES = lib@PACKAGE@crs.la
if ENABLE_DEBUG
  lib_LTLIBRARIES += lib@PACKAGE@crs_debug.la
endif
lib@PACKAGE@crs_la_SOURCES = $(crsservice_h_sources) $(crsservice_cc_sources)
lib@PACKAGE@crs_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com.la \
			$(top_builddir)/@PACKAGE@/tsp/lib@PACKAGE@tsp.la \
			$(top_builddir)/@PACKAGE@/inv/lib@PACKAGE@inv.la \
			$(top_builddir)/@PACKAGE@/crs/basic/libcrsbas.la \
			$(top_builddir)/@PACKAGE@/crs/field/libcrsfld.la \
			$(top_builddir)/@PACKAGE@/crs/bom/libcrsbom.la \
			$(top_builddir)/@PACKAGE@/crs/factory/libcrsfac.la \
			$(top_builddir)/@PACKAGE@/crs/command/libcrscmd.la \
			$(top_builddir)/@PACKAGE@/crs/service/libcrssvc.la
lib@PACKAGE@crs_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

lib@PACKAGE@crs_debug_la_SOURCES = $(crsservice_h_sources) \
									$(crsservice_cc_sources)
lib@PACKAGE@crs_debug_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com_debug.la \
			$(top_builddir)/@PACKAGE@/tsp/lib@PACKAGE@tsp_debug.la \
			$(top_builddir)/@PACKAGE@/inv/lib@PACKAGE@inv_debug.la \
			$(top_builddir)/@PACKAGE@/crs/basic/libcrsbas_debug.la \
			$(top_builddir)/@PACKAGE@/crs/field/libcrsfld_debug.la \
			$(top_builddir)/@PACKAGE@/crs/bom/libcrsbom_debug.la \
			$(top_builddir)/@PACKAGE@/crs/factory/libcrsfac_debug.la \
			$(top_builddir)/@PACKAGE@/crs/command/libcrscmd_debug.la \
			$(top_builddir)/@PACKAGE@/crs/service/libcrssvc_debug.la
lib@PACKAGE@crs_debug_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

#nobase_pkginclude_HEADERS = $(crsservice_h_sources)
#nobase_nodist_pkginclude_HEADERS = $(top_builddir)/crs/config.h
