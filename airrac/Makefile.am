# airrac
include $(top_srcdir)/Makefile.common
include $(srcdir)/core/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in

SUBDIRS = basic bom factory command service core config batches

EXTRA_DIST = config_msvc.h


# Header files
nobase_pkginclude_HEADERS = $(airrac_service_h_sources)
#nobase_nodist_pkginclude_HEADERS = $(top_builddir)/@PACKAGE@/config.h
