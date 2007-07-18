## bom sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libcombom.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libcombom_debug.la
endif
libcombom_la_SOURCES= $(combom_h_sources) $(combom_cc_sources) 
libcombom_la_CXXFLAGS = $(CXXFLAGS_OPT)
libcombom_la_LIBADD = $(GSL_LIBS)

libcombom_debug_la_SOURCES = $(combom_h_sources) $(combom_cc_sources)
libcombom_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG)

#pkgincludedir = $(includedir)/@PACKAGE@/com/bom
#pkginclude_HEADERS = $(combom_h_sources)
