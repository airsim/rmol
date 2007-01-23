## field sub-directory

fld_h_sources = FldDistributionParameters.hpp FldYieldRange.hpp
fld_cc_sources = FldDistributionParameters.cpp FldYieldRange.cpp

#Install the headers in a versioned directory - e.g. rmollib-1.1:
library_includedir=$(includedir)/$(RMOL_LIBRARY_NAME)-$(RMOL_API_VERSION)/$(RMOL_LIBRARY_NAME)/fld
library_include_HEADERS = $(fld_h_sources)

INCLUDES = -I$(top_srcdir)

noinst_LTLIBRARIES= libfld.la
libfld_la_SOURCES= $(fld_h_sources) $(fld_cc_sources) 
