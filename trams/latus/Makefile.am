include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

#SUBDIRS = com deg ucm rms inv avs tsp crs sim service
SUBDIRS = com deg inv tsp crs sim

EXTRA_DIST = config_msvc.h

lib_LTLIBRARIES = lib@PACKAGE@.la
if ENABLE_DEBUG
  lib_LTLIBRARIES += lib@PACKAGE@_debug.la
endif
lib@PACKAGE@_la_SOURCES = $(service_h_sources) $(service_cc_sources)
lib@PACKAGE@_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com.la \
			$(top_builddir)/@PACKAGE@/crs/lib@PACKAGE@crs.la \
			$(top_builddir)/@PACKAGE@/tsp/lib@PACKAGE@tsp.la \
			$(top_builddir)/@PACKAGE@/inv/lib@PACKAGE@inv.la \
			$(top_builddir)/@PACKAGE@/deg/lib@PACKAGE@deg.la \
			$(top_builddir)/@PACKAGE@/sim/lib@PACKAGE@sim.la
lib@PACKAGE@_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

lib@PACKAGE@_debug_la_SOURCES = $(service_h_sources) $(service_cc_sources)
lib@PACKAGE@_debug_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com_debug.la \
			$(top_builddir)/@PACKAGE@/crs/lib@PACKAGE@crs_debug.la \
			$(top_builddir)/@PACKAGE@/tsp/lib@PACKAGE@tsp_debug.la \
			$(top_builddir)/@PACKAGE@/inv/lib@PACKAGE@inv_debug.la \
			$(top_builddir)/@PACKAGE@/deg/lib@PACKAGE@deg_debug.la \
			$(top_builddir)/@PACKAGE@/sim/lib@PACKAGE@sim_debug.la
lib@PACKAGE@_debug_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

nobase_pkginclude_HEADERS = $(service_h_sources)
nobase_nodist_pkginclude_HEADERS = $(top_builddir)/@PACKAGE@/config.h
