# rmol/batches
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in


# Binaries (batches)
bin_PROGRAMS = rmol

rmol_SOURCES = $(rmol_batches_h_sources) $(rmol_batches_cc_sources)
rmol_CXXFLAGS = $(BOOST_CFLAGS) $(STDAIR_CFLAGS)
#rmol_LDADD = 
rmol_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LIB) $(GSL_LIBS) $(STDAIR_LIBS) \
	$(top_builddir)/rmol/core/librmol.la

