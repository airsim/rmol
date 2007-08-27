// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/LegCabinKey.hpp>
#include <latus/com/bom/LegCabin.hpp>
#include <latus/com/bom/SegmentCabin.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacLegCabin.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacLegCabin* FacLegCabin::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacLegCabin::~FacLegCabin () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacLegCabin& FacLegCabin::instance () {

      if (_instance == NULL) {
        _instance = new FacLegCabin();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    LegCabin& FacLegCabin::create (const LegCabinKey_T& iKey) {
      LegCabin* aLegCabin_ptr = NULL;

      aLegCabin_ptr = new LegCabin (iKey);
      assert (aLegCabin_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aLegCabin_ptr);

      return *aLegCabin_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    void FacLegCabin::initLinkWithSegmentCabin (LegCabin& ioLegCabin,
                                                SegmentCabin& ioSegmentCabin) {
      // Link the LegCabin to the SegmentCabin
      const bool insertSucceeded = ioLegCabin._segmentCabinList.
        insert (SegmentCabinList_T::value_type (ioSegmentCabin.describeKey(),
                                                &ioSegmentCabin)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioLegCabin.describeKey()
                         << " and " << ioSegmentCabin.describeShortKey());
        assert (insertSucceeded == true);
      }
    }

  }
}
