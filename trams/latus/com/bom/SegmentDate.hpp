#ifndef __LATUS_COM_BOM_SEGMENTDATE_HPP
#define __LATUS_COM_BOM_SEGMENTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/BomAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Short description. */
    class SegmentDate : public BomAbstract {
    public:
      
    private:
      // Primary Key
      /** Board Point. */
      AirportCode_T boardPoint;

      /** Off Point. */
      AirportCode_T offPoint;
      
      /** Board Date. */
      DateTime_T boardDate;
      
      /** Cabin Code. */
      CabinCode_T cabin;
      
      // Attributes
      /** Off Date. */
      DateTime_T offDate;

      /** Elapsed Time. */
      Duration_T elapsedTime;

    };

  }
}
#endif // __LATUS_COM_BOM_SEGMENTDATE_HPP
