# airrac/config
include $(top_srcdir)/Makefile.common

## Source directory

DISTCLEANFILES = airrac-paths.hpp

MAINTAINERCLEANFILES = Makefile.in

EXTRA_DIST = airrac-paths.hpp

# Targets
all-local: airrac-paths.hpp

airrac-paths.hpp: Makefile
	@echo '#ifndef __AIRRAC_PATHS_HPP' > $@
	@echo '#define __AIRRAC_PATHS_HPP' >> $@
	@echo >> $@
	@echo '#define PACKAGE "airrac"' >> $@
	@echo '#define PACKAGE_NAME "AIRRAC"' >> $@
	@echo '#define PACKAGE_VERSION "@VERSION@"' >> $@
	@echo '#define PREFIXDIR "$(prefix)"' >> $@
	@echo '#define BINDIR "$(bindir)"' >> $@
	@echo '#define LIBEXECDIR "$(libexecdir)"' >> $@
	@echo '#define DATADIR "$(datadir)"' >> $@
	@echo '#define DOCDIR "$(docdir)"' >> $@
	@echo '#define STDAIR_SAMPLE_DIR "$(STDAIR_SAMPLE_DIR)"' >> $@
	@echo >> $@
	@echo '#endif // __AIRRAC_PATHS_HPP' >> $@
	@echo >> $@
