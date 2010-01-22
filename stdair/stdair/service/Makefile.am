## service sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

#
noinst_LTLIBRARIES= libsvc.la

libsvc_la_SOURCES= $(svc_h_sources) $(svc_cc_sources) 
libsvc_la_CXXFLAGS =

# Header files
pkgincludedir = $(includedir)/stdair/service
pkginclude_HEADERS = $(svc_h_sources)
