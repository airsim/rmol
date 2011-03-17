# airrac/batches
include $(top_srcdir)/Makefile.common

## Source directory


# Binaries (batches)
bin_PROGRAMS = airrac

#
MAINTAINERCLEANFILES = Makefile.in
CLEANFILES = ${bin_PROGRAMS:%=%_utfresults.xml} ${bin_PROGRAMS:%=%.log}

#
airrac_SOURCES = airrac.cpp
airrac_CXXFLAGS = $(BOOST_CFLAGS) $(STDAIR_CFLAGS)
airrac_LDADD =
airrac_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LIB) $(STDAIR_LIBS) \
	$(top_builddir)/airrac/core/libairrac.la
