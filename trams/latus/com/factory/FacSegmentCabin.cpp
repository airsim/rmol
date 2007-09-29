// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/SegmentCabinKey.hpp>
#include <latus/com/bom/SegmentCabin.hpp>
#include <latus/com/bom/ClassStruct.hpp>
#include <latus/com/bom/LegCabin.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacSegmentCabin.hpp>
#include <latus/com/factory/FacLegCabin.hpp>
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

    // //////////////////////////////////////////////////////////////////////
    void FacSegmentCabin::initLinkWithClass (SegmentCabin& ioSegmentCabin,
                                             const ClassStruct_T& iClass) {
      // Add the Class to the SegmentCabin internal vector (of
      // Class objects)
      ioSegmentCabin._classOrderedList.push_back (iClass);
      ClassStructOrderedList_T::reverse_iterator itClass =
        ioSegmentCabin._classOrderedList.rbegin();
      ClassStruct_T& lClass = *itClass;

      // Link the SegmentCabin to the Class, and vice versa
      lClass.setSegmentCabin (&ioSegmentCabin);
      
      // Add the Class to the SegmentCabin internal map (of Class
      // objects)
      const bool insertSucceeded = ioSegmentCabin._classList.
        insert (ClassStructList_T::value_type (lClass.describeShortKey(),
                                               lClass)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioSegmentCabin.describeKey()
                         << " and " << lClass.describeShortKey());
        assert (insertSucceeded == true);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void FacSegmentCabin::initLinkWithLegCabin (SegmentCabin& ioSegmentCabin,
                                                LegCabin& ioLegCabin) {
      // Link the SegmentCabin to the LegCabin
      ioSegmentCabin._legCabinList.push_back (&ioLegCabin);

      // Link the SegmentCabin to the LegCabin
      FacLegCabin::initLinkWithSegmentCabin (ioLegCabin, ioSegmentCabin);
    }

  }
}
