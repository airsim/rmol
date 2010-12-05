include $(top_srcdir)/Makefile.common

## Source directory
DISTCLEANFILES = stdair-paths.hpp

MAINTAINERCLEANFILES = Makefile.in

EXTRA_DIST = stdair-paths.hpp

# Targets
all-local: stdair-paths.hpp

stdair-paths.hpp: Makefile
	@echo '#ifndef __STDAIR_PATHS_HPP' > $@
	@echo '#define __STDAIR_PATHS_HPP' >> $@
	@echo '#define PACKAGE "stdair"' >> $@
	@echo '#define PACKAGE_NAME "STDAIR"' >> $@
	@echo '#define PACKAGE_VERSION "@VERSION@"' >> $@
	@echo '#define PREFIXDIR "$(prefix)"' >> $@
	@echo '#define BINDIR "$(bindir)"' >> $@
	@echo '#define LIBEXECDIR "$(libexecdir)"' >> $@
	@echo '#define DATADIR "$(datadir)"' >> $@
	@echo '#define DOCDIR "$(docdir)"' >> $@
	@echo '#endif // __STDAIR_PATHS_HPP' >> $@
