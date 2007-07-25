// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/SegmentCabinKey.hpp>
#include <latus/com/bom/SegmentCabin.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacSegmentCabin.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacSegmentCabin* FacSegmentCabin::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacSegmentCabin::~FacSegmentCabin () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacSegmentCabin& FacSegmentCabin::instance () {

      if (_instance == NULL) {
        _instance = new FacSegmentCabin();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    SegmentCabin& FacSegmentCabin::create (const SegmentCabinKey_T& iKey) {
      SegmentCabin* aSegmentCabin_ptr = NULL;

      aSegmentCabin_ptr = new SegmentCabin (iKey);
      assert (aSegmentCabin_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aSegmentCabin_ptr);

      return *aSegmentCabin_ptr;
    }

  }
}
