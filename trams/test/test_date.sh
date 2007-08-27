#!/bin/sh

INSTALL_DIR=`grep "^prefix =" ../Makefile | cut -d"=" -d" " -f3`
TST_PROG=./date
LATUS_API_VERSION=`grep "^LATUS_API_VERSION =" ../Makefile | cut -d"=" -d" " -f3`
LATUS_LIBRARY_NAME=`grep "^LATUS_LIBRARY_NAME =" ../Makefile | cut -d"=" -d" " -f3`
LATUS_LIB=lib${LATUS_LIBRARY_NAME}-${LATUS_API_VERSION}.so

if [ ! -x ${TST_PROG} ];
then
	echo "The sample program does not seem to have been compiled. Try 'make check' first."
	exit -1
fi

if [ "$1" = "-h" -o "$1" = "-H" -o "$1" = "--h" -o "$1" = "--help" ];
then
	echo "Usage: $0"
	echo "  Tests on the Boost Date-Time Library."
	exit 0
fi

${TST_PROG} $1
