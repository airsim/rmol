include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = basic bom factory command service

lib_LTLIBRARIES = lib@PACKAGE@fqt.la
if ENABLE_DEBUG
  lib_LTLIBRARIES += lib@PACKAGE@fqt_debug.la
endif

lib@PACKAGE@fqt_la_SOURCES = $(fqtservice_h_sources) $(fqtservice_cc_sources)
lib@PACKAGE@fqt_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com.la \
			$(top_builddir)/@PACKAGE@/fqt/basic/libfqtbas.la \
			$(top_builddir)/@PACKAGE@/fqt/bom/libfqtbom.la \
			$(top_builddir)/@PACKAGE@/fqt/factory/libfqtfac.la \
			$(top_builddir)/@PACKAGE@/fqt/command/libfqtcmd.la \
			$(top_builddir)/@PACKAGE@/fqt/service/libfqtsvc.la
lib@PACKAGE@fqt_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

lib@PACKAGE@fqt_debug_la_SOURCES = $(fqtservice_h_sources) \
									$(fqtservice_cc_sources)
lib@PACKAGE@fqt_debug_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/com/lib@PACKAGE@com_debug.la \
			$(top_builddir)/@PACKAGE@/fqt/basic/libfqtbas_debug.la \
			$(top_builddir)/@PACKAGE@/fqt/bom/libfqtbom_debug.la \
			$(top_builddir)/@PACKAGE@/fqt/factory/libfqtfac_debug.la \
			$(top_builddir)/@PACKAGE@/fqt/command/libfqtcmd_debug.la \
			$(top_builddir)/@PACKAGE@/fqt/service/libfqtsvc_debug.la
lib@PACKAGE@fqt_debug_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

#nobase_pkginclude_HEADERS = $(fqtservice_h_sources)
#nobase_nodist_pkginclude_HEADERS = $(top_builddir)/fqt/config.h
