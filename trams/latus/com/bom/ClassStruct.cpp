// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <stdexcept>
// LATUS COM
#include <latus/com/basic/BasConst_ClassStruct.hpp>
#include <latus/com/bom/ClassStruct.hpp>
#include <latus/com/service/Logger.hpp>

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
    ClassStruct_T::ClassStruct_T (const ClassStruct_T& iClassStruct)
      : _segmentCabin (iClassStruct.getSegmentCabin()), _key (iClassStruct.getClassKey()),
        _bookingNumber (iClassStruct.getBookingNumber()),
        _availability (iClassStruct.getAvailability()),
        _bookingLimitBool (iClassStruct.getBookingLimitBool()),
        _bookingLimit (iClassStruct.getBookingLimit()),
        _overbookingRate (iClassStruct.getOverbookingRate()) {
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

    // //////////////////////////////////////////////////////////////////////
    void ClassStruct_T::exportInformations(std::ofstream& ioOutputFile) const {
      try {
        ioOutputFile << describeKey() << " - Bkgs: " << _bookingNumber << ", Avl: "
           << _availability; 
        if (_bookingLimitBool) {
          ioOutputFile << ", BLimitVal: " << _bookingLimit;
        }
        if (_overbookingRate != 1) {
          ioOutputFile << ", ObR: " << _overbookingRate;
        }
        ioOutputFile << std::endl;
      }
      catch (const std::exception& ce){
        std::cout << "Error (ClassStruct) in exporting the output file: " << ce.what() << std::endl;
      }

    }

    // //////////////////////////////////////////////////////////////////////
    bool ClassStruct_T::updateInventory (const BookingNumber_T& oBookingNumber) {
      assert(oBookingNumber <= _availability + DEFAULT_EPSILON_VALUE);
      if (oBookingNumber <= _availability + DEFAULT_EPSILON_VALUE) {
        _bookingNumber = _bookingNumber + oBookingNumber;
        //DEBUG
        /* LATUS_LOG_DEBUG (" " << describeKey() << " - Bkgs: " << _bookingNumber << ", Avl: "
           << _availability);*/
        return true;
      }
      else {
        return false;
      }
    }
    
  }
}
