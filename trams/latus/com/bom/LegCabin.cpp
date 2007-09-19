// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/LegDate.hpp>
#include <latus/com/bom/LegCabin.hpp>
#include <latus/com/bom/SegmentCabin.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    LegCabin::LegCabin (const LegCabinKey_T& iKey)
      : _key (iKey), _legDate (NULL),_soldSeat (0),
        _commitedSpace (0.0), _availabilityPool (0.0), _availability(0.0) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LegCabin::~LegCabin () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string LegCabin::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string LegCabin::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void LegCabin::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << " Capa: " << _capacity 
                << ", SSeats: " << _soldSeat 
                << std::endl;

      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

    // //////////////////////////////////////////////////////////////////////
    //ToDo: Update the seatCounters from the buckets
    void LegCabin::updateBookingAndSeatCounters() {
    }

     // //////////////////////////////////////////////////////////////////////
    void LegCabin::updateCommitedSpaces() {
      CommitedSpace_T lCommitedSpace = 0.0;
      for (SegmentCabinList_T::const_iterator itSegmentCabin =
             _segmentCabinList.begin();
           itSegmentCabin != _segmentCabinList.end(); itSegmentCabin++) {
        const SegmentCabin* lSegmentCabin_ptr = itSegmentCabin->second;
        assert (lSegmentCabin_ptr != NULL);

        lCommitedSpace += (lSegmentCabin_ptr->getCommitedSpace());
      }
      setCommitedSpace (lCommitedSpace);
    }

    // //////////////////////////////////////////////////////////////////////
    void LegCabin::updateAvailabilityPools() {
      Availability_T lAvailabilityPool = (getCapacity()-getCommitedSpace());
      setAvailabilityPool (lAvailabilityPool);
    }

     // //////////////////////////////////////////////////////////////////////
    void LegCabin::updateAllAvailabilities() {
      setAvailability (getAvailabilityPool());      
    }
    
    // //////////////////////////////////////////////////////////////////////
    SegmentCabin* LegCabin::
    getSegmentCabin (const std::string& iSegmentCabinKey) const {
      SegmentCabin* resultSegmentCabin_ptr = NULL;
      
      SegmentCabinList_T::const_iterator itSegmentCabin =
        _segmentCabinList.find (iSegmentCabinKey);

      if (itSegmentCabin != _segmentCabinList.end()) {
        resultSegmentCabin_ptr = itSegmentCabin->second;
      }

      return resultSegmentCabin_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    const AirportCode_T& LegCabin::getBoardPoint () const {
      assert (_legDate != NULL);
      return _legDate->getBoardPoint();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const AirportCode_T& LegCabin::getOffPoint () const {
      assert (_legDate != NULL);
      return _legDate->getOffPoint();
    }
    
  }
}
