// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <limits>
#include <stdexcept>
// LATUS COM
#include <latus/com/bom/SegmentCabin.hpp>
#include <latus/com/bom/LegCabin.hpp>
#include <latus/com/basic/BasConst_TravelSolution.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    SegmentCabin::SegmentCabin (const SegmentCabinKey_T& iKey)
      : _segmentDate (NULL), _key (iKey), _capacity (0.0), _blockSpace (0.0),
        _bookingCounter (0), _commitedSpace (0.0), _availabilityPool (0.0) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    SegmentCabin::~SegmentCabin () {
    }

     // //////////////////////////////////////////////////////////////////////
    ClassStruct_T& SegmentCabin::getClassStruct (const ClassKey_T& iClassKey) {
      ClassStructList_T::iterator itClass = _classList.find(iClassKey.describeShort());
      assert (itClass != _classList.end());
      return itClass->second;
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

      for (ClassStructList_T::const_iterator itClass =
             _classList.begin();
           itClass != _classList.end(); ++itClass) {
        const ClassStruct_T& lClass = itClass->second;
        lClass.display();
      }

      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

    // //////////////////////////////////////////////////////////////////////
    void SegmentCabin::exportInformations(std::ofstream& ioOutFile) const {
      try {
        ioOutFile << describeKey()
                << " ; ";

        for (LegCabinOrderedList_T::const_iterator itLegCabin =
             _legCabinList.begin();
           itLegCabin != _legCabinList.end(); ++itLegCabin) {
          const LegCabin* lLegCabin_ptr = *itLegCabin;
          assert (lLegCabin_ptr != NULL);

          ioOutFile << lLegCabin_ptr->getBoardPoint()
                  << "/" << getCabinCode() << "-";
        }
        ioOutFile << std::endl;
      }
      catch (const std::exception& sce){
        std::cout << "Error (SegmentCabin) in exporting the output file: " << sce.what() << std::endl;
      }
      for (ClassStructList_T::const_iterator itClass =
             _classList.begin();
           itClass != _classList.end(); ++itClass) {
        const ClassStruct_T& lClass = itClass->second;
        lClass.exportInformations(ioOutFile);
      }

    }

    // //////////////////////////////////////////////////////////////////////
    void SegmentCabin::updateBookingAndSeatCounters() {
      BookingNumber_T lBookingCounter = 0;
       for (ClassStructList_T::const_iterator itClass =
             _classList.begin();
           itClass != _classList.end(); ++itClass) {
        const ClassStruct_T& lClass = itClass->second;
        lBookingCounter += lClass.getBookingNumber();
      }
      setBookingCounter (lBookingCounter);
    }

    // //////////////////////////////////////////////////////////////////////
    void SegmentCabin::updateCommitedSpaces() {
      CommitedSpace_T lCommitedSpace = getBlockSpace();
      for (ClassStructList_T::const_iterator itClass =
             _classList.begin();
           itClass != _classList.end(); ++itClass) {
        const ClassStruct_T& lClass = itClass->second;
        lCommitedSpace += (lClass.getBookingNumber()*(lClass.getOverbookingRate()));
      }
      setCommitedSpace (lCommitedSpace);
    }

    // //////////////////////////////////////////////////////////////////////
    void SegmentCabin::updateAvailabilityPools() {
      Availability_T lAvailabilityPool = std::numeric_limits<int>::max();
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
      Availability_T lAvailabilityPool = getAvailabilityPool();
       for (ClassStructList_T::iterator itClass =
             _classList.begin();
           itClass != _classList.end(); ++itClass) {
        ClassStruct_T& lClass = itClass->second;
        if ((lClass.getBookingLimitBool()) && (lClass.getBookingLimit()< lAvailabilityPool)) {
          lClass.setAvailability(lClass.getBookingLimit());
        }
        else {
          lClass.setAvailability(lAvailabilityPool);
        }
      }
    }

    // //////////////////////////////////////////////////////////////////////
    bool SegmentCabin::buildCheapestAvailableSolution (ClassStructList_T& ioClassStructList,
                                  const SeatNumber_T& ioSeatNumber,
                                  const SegmentDateKey_T& ioSegmentDateKey) const {

      bool classAvailability = false;

      ClassStructList_T:: const_reverse_iterator itClassStruct =
        _classList.rbegin();

      while (!classAvailability && itClassStruct != _classList.rend()) {
        const ClassStruct_T& lClassStruct = itClassStruct->second;
        Availability_T classStructAvailability = lClassStruct.getAvailability();
        if (classStructAvailability >= ioSeatNumber - DEFAULT_EPSILON_VALUE) {
          ClassStruct_T lClass (lClassStruct);
          ioClassStructList.insert (ClassStructList_T::value_type (ioSegmentDateKey.describe(), lClass));
          classAvailability = true;
        }
        itClassStruct++;
      }
      return classAvailability;
    }

     // //////////////////////////////////////////////////////////////////////
    bool SegmentCabin::updateInventory (const BookingNumber_T& ioBookingNumber,
                                  const ClassKey_T& ioClassKey) {
      bool sellProcedureControl = true;

      ClassStruct_T& invClassStruct = getClassStruct(ioClassKey);
      sellProcedureControl = invClassStruct.updateInventory(ioBookingNumber);
      if (sellProcedureControl) {
        for (LegCabinOrderedList_T::iterator itLegCabin =
             _legCabinList.begin();
             itLegCabin != _legCabinList.end(); ++itLegCabin) {
          LegCabin* lLegCabin_ptr = *itLegCabin;
          assert (lLegCabin_ptr != NULL);
          bool updateLegControl = lLegCabin_ptr->updateBookings(ioBookingNumber);
          if (!updateLegControl) {
            sellProcedureControl = false;
          }
        }
      }
      return sellProcedureControl;
      
    }
  }
}
