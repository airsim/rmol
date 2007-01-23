## Source directory

#SUBDIRS = basic field bom factory command

svc_h_sources = RMOL_Service.hpp
svc_cc_sources = RMOL_Service.cpp

library_includedir=$(includedir)/$(RMOL_LIBRARY_NAME)-$(RMOL_API_VERSION)/$(RMOL_LIBRARY_NAME)
library_include_HEADERS = $(svc_h_sources)

INCLUDES = -I$(top_srcdir)

lib_LTLIBRARIES= libsvc-1.1.la
libbaslib_1_0_la_SOURCES= $(svc_h_sources) $(svc_cc_sources)
libbaslib_1_0_la_LIBADD= bas/libbas.la fld/libfld.la bom/libbom.la \
						fac/libfac.la cmd/libcmd.la
libbaslib_1_0_la_LDFLAGS= -version-info $(RMOL_LIBRARY_VERSION) -release $(RMOL_RELEASE)
