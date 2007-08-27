#ifndef __LATUS_COM_BOM_CLASSKEY_HPP
#define __LATUS_COM_BOM_CLASSKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/KeyAbstract.hpp>
#include <latus/com/bom/SegmentCabinKey.hpp>

namespace LATUS {

  namespace COM {

    /** Define the key elements of a segment-cabin. */
    struct ClassKey_T : public KeyAbstract {
      SegmentCabinKey_T segmentCabinKey;
      ClassCode_T classCode;

      /** Constructor. */
      ClassKey_T (const SegmentCabinKey_T& iSegmentCabinKey,
                  const ClassCode_T& iClassCode);
      
      /** Display of the key. */
      const std::string describe() const;

      /** Display of the short key. */
      const std::string describeShort() const;
    };
    
  }
}
#endif // __LATUS_COM_BOM_CLASSKEY_HPP
