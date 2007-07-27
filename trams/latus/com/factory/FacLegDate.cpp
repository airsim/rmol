// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/LegDateKey.hpp>
#include <latus/com/bom/LegDate.hpp>
#include <latus/com/bom/LegCabin.hpp>
#include <latus/com/bom/SegmentDate.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacLegDate.hpp>
#include <latus/com/factory/FacSegmentDate.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacLegDate* FacLegDate::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacLegDate::~FacLegDate () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacLegDate& FacLegDate::instance () {

      if (_instance == NULL) {
        _instance = new FacLegDate();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    LegDate& FacLegDate::create (const LegDateKey_T& iKey) {
      LegDate* aLegDate_ptr = NULL;

      aLegDate_ptr = new LegDate (iKey);
      assert (aLegDate_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aLegDate_ptr);

      return *aLegDate_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    void FacLegDate::initLinkWithLegCabin (LegDate& ioLegDate,
                                             LegCabin& ioLegCabin) {
      // Link the LegDate to the LegCabin, and vice versa
      ioLegCabin.setLegDate (&ioLegDate);
      
      // Link the LegDate to the LegCabin
      const bool insertSucceeded = ioLegDate._legCabinList.
        insert (LegCabinList_T::value_type (ioLegCabin.describeShortKey(),
                                           &ioLegCabin)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioLegDate.describeKey()
                         << " and " << ioLegCabin.describeShortKey());
        assert (insertSucceeded == true);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void FacLegDate::initLinkWithSegmentDate (LegDate& ioLegDate,
                                              SegmentDate& ioSegmentDate) {
      // Link the LegDate to the SegmentDate
      const bool insertSucceeded = ioLegDate._segmentDateList.
        insert (SegmentDateList_T::value_type (ioSegmentDate.describeKey(),
                                               &ioSegmentDate)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioLegDate.describeKey()
                         << " and " << ioSegmentDate.describeShortKey());
        assert (insertSucceeded == true);
      }

      // Link the SegmentDate to the LegDate
      FacSegmentDate::initLinkWithLegDate (ioSegmentDate, ioLegDate);
    }

  }
}
