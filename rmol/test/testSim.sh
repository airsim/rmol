#!/bin/sh

INSTALL_DIR=`grep "^prefix =" ../Makefile | cut -d"=" -d" " -f3`
TST_PROG=./simulate
RMOL_API_VERSION=`grep "^PACKAGE_VERSION =" ../Makefile | cut -d"=" -d" " -f3`
RMOL_LIBRARY_NAME=`grep "^PACKAGE =" ../Makefile | cut -d"=" -d" " -f3`
RMOL_LIB=lib${RMOL_LIBRARY_NAME}-${RMOL_API_VERSION}.so

if [ ! -x ${TST_PROG} ];
then
	echo "The sample program does not seem to have been compiled. Try 'make check' first."
	exit -1
fi

if [ "$1" = "-h" -o "$1" = "-H" -o "$1" = "--h" -o "$1" = "--help" ];
then
	echo "Usage: $0 [<Number of random draws> <Rate (lambda)>]"
	echo "By default:"
	echo "  * The number of random draws is 1,000."
	echo "  * The rate is 10 events per unit of time."
	echo
	echo "The library (${RMOL_LIB}) is installed in: ${INSTALL_DIR}/lib"
	exit 0
fi

${TST_PROG} $1 $2
