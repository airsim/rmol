## bom sub-directory

bom_h_sources = BomAbstract.hpp Bucket.hpp BucketList.hpp BucketHolder.hpp \
				Demand.hpp DistributionParameterList.hpp Gaussian.hpp \
				PartialSumList.hpp VariateList.hpp PartialSumHolder.hpp \
				Emsr.hpp DemandGeneratorList.hpp MCUtils.hpp
bom_cc_sources = BomAbstract.cpp Bucket.cpp BucketHolder.cpp \
				 Demand.cpp Gaussian.cpp PartialSumHolder.cpp \
				Emsr.cpp DemandGeneratorList.cpp MCUtils.cpp

#Install the headers in a versioned directory - e.g. rmollib-1.1:
library_includedir=$(includedir)/$(RMOL_LIBRARY_NAME)-$(RMOL_API_VERSION)/$(RMOL_LIBRARY_NAME)/bom
library_include_HEADERS = $(bom_h_sources)

INCLUDES = -I$(top_srcdir)

noinst_LTLIBRARIES= libbom.la
libbom_la_SOURCES= $(bom_h_sources) $(bom_cc_sources) 
