# rmol/config
include $(top_srcdir)/Makefile.common

## Source directory

DISTCLEANFILES = rmol-paths.hpp

MAINTAINERCLEANFILES = Makefile.in

EXTRA_DIST = rmol-paths.hpp

# Targets
all-local: rmol-paths.hpp

rmol-paths.hpp: Makefile
	@echo '#ifndef __RMOL_PATHS_HPP' > $@
	@echo '#define __RMOL_PATHS_HPP' >> $@
	@echo >> $@
	@echo '#define PACKAGE "rmol"' >> $@
	@echo '#define PACKAGE_NAME "RMOL"' >> $@
	@echo '#define PACKAGE_VERSION "@VERSION@"' >> $@
	@echo '#define PREFIXDIR "$(prefix)"' >> $@
	@echo '#define BINDIR "$(bindir)"' >> $@
	@echo '#define LIBEXECDIR "$(libexecdir)"' >> $@
	@echo '#define DATADIR "$(datadir)"' >> $@
	@echo '#define DOCDIR "$(docdir)"' >> $@
	@echo '#define STDAIR_SAMPLE_DIR "$(STDAIR_SAMPLE_DIR)"' >> $@
	@echo >> $@
	@echo '#endif // __RMOL_PATHS_HPP' >> $@
	@echo >> $@

