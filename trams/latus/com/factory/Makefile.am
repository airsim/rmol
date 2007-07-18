## factory sub-directory
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

noinst_LTLIBRARIES= libcomfac.la
if ENABLE_DEBUG
noinst_LTLIBRARIES += libcomfac_debug.la
endif
libcomfac_la_SOURCES= $(comfac_h_sources) $(comfac_cc_sources) 
libcomfac_la_CXXFLAGS = $(CXXFLAGS_OPT) $(BOOST_CPPFLAGS)

libcomfac_debug_la_SOURCES = $(comfac_h_sources) $(comfac_cc_sources)
libcomfac_debug_la_CXXFLAGS = $(CXXFLAGS_DEBUG) $(BOOST_CPPFLAGS)

#pkgincludedir = $(includedir)/@PACKAGE@/com/factory
#pkginclude_HEADERS = $(comfac_h_sources)
