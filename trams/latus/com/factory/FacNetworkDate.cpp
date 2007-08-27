// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/NetworkDate.hpp>
#include <latus/com/bom/AirportDate.hpp>
#include <latus/com/bom/AirportDateList.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacNetworkDate.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacNetworkDate* FacNetworkDate::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacNetworkDate::~FacNetworkDate () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacNetworkDate& FacNetworkDate::instance () {

      if (_instance == NULL) {
        _instance = new FacNetworkDate();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    NetworkDate& FacNetworkDate::create (const NetworkDateKey_T& iKey) {
      NetworkDate* aNetworkDate_ptr = NULL;

      aNetworkDate_ptr = new NetworkDate (iKey);
      assert (aNetworkDate_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aNetworkDate_ptr);

      return *aNetworkDate_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    void FacNetworkDate::initLinkWithAirportDate (NetworkDate& ioNetworkDate,
                                             AirportDate& ioAirportDate) {
      // Link the NetworkDate to the AirportDate, and vice versa
      ioAirportDate.setNetworkDate (&ioNetworkDate);
      
      // Add the AirportDate to the NetworkDate internal map (of
      // AirportDate objects)
      const bool insertSucceeded = ioNetworkDate._airportDateList.
        insert (AirportDateList_T::value_type (ioAirportDate.describeShortKey(),
                                           &ioAirportDate)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioNetworkDate.describeKey()
                         << " and " << ioAirportDate.describeShortKey());
        assert (insertSucceeded == true);
      }

      // Add the AirportDate to the NetworkDate internal vector (of
      // AirportDate objects)
      ioNetworkDate._airportDateOrderedList.push_back (&ioAirportDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void FacNetworkDate::createPathList (NetworkDate& ioNetworkDate) {
    }

  }
}
