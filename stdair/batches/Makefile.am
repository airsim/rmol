# stdair/batches
include $(top_srcdir)/Makefile.common
include $(srcdir)/sources.mk

## Source directory

MAINTAINERCLEANFILES = Makefile.in


# Binaries (batches)
bin_PROGRAMS = stdair

stdair_SOURCES = $(stdair_batches_h_sources) $(stdair_batches_cc_sources)
stdair_CXXFLAGS = $(BOOST_CFLAGS)
stdair_LDADD = 
stdair_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LIB) \
	$(top_builddir)/stdair/libstdair.la
