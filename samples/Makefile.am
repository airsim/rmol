## samples sub-directory of the StdAir project
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

##
SUBDIRS =

MAINTAINERCLEANFILES = Makefile.in Makefile

##
datadir = @datadir@
pkgdatadir = @pkgdatadir@
sampledir = @sampledir@

#
noinst_DATA = $(sample_csv_sources) 

EXTRA_DIST = $(noinst_DATA)

# Targets
install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(sampledir); \
	for f in $(sample_csv_sources); do \
		$(INSTALL_DATA) $$f $(DESTDIR)$(sampledir); \
	done

uninstall-local:
	rm -rf $(DESTDIR)$(sampledir)

clean-local:
	rm -rf *.log *.tag
