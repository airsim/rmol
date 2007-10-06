// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <limits>
// LATUS COM
#include <latus/com/bom/TravelSolution.hpp>
#include <latus/com/bom/OutboundPath.hpp>
#include <latus/com/bom/SegmentCabin.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    TravelSolution::TravelSolution (const TravelSolutionKey_T& iKey)
      : _key (iKey), _outboundPath_ptr (NULL), _fare (0.0), _tSAvailability (0.0) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    TravelSolution::~TravelSolution () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string TravelSolution::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string TravelSolution::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void TravelSolution::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << ", Availability :" << _tSAvailability << std::endl;
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

     // //////////////////////////////////////////////////////////////////////
    bool TravelSolution::buildCheapestAvailableSolution (const SeatNumber_T& lSeatNumber) {           
      return getOutboundPath()->buildCheapestAvailableSolution(_classStructList, lSeatNumber );
    }

     // //////////////////////////////////////////////////////////////////////
    void TravelSolution::calculateAvailabilities () {
      Availability_T lAvailability = std::numeric_limits<int>::max();
      for (ClassStructList_T::const_iterator itClassStruct =
             _classStructList.begin();
           itClassStruct != _classStructList.end(); ++itClassStruct) {
        const ClassStruct_T& lClassStruct = itClassStruct->second;
        if (lClassStruct.getAvailability() < lAvailability) {
          lAvailability = lClassStruct.getAvailability();
        }
      }
      setTSAvailability (lAvailability);
    }

     // //////////////////////////////////////////////////////////////////////
    bool TravelSolution::sell (const BookingNumber_T& iBookingNumber) const {
      bool sellProduct = true;
      for (ClassStructList_T::const_iterator itClassStruct =
             _classStructList.begin();
           itClassStruct != _classStructList.end(); ++itClassStruct) {
         const ClassStruct_T& lClassStruct = itClassStruct->second;
         SegmentCabin* lSegmentCabin_ptr = lClassStruct.getSegmentCabin();
         bool updateAvailable = lSegmentCabin_ptr->updateInventory(iBookingNumber, lClassStruct.getClassKey());
         if (!updateAvailable) {
           sellProduct = false;
         }
       }
      return sellProduct;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void TravelSolution::fareQuote () {     
    }
    
  }
}
