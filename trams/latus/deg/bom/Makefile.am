## bom sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libdegbom.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libdegbom_debug.la
endif
libdegbom_la_SOURCES= $(degbom_h_sources) $(degbom_cc_sources) 
libdegbom_la_CXXFLAGS = $(CXXFLAGS_OPT) $(GSL_CFLAGS)
libdegbom_la_LIBADD = $(GSL_LIBS)

libdegbom_debug_la_SOURCES = $(degbom_h_sources) $(degbom_cc_sources)
libdegbom_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/deg/bom
#pkginclude_HEADERS = $(degbom_h_sources)
