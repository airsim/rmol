// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_TravelSolution.hpp>
#include <stdair/bom/OutboundPathContent.hpp>

namespace stdair {

  // ////////////////////////////////////////////////////////////////////
  OutboundPathContent::OutboundPathContent (const OutboundPathKey_T& iKey)
    :  _key (iKey), _airlineCode (DEFAULT_AIRLINE_CODE),
      _flightPathCode (DEFAULT_FLIGHTPATH_CODE),
      _flightTime (NULL_BOOST_TIME_DURATION) {
  }
  
  // ////////////////////////////////////////////////////////////////////
  OutboundPathContent::~OutboundPathContent () {
  }

}

