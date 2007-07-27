// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/SegmentDateKey.hpp>
#include <latus/com/bom/SegmentDate.hpp>
#include <latus/com/bom/SegmentCabin.hpp>
#include <latus/com/bom/LegDate.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacSegmentDate.hpp>
#include <latus/com/factory/FacLegDate.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacSegmentDate* FacSegmentDate::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacSegmentDate::~FacSegmentDate () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacSegmentDate& FacSegmentDate::instance () {

      if (_instance == NULL) {
        _instance = new FacSegmentDate();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    SegmentDate& FacSegmentDate::create (const SegmentDateKey_T& iKey) {
      SegmentDate* aSegmentDate_ptr = NULL;

      aSegmentDate_ptr = new SegmentDate (iKey);
      assert (aSegmentDate_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aSegmentDate_ptr);

      return *aSegmentDate_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    void FacSegmentDate::initLinkWithSegmentCabin (SegmentDate& ioSegmentDate,
                                             SegmentCabin& ioSegmentCabin) {
      // Link the SegmentDate to the SegmentCabin, and vice versa
      ioSegmentCabin.setSegmentDate (&ioSegmentDate);
      
      // Link the SegmentDate to the SegmentCabin
      const bool insertSucceeded = ioSegmentDate._segmentCabinList.
        insert (SegmentCabinList_T::value_type (ioSegmentCabin.describeShortKey(),
                                           &ioSegmentCabin)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioSegmentDate.describeKey()
                         << " and " << ioSegmentCabin.describeShortKey());
        assert (insertSucceeded == true);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void FacSegmentDate::initLinkWithLegDate (SegmentDate& ioSegmentDate,
                                              LegDate& ioLegDate) {
      // Link the SegmentDate to the LegDate
      const bool insertSucceeded = ioSegmentDate._legDateList.
        insert (LegDateList_T::value_type (ioLegDate.describeKey(),
                                           &ioLegDate)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioSegmentDate.describeKey()
                         << " and " << ioLegDate.describeShortKey());
        assert (insertSucceeded == true);
      }
    }

  }
}
