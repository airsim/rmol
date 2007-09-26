include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = basic bom factory command service

lib_LTLIBRARIES = lib@PACKAGE@sim.la
if ENABLE_DEBUG
  lib_LTLIBRARIES += lib@PACKAGE@sim_debug.la
endif

lib@PACKAGE@sim_la_SOURCES = $(simservice_h_sources) $(simservice_cc_sources)
lib@PACKAGE@sim_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com.la \
			$(top_builddir)/@PACKAGE@/deg/lib@PACKAGE@deg.la \
			$(top_builddir)/@PACKAGE@/crs/lib@PACKAGE@crs.la \
			$(top_builddir)/@PACKAGE@/sim/basic/libsimbas.la \
			$(top_builddir)/@PACKAGE@/sim/bom/libsimbom.la \
			$(top_builddir)/@PACKAGE@/sim/factory/libsimfac.la \
			$(top_builddir)/@PACKAGE@/sim/command/libsimcmd.la \
			$(top_builddir)/@PACKAGE@/sim/service/libsimsvc.la
lib@PACKAGE@sim_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

lib@PACKAGE@sim_debug_la_SOURCES = $(simservice_h_sources) \
									$(simservice_cc_sources)
lib@PACKAGE@sim_debug_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com_debug.la \
			$(top_builddir)/@PACKAGE@/deg/lib@PACKAGE@deg_debug.la \
			$(top_builddir)/@PACKAGE@/crs/lib@PACKAGE@crs_debug.la \
			$(top_builddir)/@PACKAGE@/sim/basic/libsimbas_debug.la \
			$(top_builddir)/@PACKAGE@/sim/bom/libsimbom_debug.la \
			$(top_builddir)/@PACKAGE@/sim/factory/libsimfac_debug.la \
			$(top_builddir)/@PACKAGE@/sim/command/libsimcmd_debug.la \
			$(top_builddir)/@PACKAGE@/sim/service/libsimsvc_debug.la
lib@PACKAGE@sim_debug_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

#nobase_pkginclude_HEADERS = $(simservice_h_sources)
#nobase_nodist_pkginclude_HEADERS = $(top_builddir)/sim/config.h
