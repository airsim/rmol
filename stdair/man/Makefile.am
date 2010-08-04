# StdAir manual pages

#
MAN_SRC_SUFFIX = doc
MAN_TARGET_SUFFIX = 1
MAN_DIR = man$(MAN_TARGET_SUFFIX)

MAN_SRC = stdair.doc stdair-config.doc
man_MANS = $(MAN_SRC:%.doc=%.$(MAN_TARGET_SUFFIX))

#EXTRA_DIST = $(man_MANS)

#
all-local: man-local

man-local: doxygen_man.cfg $(MAN_SRC)
	doxygen $< $(MAN_SRC); \
	mv -f $(MAN_DIR)/* . && rmdir $(MAN_DIR)

clean-local:
	rm -f $(man_MANS)
