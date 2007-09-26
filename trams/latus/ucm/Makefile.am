include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = basic bom factory command service

lib_LTLIBRARIES = lib@PACKAGE@ucm.la
if ENABLE_DEBUG
  lib_LTLIBRARIES += lib@PACKAGE@ucm_debug.la
endif

lib@PACKAGE@ucm_la_SOURCES = $(ucmservice_h_sources) $(ucmservice_cc_sources)
lib@PACKAGE@ucm_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com.la \
			$(top_builddir)/@PACKAGE@/ucm/basic/libucmbas.la \
			$(top_builddir)/@PACKAGE@/ucm/bom/libucmbom.la \
			$(top_builddir)/@PACKAGE@/ucm/factory/libucmfac.la \
			$(top_builddir)/@PACKAGE@/ucm/command/libucmcmd.la \
			$(top_builddir)/@PACKAGE@/ucm/service/libucmsvc.la
lib@PACKAGE@ucm_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

lib@PACKAGE@ucm_debug_la_SOURCES = $(ucmservice_h_sources) \
									$(ucmservice_cc_sources)
lib@PACKAGE@ucm_debug_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com_debug.la \
			$(top_builddir)/@PACKAGE@/ucm/basic/libucmbas_debug.la \
			$(top_builddir)/@PACKAGE@/ucm/bom/libucmbom_debug.la \
			$(top_builddir)/@PACKAGE@/ucm/factory/libucmfac_debug.la \
			$(top_builddir)/@PACKAGE@/ucm/command/libucmcmd_debug.la \
			$(top_builddir)/@PACKAGE@/ucm/service/libucmsvc_debug.la
lib@PACKAGE@ucm_debug_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

#nobase_pkginclude_HEADERS = $(ucmservice_h_sources)
#nobase_nodist_pkginclude_HEADERS = $(top_builddir)/ucm/config.h
