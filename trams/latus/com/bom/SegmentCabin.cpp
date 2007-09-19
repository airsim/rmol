// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/SegmentCabin.hpp>
#include <latus/com/bom/LegCabin.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    SegmentCabin::SegmentCabin (const SegmentCabinKey_T& iKey)
      : _key (iKey), _segmentDate (NULL), _reservedSeats (0),
        _bookingCounter (0), _commitedSpace (0.0), _availabilityPool (0.0) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    SegmentCabin::~SegmentCabin () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string SegmentCabin::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string SegmentCabin::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void SegmentCabin::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey()
                << " ; ";

      for (LegCabinOrderedList_T::const_iterator itLegCabin =
             _legCabinList.begin();
           itLegCabin != _legCabinList.end(); ++itLegCabin) {
        const LegCabin* lLegCabin_ptr = *itLegCabin;
        assert (lLegCabin_ptr != NULL);

        std::cout << lLegCabin_ptr->getBoardPoint()
                  << "/" << getCabinCode() << "-";
      }
      std::cout << std::endl;

      for (ClassStructOrderedList_T::const_iterator itClass =
             _classOrderedList.begin();
           itClass != _classOrderedList.end(); ++itClass) {
        const ClassStruct_T& lClass = *itClass;
        lClass.display();
      }

      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

    // //////////////////////////////////////////////////////////////////////
    void SegmentCabin::updateBookingAndSeatCounters() {
      BookingNumber_T lBookingCounter = 0;
       for (ClassStructOrderedList_T::const_iterator itClass =
             _classOrderedList.begin();
           itClass != _classOrderedList.end(); ++itClass) {
        const ClassStruct_T& lClass = *itClass;
        lBookingCounter += lClass.getBookingNumber();
        }
      setBookingCounter (lBookingCounter);
    }

    // //////////////////////////////////////////////////////////////////////
    void SegmentCabin::updateCommitedSpaces() {
      CommitedSpace_T lCommitedSpace = getReservedSeats();
      for (ClassStructOrderedList_T::const_iterator itClass =
             _classOrderedList.begin();
           itClass != _classOrderedList.end(); ++itClass) {
        const ClassStruct_T& lClass = *itClass;
        lCommitedSpace += (lClass.getBookingNumber()*(1+lClass.getOverbookingRate()));
      }
      setCommitedSpace (lCommitedSpace);
    }

    // //////////////////////////////////////////////////////////////////////
    void SegmentCabin::updateAvailabilityPools() {
      //ToDo: Set the default availabilityPool value in the BasConst.cpp file
      Availability_T lAvailabilityPool = 300000.0;
      for (LegCabinOrderedList_T::const_iterator itLegCabin =
             _legCabinList.begin();
           itLegCabin != _legCabinList.end(); ++itLegCabin) {
        const LegCabin* lLegCabin_ptr = *itLegCabin;
        assert (lLegCabin_ptr != NULL);
        if (lLegCabin_ptr->getAvailabilityPool() < lAvailabilityPool) {
          lAvailabilityPool = lLegCabin_ptr->getAvailabilityPool();
        }
      }
      setAvailabilityPool (lAvailabilityPool);
    }

     // //////////////////////////////////////////////////////////////////////
    void SegmentCabin::updateAllAvailabilities() {
      Availability_T lAvailibilityPool = getAvailabilityPool();
       for (ClassStructOrderedList_T::const_iterator itClass =
             _classOrderedList.begin();
           itClass != _classOrderedList.end(); ++itClass) {
        const ClassStruct_T& lClass = *itClass;
        //lClass.setAvailabilities(lAvailabilityPool);
      }
    }
  }
}
