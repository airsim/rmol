// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/FlightDateKey.hpp>
#include <latus/com/bom/FlightDate.hpp>
#include <latus/com/bom/LegDate.hpp>
#include <latus/com/bom/SegmentDate.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacFlightDate.hpp>
#include <latus/com/service/Logger.hpp>


namespace LATUS {

  namespace COM {

    FacFlightDate* FacFlightDate::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacFlightDate::~FacFlightDate () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacFlightDate& FacFlightDate::instance () {

      if (_instance == NULL) {
        _instance = new FacFlightDate();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    FlightDate& FacFlightDate::create (const FlightDateKey_T& iKey) {
      FlightDate* aFlightDate_ptr = NULL;

      aFlightDate_ptr = new FlightDate (iKey);
      assert (aFlightDate_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aFlightDate_ptr);

      return *aFlightDate_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    void FacFlightDate::initLinkWithLegDate (FlightDate& ioFlightDate,
                                             LegDate& ioLegDate) {
      // Link the FlightDate to the LegDate, and vice versa
      ioLegDate.setFlightDate (&ioFlightDate);
      
      // Link the FlightDate to the LegDate
      const bool insertSucceeded = ioFlightDate._legDateList.
        insert (LegDateList_T::value_type (ioLegDate.describeShortKey(),
                                           &ioLegDate)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioFlightDate.describeKey()
                         << " and " << ioLegDate.describeShortKey());
        assert (insertSucceeded == true);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void FacFlightDate::initLinkWithSegmentDate (FlightDate& ioFlightDate,
                                                 SegmentDate& ioSegmentDate) {
      // Link the FlightDate to the SegmentDate, and vice versa
      ioSegmentDate.setFlightDate (&ioFlightDate);
      
      // Link the FlightDate to the SegmentDate
      const bool insertSucceeded = ioFlightDate._segmentDateList.
        insert (SegmentDateList_T::value_type(ioSegmentDate.describeShortKey(),
                                              &ioSegmentDate)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioFlightDate.describeKey()
                         << " and " << ioSegmentDate.describeShortKey());
        assert (insertSucceeded == true);
      }
    }

  }
}
