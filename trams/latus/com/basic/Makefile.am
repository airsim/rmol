## basic sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libcombas.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libcombas_debug.la
endif
libcombas_la_SOURCES= $(combas_h_sources) $(combas_cc_sources) 
libcombas_la_CXXFLAGS = $(CXXFLAGS_OPT)

libcombas_debug_la_SOURCES = $(combas_h_sources) $(combas_cc_sources)
libcombas_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/com/basic
#pkginclude_HEADERS = $(combas_h_sources)
