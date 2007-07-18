include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = service

lib_LTLIBRARIES = lib@PACKAGE@inv.la
if ENABLE_DEBUG
  lib_LTLIBRARIES += lib@PACKAGE@inv_debug.la
endif

lib@PACKAGE@inv_la_SOURCES = $(invservice_h_sources) $(invservice_cc_sources)
lib@PACKAGE@inv_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/inv/service/libinvsvc.la
lib@PACKAGE@inv_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

lib@PACKAGE@inv_debug_la_SOURCES = $(invservice_h_sources) \
									$(invservice_cc_sources)
lib@PACKAGE@inv_debug_la_LIBADD = \
			$(top_builddir)/@PACKAGE@/inv/service/libinvsvc_debug.la
lib@PACKAGE@inv_debug_la_LDFLAGS = -version-info $(GENERIC_LIBRARY_VERSION)

#nobase_pkginclude_HEADERS = $(invservice_h_sources)
#nobase_nodist_pkginclude_HEADERS = $(top_builddir)/inv/config.h
