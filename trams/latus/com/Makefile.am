include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = basic field bom factory command service

lib_LTLIBRARIES = lib@PACKAGE@com.la
if ENABLE_DEBUG
  lib_LTLIBRARIES += lib@PACKAGE@com_debug.la
endif
lib@PACKAGE@com_la_SOURCES = $(comservice_h_sources) $(comservice_cc_sources)
lib@PACKAGE@com_la_LIBADD = $(BOOST_LDFLAGS) $(BOOST_DATE_TIME_LIB) \
		$(top_builddir)/@PACKAGE@/com/basic/libcombas.la \
		$(top_builddir)/@PACKAGE@/com/field/libcomfld.la \
		$(top_builddir)/@PACKAGE@/com/bom/libcombom.la \
		$(top_builddir)/@PACKAGE@/com/factory/libcomfac.la \
		$(top_builddir)/@PACKAGE@/com/command/libcomcmd.la \
		$(top_builddir)/@PACKAGE@/com/service/libcomsvc.la
lib@PACKAGE@com_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

lib@PACKAGE@com_debug_la_SOURCES = $(comservice_h_sources) \
									$(comservice_cc_sources)
lib@PACKAGE@com_debug_la_LIBADD = $(BOOST_LDFLAGS) $(BOOST_DATE_TIME_LIB) \
		$(top_builddir)/@PACKAGE@/com/basic/libcombas_debug.la \
		$(top_builddir)/@PACKAGE@/com/field/libcomfld_debug.la \
		$(top_builddir)/@PACKAGE@/com/bom/libcombom_debug.la \
		$(top_builddir)/@PACKAGE@/com/factory/libcomfac_debug.la \
		$(top_builddir)/@PACKAGE@/com/command/libcomcmd_debug.la \
		$(top_builddir)/@PACKAGE@/com/service/libcomsvc_debug.la
lib@PACKAGE@com_debug_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

#nobase_pkginclude_HEADERS = $(comservice_h_sources)
#nobase_nodist_pkginclude_HEADERS = $(top_builddir)/com/config.h
