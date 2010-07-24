## stdair top directory
include $(top_srcdir)/Makefile.common

ACLOCAL_AMFLAGS = -I config

AUTOMAKE_OPTIONS = dist-bzip2

if INFO_DOC
  INFO_DOC_DIR = info
endif

if HTML_DOC
  HTML_DOC_DIR = doc
endif

if RUN_TESTS
  TEST_DIR = test
endif

# Maintainance files
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 configure \
			config-h.in sic/stamp-h.in autogen.sh bootstrap

#EXTRA_DIST = @PACKAGE@.spec @PACKAGE@.m4 @PACKAGE@.pc Makefile.common 
EXTRA_DIST =

# Build in these directories:
SUBDIRS = stdair @PACKAGE@ man $(HTML_DOC_DIR) extracppunit $(TEST_DIR)


# Configuration helpers
bin_SCRIPTS = @PACKAGE@-config

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = @PACKAGE@.pc

m4datadir = $(datadir)/aclocal
m4data_DATA = @PACKAGE@.m4

# Targets
uninstall-local:
	rm -rf $(DESTDIR)$(includedir)/@PACKAGE@

dist-html:
	$(MAKE) -C doc dist-html

dist-tex:
	$(MAKE) -C doc dist-tex


snapshot: snapshot-src snapshot-html snapshot-tex


snapshot-src:
        $(MAKE) dist distdir=@PACKAGE_TARNAME@-`date +"%Y%m%d"`

snapshot-html:
	$(MAKE) -C doc dist-html html_tarname=@PACKAGE_TARNAME@-doc-`date +"%Y%m%d"`

snapshot-tex:
	$(MAKE) -C doc dist-tex tex_tarname=@PACKAGE_TARNAME@-tex-`date +"%Y%m%d"`

upload: upload-src upload-html upload-tex

upload-src: dist
	@UPLOAD_COMMAND@ @PACKAGE_TARNAME@-@VERSION@.tar.gz \
	@PACKAGE_TARNAME@-@VERSION@.tar.bz2

upload-html: dist-html
	@UPLOAD_COMMAND@ @PACKAGE_TARNAME@-doc-@VERSION@.tar.gz \
	@PACKAGE_TARNAME@-doc-@VERSION@.tar.bz2

upload-tex: dist-tex
	@UPLOAD_COMMAND@ @PACKAGE_TARNAME@-tex-@VERSION@.tar.gz \
	@PACKAGE_TARNAME@-tex-@VERSION@.tar.bz2
