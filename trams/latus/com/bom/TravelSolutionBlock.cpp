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
    TravelSolutionBlock::TravelSolutionBlock (const TravelSolutionBlockKey_T& iKey, const WTP* iWTP_ptr)
      : _airportDate_ptr (NULL), _wTP_ptr (iWTP_ptr), _key (iKey), _travelSolutionNumber (0) {
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
   TravelSolution* TravelSolutionBlock::getBestTravelSolution (const SeatNumber_T& iPartSize) const {
      bool lProductSell = false;
      TravelSolutionList_T:: const_iterator itTravelSolution
        = _travelSolutionList.begin();
      TravelSolution* lTravelSolution = NULL;

      while (!lProductSell && itTravelSolution != _travelSolutionList.end()) {
        lTravelSolution = itTravelSolution->second;
        Availability_T travelSolAvailability = lTravelSolution->getTSAvailability();
        if (travelSolAvailability >= (iPartSize - COM::DEFAULT_EPSILON_VALUE)) {
          lProductSell = true;
        }
        itTravelSolution++;
      }
      return lTravelSolution;
    }
    
  }
}
