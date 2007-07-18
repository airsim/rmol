## basic sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libdegbas.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libdegbas_debug.la
endif
libdegbas_la_SOURCES= $(degbas_h_sources) $(degbas_cc_sources) 
libdegbas_la_CXXFLAGS = $(CXXFLAGS_OPT)

libdegbas_debug_la_SOURCES = $(degbas_h_sources) $(degbas_cc_sources)
libdegbas_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/deg/basic
#pkginclude_HEADERS = $(degbas_h_sources)
