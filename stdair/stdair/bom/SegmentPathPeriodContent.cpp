// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_TravelSolution.hpp>
#include <stdair/bom/SegmentPathPeriodContent.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriodContent::SegmentPathPeriodContent (const Key_T& iKey)
    :  _key (iKey), _airlineCode (DEFAULT_AIRLINE_CODE),
      _flightPathCode (DEFAULT_FLIGHTPATH_CODE) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  SegmentPathPeriodContent::~SegmentPathPeriodContent () {
  }

}

