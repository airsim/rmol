# rmol doc sub-directory
include $(top_srcdir)/doc/local/sources.mk
include $(top_srcdir)/doc/tutorial/sources.mk
include $(top_srcdir)/doc/tutorial/src/sources.mk
# RMOL
include $(top_srcdir)/rmol/basic/sources.mk
include $(top_srcdir)/rmol/bom/sources.mk
include $(top_srcdir)/rmol/factory/sources.mk
include $(top_srcdir)/rmol/command/sources.mk
include $(top_srcdir)/rmol/service/sources.mk
include $(top_srcdir)/rmol/core/sources.mk
include $(top_srcdir)/rmol/batches/sources.mk

SUBDIRS = images tutorial local

docdir = @docdir@

html_tarname = @PACKAGE_TARNAME@-doc-@PACKAGE_VERSION@
pdf_tarname = @PACKAGE_TARNAME@-pdf-@PACKAGE_VERSION@

noinst_DATA =
EXTRA_DIST = $(noinst_DATA)

# Targets
all-local: html-local

html-local: html/index.html

html/index.html: doxygen_html.cfg \
	$(doc_local_sources) $(html_local_sources) \
	$(doc_tutorial_sources) $(cpp_tutorial_sources) \
	$(rmol_service_h_sources) $(rmol_service_cc_sources) \
	$(rmol_batches_h_sources) $(rmol_batches_cc_sources) \
	$(rmol_bas_h_sources) $(rmol_bas_cc_sources) \
	$(rmol_bom_h_sources) $(rmol_bom_cc_sources) \
	$(rmol_fac_h_sources) $(rmol_fac_cc_sources) \
	$(rmol_cmd_h_sources) $(rmol_cmd_cc_sources) \
	$(rmol_svc_h_sources) $(rmol_svc_cc_sources)
	doxygen $<; \
	if test -d html; then \
		cp $(srcdir)/images/rmol_logo.png html; \
		cp $(srcdir)/images/sfx_logo.png html; \
		cp $(srcdir)/images/favicon.ico html; \
	fi

dist-html: html-local
	cp -a $(top_builddir)/doc/html $(top_builddir)/$(html_tarname)
	tar chof - $(top_builddir)/$(html_tarname) | \
		gzip --best -c > $(top_builddir)/$(html_tarname).tar.gz
	tar chof - $(top_builddir)/$(html_tarname) | \
		bzip2 -9 -c > $(top_builddir)/$(html_tarname).tar.bz2
	rm -rf $(top_builddir)/$(html_tarname)

dist-pdf: html-local
	cp -a $(top_builddir)/doc/latex $(top_builddir)/$(pdf_tarname)
	tar chof - $(top_builddir)/$(pdf_tarname) | \
		gzip --best -c > $(top_builddir)/$(pdf_tarname).tar.gz
	tar chof - $(top_builddir)/$(pdf_tarname) | \
		bzip2 -9 -c > $(top_builddir)/$(pdf_tarname).tar.bz2
	rm -rf $(top_builddir)/$(pdf_tarname)

install-data-local: html-local
	$(mkinstalldirs) $(DESTDIR)$(docdir)
	if test -d html; then \
		$(mkinstalldirs) $(DESTDIR)$(docdir)/html; \
		for f in html/*; do \
			$(INSTALL_DATA) $$f $(DESTDIR)$(docdir)/html; \
		done \
	fi
	$(mkinstalldirs) $(DESTDIR)$(docdir)
	if test -d latex; then \
		$(mkinstalldirs) $(DESTDIR)$(docdir)/latex; \
		for f in latex/*; do \
			$(INSTALL_DATA) $$f $(DESTDIR)$(docdir)/latex; \
		done \
	fi

uninstall-local:
	rm -rf $(DESTDIR)$(docdir)

clean-local:
	rm -rf html latex *.log *.tag
