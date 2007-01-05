#!/bin/sh

INSTALL_DIR=`make print_INSTALL_ROOTDIR_value`
TST_PROG=`make print_FULL_BIN_NAME_value`
RMOL_LIB=`make print_RMOL_LIB_value`

if [ ! -x ${TST_PROG} ];
then
	echo "The sample program does not seem to have been compiled. Try 'make test' first."
	exit -1
fi

if [ "$1" = "-h" -o "$1" = "-H" -o "$1" = "--h" -o "$1" = "--help" ];
then
	echo "Usage: $0 [<Number of random draws> <Cabin capacity> <CSV input filename>]"
	echo "By default:"
	echo "  * The number of random draws is 10,000."
	echo "  * The cabin capacity is 500 seats."
	echo "  * If no input filename is provided, an internal sample with 3 classes is used."
	echo
	echo "The library (${RMOL_LIB}) is installed in: ${INSTALL_DIR}/lib"
	exit 0
fi

${TST_PROG} $1 $2 $3
