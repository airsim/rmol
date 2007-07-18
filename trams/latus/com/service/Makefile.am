## command sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libcomsvc.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libcomsvc_debug.la
endif
libcomsvc_la_SOURCES= $(comsvc_h_sources) $(comsvc_cc_sources) 
libcomsvc_la_CXXFLAGS = $(CXXFLAGS_OPT)

libcomsvc_debug_la_SOURCES = $(comsvc_h_sources) $(comsvc_cc_sources)
libcomsvc_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/com/service
#pkginclude_HEADERS = $(comsvc_h_sources)
