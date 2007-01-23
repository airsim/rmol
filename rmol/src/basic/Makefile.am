## basic sub-directory

bas_h_sources = BasConst_General.hpp
bas_cc_sources = BasConst.cpp

#Install the headers in a versioned directory - e.g. rmollib-1.1:
library_includedir=$(includedir)/$(RMOL_LIBRARY_NAME)-$(RMOL_API_VERSION)/$(RMOL_LIBRARY_NAME)/bas
library_include_HEADERS = $(bas_h_sources)

INCLUDES = -I$(top_srcdir)

noinst_LTLIBRARIES= libbas.la
libbas_la_SOURCES= $(bas_h_sources) $(bas_cc_sources) 
