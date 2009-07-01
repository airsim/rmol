// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
// STDAIR 
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/PrintBomContent.hpp>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  PrintBomContent::PrintBomContent (std::ostringstream& ioStr,
                                    unsigned short& idx) :
    _str (&ioStr), _idx (&idx) {
  }

}

