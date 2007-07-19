// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/Inventory.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    const std::string Inventory::describeKey() const {
      std::ostringstream ostr;
      ostr << "\"" << _description << "\"";
      return ostr.str();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void Inventory::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << _description << "; ";

      /*
      int j = 1;
      for (FlightDateDateList_T::const_iterator itFlightDateDate =
             _cityPairDateList.begin();
           itFlightDateDate != _cityPairDateList.end();
           itFlightDateDate++, j++) {
        const FlightDateDate* lFlightDateDate_ptr = itFlightDateDate->second;
        assert (lFlightDateDate_ptr != NULL);

        bool lIndented = (j != 1);
        lFlightDateDate_ptr->display (lIndented);
      }
      */
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

  }
}
