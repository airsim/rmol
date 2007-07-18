#!/bin/sh

INSTALL_DIR=`grep "^prefix =" ../Makefile | cut -d"=" -d" " -f3`
TST_PROG=./single_date_simulator
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
	echo "Usage: $0 [<Number of random draws> <Mean value> <Std dev>]"
	echo "That simulation generates the demand (reservations made on a full year) for a single flight-date."
	echo "The demand is generated for every booking date (during one year) according to Poisson laws."
	echo "The aggregated demand is compared to a reference Gaussian distribution."
	echo "By default:"
	echo "  * Simulation length (number of runs). Default to 10 runs."
	echo "  * Mean value of the final demand (number of passengers ready to go. Default to 300.0."
	echo "  * Standard Deviation of the final demand. Default to 20.0."
	echo
	echo "The library (${LATUS_LIB}) is installed in: ${INSTALL_DIR}/lib"
	exit 0
fi

${TST_PROG} $1 $2 $3
