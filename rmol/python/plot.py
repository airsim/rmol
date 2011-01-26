#!/usr/bin/env python

import sys
import getopt
import matplotlib.pyplot as plt

def treat_input(aStr):
    aListOfStr = aStr.rstrip().split(',')
    aListOfFloat = [float(aStr) for aStr in aListOfStr]
    return aListOfFloat


def plot_simple(yVals):
    plt.plot(yVals,'b-o')
    plt.show()


def main():
    # parse command line options
    try:
        opts, args = getopt.getopt(sys.argv[1:], "h", ["help"])
    except getopt.error, msg:
        print msg
        print "for help use --help"
        sys.exit(2)
    # process options
    for o, a in opts:
        if o in ("-h", "--help"):
            print "to run the script: python plot.py 10,11,22"
            sys.exit(0)
    # process arguments
    for arg in args:
        yVals = treat_input(arg)
        plot_simple(yVals) 


if __name__ == "__main__":
    main()

