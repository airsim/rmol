include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = basic bom factory command service

lib_LTLIBRARIES = lib@PACKAGE@tsp.la
if ENABLE_DEBUG
  lib_LTLIBRARIES += lib@PACKAGE@tsp_debug.la
endif
lib@PACKAGE@tsp_la_SOURCES = $(tspservice_h_sources) $(tspservice_cc_sources)
lib@PACKAGE@tsp_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com.la \
			$(top_builddir)/@PACKAGE@/tsp/basic/libtspbas.la \
			$(top_builddir)/@PACKAGE@/tsp/bom/libtspbom.la \
			$(top_builddir)/@PACKAGE@/tsp/factory/libtspfac.la \
			$(top_builddir)/@PACKAGE@/tsp/command/libtspcmd.la \
			$(top_builddir)/@PACKAGE@/tsp/service/libtspsvc.la
lib@PACKAGE@tsp_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

lib@PACKAGE@tsp_debug_la_SOURCES = $(tspservice_h_sources) \
									$(tspservice_cc_sources)
lib@PACKAGE@tsp_debug_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com_debug.la \
			$(top_builddir)/@PACKAGE@/tsp/basic/libtspbas_debug.la \
			$(top_builddir)/@PACKAGE@/tsp/bom/libtspbom_debug.la \
			$(top_builddir)/@PACKAGE@/tsp/factory/libtspfac_debug.la \
			$(top_builddir)/@PACKAGE@/tsp/command/libtspcmd_debug.la \
			$(top_builddir)/@PACKAGE@/tsp/service/libtspsvc_debug.la
lib@PACKAGE@tsp_debug_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

#nobase_pkginclude_HEADERS = $(tspservice_h_sources)
#nobase_nodist_pkginclude_HEADERS = $(top_builddir)/tsp/config.h
