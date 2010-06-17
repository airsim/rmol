include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in


# Binaries (batches)
bin_PROGRAMS = rmol

rmol_SOURCES = $(batches_h_sources) $(batches_cc_sources)
rmol_CXXFLAGS = $(BOOST_CFLAGS)
#rmol_LDADD = 
rmol_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LIB) $(GSL_LIBS) \
	$(top_builddir)/stdair/core/libstdair.la \
	$(top_builddir)/rmol/core/librmol.la
