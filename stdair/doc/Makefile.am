include $(top_srcdir)/doc/local/sources.mk
include $(top_srcdir)/doc/tutorial/sources.mk
include $(top_srcdir)/doc/tutorial/src/sources.mk
include $(top_srcdir)/@PACKAGE@/basic/sources.mk
include $(top_srcdir)/@PACKAGE@/bom/sources.mk
include $(top_srcdir)/@PACKAGE@/factory/sources.mk
#include $(top_srcdir)/@PACKAGE@/command/sources.mk
#include $(top_srcdir)/@PACKAGE@/service/sources.mk
include $(top_srcdir)/@PACKAGE@/core/sources.mk

SUBDIRS = images tutorial local

docdir = @docdir@

html_tarname = @PACKAGE_TARNAME@-html-doc-@PACKAGE_VERSION@

noinst_DATA = sourceforge/howto_release_stdair.html.in
EXTRA_DIST = $(noinst_DATA)

# Targets
all-local: html-local

html-local: html/index.html

html/index.html: doxygen_html.cfg \
	$(doc_local_sources) $(html_local_sources) \
	$(doc_tutorial_sources) $(cpp_tutorial_sources) \
	$(service_h_sources) $(service_cc_sources) \
	$(bas_h_sources) $(bas_cc_sources) \
	$(bom_h_sources) $(bom_cc_sources) \
	$(fac_h_sources) $(fac_cc_sources) \
	$(dba_h_sources) $(dba_cc_sources) \
	$(cmd_h_sources) $(cmd_cc_sources) \
	$(svc_h_sources) $(svc_cc_sources)
	doxygen $<; \
	if test -d html; then \
		cp $(srcdir)/images/stdair_logo.png html; \
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

install-data-local: html-local
	$(mkinstalldirs) $(DESTDIR)$(docdir)
	if test -d html; then \
		$(mkinstalldirs) $(DESTDIR)$(docdir)/html; \
		for f in html/*; do \
			$(INSTALL_DATA) $$f $(DESTDIR)$(docdir)/html; \
		done \
	fi

uninstall-local:
	rm -rf $(DESTDIR)$(docdir)

clean-local:
	rm -rf html *.log *.tag
