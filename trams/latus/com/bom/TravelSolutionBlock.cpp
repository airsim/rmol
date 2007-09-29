#include <latus/com/bom/AirportDate.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    TravelSolutionBlock::TravelSolutionBlock (const TravelSolutionBlockKey_T& iKey)
      : _key (iKey), _airportDate (NULL), _travelSolutionNumber (0) {
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
    
  }
}
