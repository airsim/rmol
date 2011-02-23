# rmol
include $(top_srcdir)/Makefile.common
include $(srcdir)/core/sources.mk

#
SUBDIRS = basic bom factory command service core config batches

#
MAINTAINERCLEANFILES = Makefile.in

EXTRA_DIST = config_msvc.h


# Header files
nobase_pkginclude_HEADERS = $(rmol_service_h_sources)
#nobase_nodist_pkginclude_HEADERS = $(top_builddir)/@PACKAGE@/config.h

