#!/bin/sh

GNUPLOT_EXT=".gpl"
BASE_FILENAME=`basename $1 ${GNUPLOT_EXT}`
TARGET_EXT="png"
TARGET_FILENAME="${BASE_FILENAME}.${TARGET_EXT}"

gnuplot << _EOT
set term ${TARGET_EXT}
set output '${TARGET_FILENAME}'
load '$1'
_EOT

echo "Wrote the file ${TARGET_FILENAME}"
 
