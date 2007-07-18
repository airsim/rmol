## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libinvsvc.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libinvsvc_debug.la
endif
libinvsvc_la_SOURCES= $(invsvc_h_sources) $(invsvc_cc_sources) 
libinvsvc_la_CXXFLAGS = $(CXXFLAGS_OPT)

libinvsvc_debug_la_SOURCES = $(invsvc_h_sources) $(invsvc_cc_sources)
libinvsvc_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/inv/service
#pkginclude_HEADERS = $(invsvc_h_sources)
