include $(top_srcdir)/doc/local/sources.mk
include $(top_srcdir)/doc/tutorial/sources.mk
include $(top_srcdir)/doc/tutorial/src/sources.mk
include $(top_srcdir)/@PACKAGE@/sources.mk
include $(top_srcdir)/@PACKAGE@/com/sources.mk
include $(top_srcdir)/@PACKAGE@/com/basic/sources.mk
include $(top_srcdir)/@PACKAGE@/com/field/sources.mk
include $(top_srcdir)/@PACKAGE@/com/bom/sources.mk
include $(top_srcdir)/@PACKAGE@/com/factory/sources.mk
include $(top_srcdir)/@PACKAGE@/com/command/sources.mk
include $(top_srcdir)/@PACKAGE@/com/service/sources.mk
include $(top_srcdir)/@PACKAGE@/deg/sources.mk
include $(top_srcdir)/@PACKAGE@/deg/basic/sources.mk
include $(top_srcdir)/@PACKAGE@/deg/field/sources.mk
include $(top_srcdir)/@PACKAGE@/deg/bom/sources.mk
include $(top_srcdir)/@PACKAGE@/deg/factory/sources.mk
include $(top_srcdir)/@PACKAGE@/deg/command/sources.mk
include $(top_srcdir)/@PACKAGE@/deg/service/sources.mk
include $(top_srcdir)/@PACKAGE@/sim/sources.mk
include $(top_srcdir)/@PACKAGE@/sim/basic/sources.mk
include $(top_srcdir)/@PACKAGE@/sim/field/sources.mk
include $(top_srcdir)/@PACKAGE@/sim/bom/sources.mk
include $(top_srcdir)/@PACKAGE@/sim/factory/sources.mk
include $(top_srcdir)/@PACKAGE@/sim/command/sources.mk
include $(top_srcdir)/@PACKAGE@/sim/service/sources.mk

SUBDIRS = images tutorial local

docdir = @docdir@

html_tarname = @PACKAGE_TARNAME@-html-doc-@PACKAGE_VERSION@

noinst_DATA = website/howto_to_release_@PACKAGE@.html.in
EXTRA_DIST = $(noinst_DATA)

# Targets
all-local: html-local

html-local: html/index.html

html/index.html: doxygen_html.cfg \
	$(doc_local_sources) $(html_local_sources) \
	$(doc_tutorial_sources) $(cpp_tutorial_sources) \
	$(service_h_sources) $(service_cc_sources) \
	$(comservice_h_sources) $(comservice_cc_sources) \
	$(combas_h_sources) $(combas_cc_sources) \
	$(comfld_h_sources) $(comfld_cc_sources) \
	$(combom_h_sources) $(combom_cc_sources) \
	$(comfac_h_sources) $(comfac_cc_sources) \
	$(comcmd_h_sources) $(comcmd_cc_sources) \
	$(comsvc_h_sources) $(comsvc_cc_sources) \
	$(degservice_h_sources) $(degservice_cc_sources) \
	$(degbas_h_sources) $(degbas_cc_sources) \
	$(degfld_h_sources) $(degfld_cc_sources) \
	$(degbom_h_sources) $(degbom_cc_sources) \
	$(degfac_h_sources) $(degfac_cc_sources) \
	$(degcmd_h_sources) $(degcmd_cc_sources) \
	$(degsvc_h_sources) $(degsvc_cc_sources) \
	$(simservice_h_sources) $(simservice_cc_sources) \
	$(simbas_h_sources) $(simbas_cc_sources) \
	$(simfld_h_sources) $(simfld_cc_sources) \
	$(simbom_h_sources) $(simbom_cc_sources) \
	$(simfac_h_sources) $(simfac_cc_sources) \
	$(simcmd_h_sources) $(simcmd_cc_sources) \
	$(simsvc_h_sources) $(simsvc_cc_sources)
	doxygen $<; \
	if test -d html; then \
		cp $(srcdir)/images/@PACKAGE@_logo.png html; \
		cp $(srcdir)/images/sfx_logo.png html; \
		cp $(srcdir)/images/favicon.ico html; \
		cp $(srcdir)/images/amadeus_logo.png html; \
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
