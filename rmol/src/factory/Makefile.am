## factory sub-directory

fac_h_sources = FacAbstract.hpp FacSupervisor.hpp FacBucketHolder.hpp \
				FacPartialSumHolder.hpp
fac_cc_sources = FacAbstract.cpp FacSupervisor.cpp FacBucketHolder.cpp \
				FacPartialSumHolder.cpp

#Install the headers in a versioned directory - e.g. rmollib-1.1:
library_includedir=$(includedir)/$(RMOL_LIBRARY_NAME)-$(RMOL_API_VERSION)/$(RMOL_LIBRARY_NAME)/fac
library_include_HEADERS = $(fac_h_sources)

INCLUDES = -I$(top_srcdir)

noinst_LTLIBRARIES= libfac.la
libfac_la_SOURCES= $(fac_h_sources) $(fac_cc_sources) 
