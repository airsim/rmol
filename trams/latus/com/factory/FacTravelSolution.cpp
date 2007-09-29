// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/TravelSolutionKey.hpp>
#include <latus/com/bom/TravelSolution.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacTravelSolution.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacTravelSolution* FacTravelSolution::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacTravelSolution::~FacTravelSolution () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacTravelSolution& FacTravelSolution::instance () {

      if (_instance == NULL) {
        _instance = new FacTravelSolution();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    TravelSolution& FacTravelSolution::create (const TravelSolutionKey_T& iKey) {
      TravelSolution* aTravelSolution_ptr = NULL;

      aTravelSolution_ptr = new TravelSolution (iKey);
      assert (aTravelSolution_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aTravelSolution_ptr);

      return *aTravelSolution_ptr;
    }
    
  }
}
