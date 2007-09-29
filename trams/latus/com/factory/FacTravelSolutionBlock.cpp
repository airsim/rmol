// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/TravelSolutionBlockKey.hpp>
#include <latus/com/bom/TravelSolutionBlock.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacTravelSolutionBlock.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacTravelSolutionBlock* FacTravelSolutionBlock::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacTravelSolutionBlock::~FacTravelSolutionBlock () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacTravelSolutionBlock& FacTravelSolutionBlock::instance () {

      if (_instance == NULL) {
        _instance = new FacTravelSolutionBlock();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    TravelSolutionBlock& FacTravelSolutionBlock::create (const TravelSolutionBlockKey_T& iKey) {
      TravelSolutionBlock* aTravelSolutionBlock_ptr = NULL;

      aTravelSolutionBlock_ptr = new TravelSolutionBlock (iKey);
      assert (aTravelSolutionBlock_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aTravelSolutionBlock_ptr);

      return *aTravelSolutionBlock_ptr;
    }
    
  }
}
