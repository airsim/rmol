# StdAir manual pages

#
MAN_SRC_SUFFIX = doc
MAN_TARGET_SUFFIX = 3

man_MANS = stdair.3 stdair-config.1
MAN_SRC_BASE = stdair_man
MAN_SRC = $(MAN_SRC_BASE).$(MAN_SRC_SUFFIX)

EXTRA_DIST = $(man_MANS) $(MAN_SRC)

#
man-local: doxygen_man.cfg $(MAN_SRC)
	doxygen $<; \
	mv -f man3/* . && rmdir man3

clean-local:
	rm -f $(MAN_SRC_BASE).$(MAN_TARGET_SUFFIX)
