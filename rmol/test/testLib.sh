#!/bin/sh

INSTALL_DIR=`grep "^prefix =" ../Makefile | cut -d"=" -d" " -f3`
TST_PROG=./optimise
RMOL_API_VERSION=`grep "^PACKAGE_VERSION =" ../Makefile | cut -d"=" -d" " -f3`
RMOL_LIBRARY_NAME=`grep "^PACKAGE =" ../Makefile | cut -d"=" -d" " -f3`
RMOL_LIB=lib${RMOL_LIBRARY_NAME}-${RMOL_API_VERSION}.so

if [ ! -x ${TST_PROG} ];
then
	echo "The sample program does not seem to have been compiled. Try 'make check' first."
	exit -1
fi

## 
# Get a few pieces of information about the library
PACKAGE=`grep "^PACKAGE =" ../Makefile | cut -d"=" -d" " -f3`
INSTALL_DIR=`grep "^prefix =" ../Makefile | cut -d"=" -d" " -f3`
ALT_INSTALL_DIR="../${PACKAGE}/.libs"

# Calculate the library version
GENERIC_VERSION=`grep "^GENERIC_LIBRARY_VERSION =" ../Makefile | cut -d"=" -d" " -f3`
GENERIC_VERSION_CURRENT=`echo ${GENERIC_VERSION} | cut -d":" -f1`
GENERIC_VERSION_REVISION=`echo ${GENERIC_VERSION} | cut -d":" -f2`
GENERIC_VERSION_AGE=`echo ${GENERIC_VERSION} | cut -d":" -f3`
LIB_VERSION="${GENERIC_VERSION_CURRENT}.${GENERIC_VERSION_AGE}.${GENERIC_VERSION_REVISION}"
RMOL_LIB="lib${PACKAGE}.so.${LIB_VERSION}"

if [ "${INSTALL_DIR}" = "/usr/local" ];
then
        LIBRARY_TYPE=`/usr/bin/file ${ALT_INSTALL_DIR}/lib/${RMOL_LIB} | cut -d"," -f4 | cut -d" " -f2`
else
        LIBRARY_TYPE=`/usr/bin/file ${INSTALL_DIR}/lib/${RMOL_LIB} | cut -d"," -f4 | cut -d" " -f2`
fi

##
# Whether or not the usage should be displayed
USAGE=0
if [ "$1" = "-h" -o "$1" = "-H" -o "$1" = "--h" -o "$1" = "--help" ];
then
        USAGE=1
fi

if [ "$USAGE" = "1" ];
then
	echo
	echo "Usage: $0 [<Number of random draws> [<Cabin capacity> [<CSV input filename>]]]"
	echo "By default:"
	echo "  * The number of random draws is 10,000."
	echo "  * The cabin capacity is 500 seats."
	echo "  * If no input filename is provided, an internal sample with 3 classes is used."
	echo
if [ "${INSTALL_DIR}" = "/usr/local" ];
then
        echo "The library (${RMOL_LIB}) is not installed, and taken from: ../${PACKAGE}/.libs"
else
        echo "The library (${RMOL_LIB}) is (will be) installed in: ${INSTALL_DIR}/lib"
fi
        echo
        exit 0
fi

${TST_PROG} $1 $2 $3

