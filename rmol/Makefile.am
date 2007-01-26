## top directory

MAINTAINERCLEANFILES = Makefile.in aclocal.m4 configure \
			config-h.in sic/stamp-h.in

# Build in these directories:
SUBDIRS = $(RMOL_LIBRARY_NAME)

# Distribute these directories:
DIST_SUBDIRS = $(RMOL_LIBRARY_NAME)

# Configuration helpers
bin_SCRIPTS = rmol-config
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = rmollib-1.1.pc

EXTRA_DIST = autogen.sh bootstrap
