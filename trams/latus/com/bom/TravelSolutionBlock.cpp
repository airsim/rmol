// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/basic/BasConst_CityPair.hpp>
#include <latus/com/bom/TravelSolution.hpp>
#include <latus/com/bom/AirportDate.hpp>
#include <latus/com/bom/TravelSolutionBlock.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    TravelSolutionBlock::TravelSolutionBlock (const TravelSolutionBlockKey_T& iKey)
      : _airportDate (NULL), _key (iKey), _travelSolutionNumber (0) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    TravelSolutionBlock::~TravelSolutionBlock () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string TravelSolutionBlock::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string TravelSolutionBlock::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void TravelSolutionBlock::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << std::endl;
      std::cout << "Nb TravelSolutions: " << _travelSolutionNumber << std::endl;

      for (TravelSolutionList_T::const_iterator itTravelSolution =
             _travelSolutionList.begin();
           itTravelSolution != _travelSolutionList.end(); ++itTravelSolution) {
        const TravelSolution* lTravelSolution_ptr = itTravelSolution->second;
        assert (lTravelSolution_ptr != NULL);

        std::cout << lTravelSolution_ptr->describeKey() << std::endl;
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

    // //////////////////////////////////////////////////////////////////////
    void TravelSolutionBlock::getBestTravelSolution (TravelSolution* lbTS, const SeatNumber_T& lPartSize) const {
      bool lProductSell = false;
      TravelSolutionList_T:: const_iterator itTravelSolution
        = _travelSolutionList.begin();

      while ((lProductSell != true) && (itTravelSolution != _travelSolutionList.end())) {
        lbTS = itTravelSolution->second;
        assert (lbTS != NULL);
        Availability_T travelSolAvailability = lbTS->getTSAvailability();
        if (travelSolAvailability > (lPartSize - COM::DEFAULT_EPSILON_VALUE)) {
          lProductSell = true;
        }
        itTravelSolution++;
      }
    }
    
  }
}
