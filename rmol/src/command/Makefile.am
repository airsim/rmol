## command sub-directory

cmd_h_sources = FileMgr.hpp
cmd_cc_sources = FileMgr.cpp

#Install the headers in a versioned directory - e.g. rmollib-1.1:
library_includedir=$(includedir)/$(RMOL_LIBRARY_NAME)-$(RMOL_API_VERSION)/$(RMOL_LIBRARY_NAME)/cmd
library_include_HEADERS = $(cmd_h_sources)

INCLUDES = -I$(top_srcdir)

noinst_LTLIBRARIES= libcmd.la
libcmd_la_SOURCES= $(cmd_h_sources) $(cmd_cc_sources) 
