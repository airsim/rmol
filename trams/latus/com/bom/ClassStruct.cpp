// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/basic/BasConst_ClassStruct.hpp>
#include <latus/com/bom/ClassStruct.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    ClassStruct_T::ClassStruct_T (const ClassKey_T& iClassKey)
      : _segmentCabin (NULL), _key (iClassKey),
        _bookingNumber (DEFAULT_CLASS_BOOKING_NUMBER),
        _availability (DEFAULT_CLASS_AVAILABILITY),
        _bookingLimitBool (DEFAULT_CLASS_BOOKING_LIMIT_BOOL),
        _bookingLimit (DEFAULT_CLASS_BOOKING_LIMIT),
        _overbookingRate (1 + DEFAULT_CLASS_OVERBOOKING_RATE) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string ClassStruct_T::describe() const {
      std::ostringstream ostr;
      ostr << describeKey() << " - Bkgs: " << _bookingNumber << ", Avl: "
           << _availability; 
      if (_bookingLimitBool) {
        ostr << ", BLimitVal: " << _bookingLimit;
      }
      if (_overbookingRate != 1) {
        ostr << ", ObR: " << _overbookingRate;
      }
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string ClassStruct_T::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string ClassStruct_T::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void ClassStruct_T::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describe() << std::endl;

      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
  }
}
