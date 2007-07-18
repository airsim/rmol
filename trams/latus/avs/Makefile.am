include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = basic field bom factory command service

lib_LTLIBRARIES = libavs.la
if ENABLE_DEBUG
  lib_LTLIBRARIES += libavs_debug.la
endif
libavs_la_SOURCES = $(service_h_sources) $(service_cc_sources)
libavs_la_LIBADD = $(top_builddir)/avs/basic/libbas.la \
			$(top_builddir)/avs/field/libfld.la \
			$(top_builddir)/avs/bom/libbom.la \
			$(top_builddir)/avs/factory/libfac.la \
			$(top_builddir)/avs/command/libcmd.la \
			$(top_builddir)/avs/command/libsvc.la
libavs_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

libavs_debug_la_SOURCES = $(service_h_sources) $(service_cc_sources)
libavs_debug_la_LIBADD =$(top_builddir)/avs/basic/libbas_debug.la \
			$(top_builddir)/avs/field/libfld_debug.la \
			$(top_builddir)/avs/bom/libbom_debug.la \
			$(top_builddir)/avs/factory/libfac_debug.la \
			$(top_builddir)/avs/command/libcmd_debug.la \
			$(top_builddir)/avs/command/libavs_debug.la
libavs_debug_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

#nobase_pkginclude_HEADERS = $(service_h_sources)
#nobase_nodist_pkginclude_HEADERS = $(top_builddir)/avs/config.h
