#ifndef __LATUS_COM_BOM_SEGMENTCABINKEY_HPP
#define __LATUS_COM_BOM_SEGMENTCABINKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/SegmentDateKey.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of a segment-cabin. */
    struct SegmentCabinKey_T {
      SegmentDateKey_T segmentDateKey;
      CabinCode_T cabinCode;

      /** Constructor. */
      SegmentCabinKey_T (const SegmentDateKey_T& iSegmentDateKey,
                         const CabinCode_T& iCabinCode);
      
      /** Display of the key. */
      const std::string describe() const;
    };
    
  }
}
#endif // __LATUS_COM_BOM_SEGMENTCABINKEY_HPP
