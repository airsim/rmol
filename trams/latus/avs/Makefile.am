include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = basic bom factory command service

lib_LTLIBRARIES = libavs.la
if ENABLE_DEBUG
  lib_LTLIBRARIES += libavs_debug.la
endif
libavs_la_SOURCES = $(service_h_sources) $(service_cc_sources)
libavs_la_LIBADD = 
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com_debug.la \
			$(top_builddir)/@PACKAGE@/avs/basic/libavsbas.la \
			$(top_builddir)/@PACKAGE@/avs/bom/libavsbom.la \
			$(top_builddir)/@PACKAGE@/avs/factory/libavsfac.la \
			$(top_builddir)/@PACKAGE@/avs/command/libavscmd.la \
			$(top_builddir)/@PACKAGE@/avs/service/libavssvc.la
libavs_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

libavs_debug_la_SOURCES = $(service_h_sources) $(service_cc_sources)
libavs_debug_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com_debug.la \
			$(top_builddir)/@PACKAGE@/avs/basic/libavsbas_debug.la \
			$(top_builddir)/@PACKAGE@/avs/bom/libavsbom_debug.la \
			$(top_builddir)/@PACKAGE@/avs/factory/libavsfac_debug.la \
			$(top_builddir)/@PACKAGE@/avs/command/libavscmd_debug.la \
			$(top_builddir)/@PACKAGE@/avs/service/libavssvc_debug.la
libavs_debug_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

#nobase_pkginclude_HEADERS = $(service_h_sources)
#nobase_nodist_pkginclude_HEADERS = $(top_builddir)/avs/config.h
