// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/TravelSolution.hpp>
#include <latus/com/bom/OutboundPath.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    TravelSolution::TravelSolution (const TravelSolutionKey_T& iKey)
      : _key (iKey), _outboundPath_ptr (NULL), _fare (0.0), _tSAvailability (0.0) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    TravelSolution::~TravelSolution () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string TravelSolution::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string TravelSolution::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void TravelSolution::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << std::endl;

      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

     // //////////////////////////////////////////////////////////////////////
    bool TravelSolution::buildCheapestSolution (const SeatNumber_T& lSeatNumber) {     
      
      bool availability = getOutboundPath()->buildCheapestSolution(_classStructList, lSeatNumber );
      return availability;
    }

     // //////////////////////////////////////////////////////////////////////
    void TravelSolution::calculateAvailabilities () {     
    }

    // //////////////////////////////////////////////////////////////////////
    void TravelSolution::fareQuote () {     
    }
    
  }
}
