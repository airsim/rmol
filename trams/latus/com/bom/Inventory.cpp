// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/FlightDate.hpp>
#include <latus/com/bom/Inventory.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    Inventory::Inventory (const InventoryKey_T& iKey)
      : _key (iKey), _worldSchedule (NULL) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    Inventory::~Inventory () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string Inventory::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string Inventory::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void Inventory::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << std::endl;

      for (FlightDateList_T::const_iterator itFlightDate =
             _flightDateList.begin();
           itFlightDate != _flightDateList.end(); ++itFlightDate) {
        const FlightDate* lFlightDate_ptr = itFlightDate->second;
        assert (lFlightDate_ptr != NULL);

        lFlightDate_ptr->display ();
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

     // //////////////////////////////////////////////////////////////////////
     void Inventory::updateBookingsAndSeatCounters() const {
      
        for (FlightDateList_T::const_iterator itFlightDate =
             _flightDateList.begin();
           itFlightDate != _flightDateList.end(); ++itFlightDate) {
        const FlightDate* lFlightDate_ptr = itFlightDate->second;
        assert (lFlightDate_ptr != NULL);

        lFlightDate_ptr->updateBookingsAndSeatCounters ();
        }

     }

     // //////////////////////////////////////////////////////////////////////
     void Inventory::updateCommitedSpaces() const {
      
        for (FlightDateList_T::const_iterator itFlightDate =
             _flightDateList.begin();
           itFlightDate != _flightDateList.end(); ++itFlightDate) {
        const FlightDate* lFlightDate_ptr = itFlightDate->second;
        assert (lFlightDate_ptr != NULL);

        lFlightDate_ptr->updateCommitedSpaces ();
        }

     }

    // //////////////////////////////////////////////////////////////////////
     void Inventory::updateAvailabilityPools() const {
      
        for (FlightDateList_T::const_iterator itFlightDate =
             _flightDateList.begin();
           itFlightDate != _flightDateList.end(); ++itFlightDate) {
        const FlightDate* lFlightDate_ptr = itFlightDate->second;
        assert (lFlightDate_ptr != NULL);

        lFlightDate_ptr->updateAvailabilityPools ();
        }

     }

    // //////////////////////////////////////////////////////////////////////
     void Inventory::updateAllAvailabilities() const {
      
        for (FlightDateList_T::const_iterator itFlightDate =
             _flightDateList.begin();
           itFlightDate != _flightDateList.end(); ++itFlightDate) {
        const FlightDate* lFlightDate_ptr = itFlightDate->second;
        assert (lFlightDate_ptr != NULL);

        lFlightDate_ptr->updateAllAvailabilities ();
        }

     }

    // //////////////////////////////////////////////////////////////////////
    FlightDate* Inventory::
    getFlightDateInternal (const std::string& iFlightDateKey) const {
      FlightDate* resultFlightDate_ptr = NULL;
      
      FlightDateList_T::const_iterator itFlightDate =
        _flightDateList.find (iFlightDateKey);

      if (itFlightDate != _flightDateList.end()) {
        resultFlightDate_ptr = itFlightDate->second;
      }

      return resultFlightDate_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    FlightDate* Inventory::
    getFlightDate (const FlightNumber_T& iFlightNumber,
                   const DateTime_T& iFlightDate) const {
      const InventoryKey_T& lInventoryKey = getPrimaryKey();
      const FlightKey_T lFlightKey (lInventoryKey, iFlightNumber);
      const FlightDateKey_T lFlightDateKey (lFlightKey, iFlightDate);
      const std::string& lFlightDateKeyString = lFlightDateKey.describeShort();
      return getFlightDateInternal (lFlightDateKeyString);
    }
    
  }
}
