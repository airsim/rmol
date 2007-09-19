#ifndef __LATUS_COM_BAS_BASCONST_LATUS_SERVICE_HPP
#define __LATUS_COM_BAS_BASCONST_LATUS_SERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>

namespace LATUS {

  namespace COM {
    
    /** Default number of airlines for the LATUS_Service. */
    extern const unsigned int DEFAULT_LATUS_SERVICE_NUMBER_OF_AIRLINES;
    
    /** Default name for the first Inventory (INV) airline owner. */
    extern const std::string DEFAULT_LATUS_INV1_AIRLINE_CODE;

    /** Default name for the second Inventory (INV) airline owner. */
    extern const std::string DEFAULT_LATUS_INV2_AIRLINE_CODE;
    
    /** Maximum number of legs linked to a single flight-date.
        <br>Note that the number of derived segments is n*(n+1)/2 if n
        is the number of legs. */
    extern const unsigned short MAXIMUM_NUMBER_OF_LEGS_IN_FLIGHT;

    /** Maximum number of segments linked to a single O&D
        (Origin & Destination). */
    extern const unsigned short MAXIMUM_NUMBER_OF_SEGMENTS_IN_OND;
  }
}
#endif // __LATUS_COM_BAS_BASCONST_LATUS_SERVICE_HPP
