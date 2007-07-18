## bom sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libcrsbom.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libcrsbom_debug.la
endif
libcrsbom_la_SOURCES= $(crsbom_h_sources) $(crsbom_cc_sources) 
libcrsbom_la_CXXFLAGS = $(CXXFLAGS_OPT) $(GSL_CFLAGS)
libcrsbom_la_LIBADD = $(GSL_LIBS)

libcrsbom_debug_la_SOURCES = $(crsbom_h_sources) $(crsbom_cc_sources)
libcrsbom_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/crs/bom
#pkginclude_HEADERS = $(crsbom_h_sources)
