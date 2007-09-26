include $(top_srcdir)/doc/local/sources.mk
include $(top_srcdir)/doc/tutorial/sources.mk
include $(top_srcdir)/doc/tutorial/src/sources.mk
include $(top_srcdir)/@PACKAGE@/sources.mk
include $(top_srcdir)/@PACKAGE@/com/sources.mk
include $(top_srcdir)/@PACKAGE@/com/basic/sources.mk
include $(top_srcdir)/@PACKAGE@/com/bom/sources.mk
include $(top_srcdir)/@PACKAGE@/com/factory/sources.mk
include $(top_srcdir)/@PACKAGE@/com/command/sources.mk
include $(top_srcdir)/@PACKAGE@/com/service/sources.mk
include $(top_srcdir)/@PACKAGE@/deg/sources.mk
include $(top_srcdir)/@PACKAGE@/deg/basic/sources.mk
include $(top_srcdir)/@PACKAGE@/deg/bom/sources.mk
include $(top_srcdir)/@PACKAGE@/deg/factory/sources.mk
include $(top_srcdir)/@PACKAGE@/deg/command/sources.mk
include $(top_srcdir)/@PACKAGE@/deg/service/sources.mk
include $(top_srcdir)/@PACKAGE@/ucm/sources.mk
include $(top_srcdir)/@PACKAGE@/ucm/basic/sources.mk
include $(top_srcdir)/@PACKAGE@/ucm/bom/sources.mk
include $(top_srcdir)/@PACKAGE@/ucm/factory/sources.mk
include $(top_srcdir)/@PACKAGE@/ucm/command/sources.mk
include $(top_srcdir)/@PACKAGE@/ucm/service/sources.mk
include $(top_srcdir)/@PACKAGE@/sim/sources.mk
include $(top_srcdir)/@PACKAGE@/sim/basic/sources.mk
include $(top_srcdir)/@PACKAGE@/sim/bom/sources.mk
include $(top_srcdir)/@PACKAGE@/sim/factory/sources.mk
include $(top_srcdir)/@PACKAGE@/sim/command/sources.mk
include $(top_srcdir)/@PACKAGE@/sim/service/sources.mk
include $(top_srcdir)/@PACKAGE@/crs/sources.mk
include $(top_srcdir)/@PACKAGE@/crs/basic/sources.mk
include $(top_srcdir)/@PACKAGE@/crs/bom/sources.mk
include $(top_srcdir)/@PACKAGE@/crs/factory/sources.mk
include $(top_srcdir)/@PACKAGE@/crs/command/sources.mk
include $(top_srcdir)/@PACKAGE@/crs/service/sources.mk
include $(top_srcdir)/@PACKAGE@/fqt/sources.mk
include $(top_srcdir)/@PACKAGE@/fqt/basic/sources.mk
include $(top_srcdir)/@PACKAGE@/fqt/bom/sources.mk
include $(top_srcdir)/@PACKAGE@/fqt/factory/sources.mk
include $(top_srcdir)/@PACKAGE@/fqt/command/sources.mk
include $(top_srcdir)/@PACKAGE@/fqt/service/sources.mk
include $(top_srcdir)/@PACKAGE@/tsp/sources.mk
include $(top_srcdir)/@PACKAGE@/tsp/basic/sources.mk
include $(top_srcdir)/@PACKAGE@/tsp/bom/sources.mk
include $(top_srcdir)/@PACKAGE@/tsp/factory/sources.mk
include $(top_srcdir)/@PACKAGE@/tsp/command/sources.mk
include $(top_srcdir)/@PACKAGE@/tsp/service/sources.mk
include $(top_srcdir)/@PACKAGE@/inv/sources.mk
include $(top_srcdir)/@PACKAGE@/inv/basic/sources.mk
include $(top_srcdir)/@PACKAGE@/inv/bom/sources.mk
include $(top_srcdir)/@PACKAGE@/inv/factory/sources.mk
include $(top_srcdir)/@PACKAGE@/inv/command/sources.mk
include $(top_srcdir)/@PACKAGE@/inv/service/sources.mk
include $(top_srcdir)/@PACKAGE@/rms/sources.mk
include $(top_srcdir)/@PACKAGE@/rms/basic/sources.mk
include $(top_srcdir)/@PACKAGE@/rms/bom/sources.mk
include $(top_srcdir)/@PACKAGE@/rms/factory/sources.mk
include $(top_srcdir)/@PACKAGE@/rms/command/sources.mk
include $(top_srcdir)/@PACKAGE@/rms/service/sources.mk

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
	$(combom_h_sources) $(combom_cc_sources) \
	$(comfac_h_sources) $(comfac_cc_sources) \
	$(comcmd_h_sources) $(comcmd_cc_sources) \
	$(comsvc_h_sources) $(comsvc_cc_sources) \
	$(degservice_h_sources) $(degservice_cc_sources) \
	$(degbas_h_sources) $(degbas_cc_sources) \
	$(degbom_h_sources) $(degbom_cc_sources) \
	$(degfac_h_sources) $(degfac_cc_sources) \
	$(degcmd_h_sources) $(degcmd_cc_sources) \
	$(degsvc_h_sources) $(degsvc_cc_sources) \
	$(ucmservice_h_sources) $(ucmservice_cc_sources) \
	$(ucmbas_h_sources) $(ucmbas_cc_sources) \
	$(ucmbom_h_sources) $(ucmbom_cc_sources) \
	$(ucmfac_h_sources) $(ucmfac_cc_sources) \
	$(ucmcmd_h_sources) $(ucmcmd_cc_sources) \
	$(ucmsvc_h_sources) $(ucmsvc_cc_sources) \
	$(simservice_h_sources) $(simservice_cc_sources) \
	$(simbas_h_sources) $(simbas_cc_sources) \
	$(simbom_h_sources) $(simbom_cc_sources) \
	$(simfac_h_sources) $(simfac_cc_sources) \
	$(simcmd_h_sources) $(simcmd_cc_sources) \
	$(simsvc_h_sources) $(simsvc_cc_sources) \
	$(crsservice_h_sources) $(crsservice_cc_sources) \
	$(crsbas_h_sources) $(crsbas_cc_sources) \
	$(crsbom_h_sources) $(crsbom_cc_sources) \
	$(crsfac_h_sources) $(crsfac_cc_sources) \
	$(crscmd_h_sources) $(crscmd_cc_sources) \
	$(crssvc_h_sources) $(crssvc_cc_sources) \
	$(fqtservice_h_sources) $(fqtservice_cc_sources) \
	$(fqtbas_h_sources) $(fqtbas_cc_sources) \
	$(fqtbom_h_sources) $(fqtbom_cc_sources) \
	$(fqtfac_h_sources) $(fqtfac_cc_sources) \
	$(fqtcmd_h_sources) $(fqtcmd_cc_sources) \
	$(fqtsvc_h_sources) $(fqtsvc_cc_sources) \
	$(tspservice_h_sources) $(tspservice_cc_sources) \
	$(tspbas_h_sources) $(tspbas_cc_sources) \
	$(tspbom_h_sources) $(tspbom_cc_sources) \
	$(tspfac_h_sources) $(tspfac_cc_sources) \
	$(tspcmd_h_sources) $(tspcmd_cc_sources) \
	$(tspsvc_h_sources) $(tspsvc_cc_sources) \
	$(invservice_h_sources) $(invservice_cc_sources) \
	$(invbas_h_sources) $(invbas_cc_sources) \
	$(invbom_h_sources) $(invbom_cc_sources) \
	$(invfac_h_sources) $(invfac_cc_sources) \
	$(invcmd_h_sources) $(invcmd_cc_sources) \
	$(invsvc_h_sources) $(invsvc_cc_sources) \
	$(rmsservice_h_sources) $(rmsservice_cc_sources) \
	$(rmsbas_h_sources) $(rmsbas_cc_sources) \
	$(rmsbom_h_sources) $(rmsbom_cc_sources) \
	$(rmsfac_h_sources) $(rmsfac_cc_sources) \
	$(rmscmd_h_sources) $(rmscmd_cc_sources) \
	$(rmssvc_h_sources) $(rmssvc_cc_sources)
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
