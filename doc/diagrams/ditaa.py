#!/usr/bin/env python
# -*- coding: utf-8 -*-

__author__ = "Mathieu Lecarme <mathieu@garambrogne.net>"
__version__ = '0.1'

import urllib

class Ditaa:
  antialias = True;
  shadows = True;
  scale = 1;
  round_corners = False;
  separations = True;
  def __init__(self, url):
    self.url = url
  def buildImage(self, ditaa):
    return urllib.urlopen(self.url, urllib.urlencode({
    'ditaa': ditaa,
    'no-antialias': not self.antialias,
    'no-shadows': not self.shadows,
    'scale': self.scale,
    'round-corners': self.round_corners,
    'no-separations': not self.separations
    }))
  def saveImage(self, ditaa, path):
    f = open(path, 'w')
    f.write(self.buildImage(ditaa).read())
    f.close()

#------------------------------------------------------------------------------	
def usage():
    print
    print
    print "-h, --help                        : outputs help and quits"
    print "-o <path>                         : path to output file (if blank, stdout)"
    print "<path>                            : input file (if blank, stdin)"
    print
	
#------------------------------------------------------------------------------	
def handle_opt():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "h:o:", ["help", "output"])
    except getopt.GetoptError, err:
        print str(err) # will print something like "option -a not recognized"
        usage()
        sys.exit(2)
	
    # Default options
    input_filename = ''
    output_filename = ''
    input_file = sys.stdin #'/dev/stdin'
    output_file = sys.stdout #'/dev/stdout'

    # Input stream/file
    if len (args) != 0:
        input_filename = args[0]

    # Handling
    for o, a in opts:
        if o in ("-h", "--help"):
            usage()
            sys.exit()
        elif o == "-o":
            output_filename = a
        else:
            assert False, "Unhandled option"

    # Input Ditaa (http://ditaa.sourceforge.net) formatted file.
    if (input_filename != ''):
      input_file = open (input_filename, 'r')

    if (output_filename != ''):
        output_file = open (output_filename, 'wb')


    print "Input stream/file: '" + input_filename + "'"
    print "Output stream/file: '" + output_filename + "'"
    return input_file, output_file

#------------------------------------------------------------------------------	
def main():

    # Parse command options
    input_file, output_file = handle_opt()

    # Size of the chunks to read
    chunkSize = 100000

    # Iterate while there is something to read from the file
    chunkIdx = 0
    flightIdx = 0
    currentBuffer = ''
    chunk = 'init'
    #while (chunk != '' and chunkIdx == 0):
    while (chunk != ''):
        chunkIdx += 1

        # DEBUG
        # print 'CurrentBuffer[' + str(chunkIdx) + ']:'

        chunk = input_file.read (chunkSize)

        # Check that the end of the file has not been reached
        #if (chunk == ''): print "No more characters to read for chunk #" + str (chunkIdx)

        # Add the newly read chunk to the current buffer
        currentBuffer += chunk

        # Iterate while there are full IFLIRR messages within the read chunk
        flightDateEDI = 'init'
        while (flightDateEDI != '' and currentBuffer != ''):
            flightIdx += 1
            # Extract a flight-date from the current buffer, and cut 
            # the corresponding part from that latter
            flightDateEDI, currentBuffer = getFlightDate (currentBuffer)

            # Note: if we just print flightDateEDI at this stage, we get
            # a human readable Edifact-based BIF (equivalent to edi2ascii tools)
            # print flightDateEDI

            flightDateCSV = convert_data_into_csv_format (flightDateEDI)

            # DEBUG
            # print "FlightDate[" + str(flightIdx) + "]:\n"

            # Main output
            if (flightDateCSV != ''):
                output_file.write (flightDateCSV + '\n')
            # output_file.write (flightDateEDI)


#-------------------------------------------------------------------------------
if __name__ == "__main__":
  main()

  ditaa = Ditaa('http://admin.garambrogne.net/ditaa_web/ditaa')
  ditaa.round_corners = True
  ditaa.scale = 1.5
  ditaa.saveImage('''
  +--------------+
  | Python rulez |
  +--------------+''', '/tmp/python_ditaa.png')
  
