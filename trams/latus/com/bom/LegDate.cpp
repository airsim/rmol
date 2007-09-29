// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/LegDate.hpp>
#include <latus/com/bom/LegCabin.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    LegDate::LegDate (const LegDateKey_T& iKey)
      : _flightDate (NULL), _key (iKey) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    LegDate::~LegDate () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string LegDate::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string LegDate::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void LegDate::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey()
                << " - " << _offPoint
                << ", " << _boardDate << " --> " << _offDate
                << ", " << _boardTime << " --> " << _offTime
                << "/ " << _elapsedTime << std::endl;

      for (LegCabinOrderedList_T::const_iterator itLegCabin =
             _legCabinOrderedList.begin();
           itLegCabin != _legCabinOrderedList.end(); itLegCabin++) {
        const LegCabin* lLegCabin_ptr = *itLegCabin;
        assert (lLegCabin_ptr != NULL);

        lLegCabin_ptr->display ();
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

    // //////////////////////////////////////////////////////////////////////
    void LegDate::updateBookingsAndSeatCounters() const {

      for (LegCabinOrderedList_T::const_iterator itLegCabin =
             _legCabinOrderedList.begin();
           itLegCabin != _legCabinOrderedList.end(); itLegCabin++) {
        LegCabin* lLegCabin_ptr = *itLegCabin;
        assert (lLegCabin_ptr != NULL);

        lLegCabin_ptr->updateBookingAndSeatCounters();
      }
            
    }

    // //////////////////////////////////////////////////////////////////////
    void LegDate::updateCommitedSpaces() const {

      for (LegCabinOrderedList_T::const_iterator itLegCabin =
             _legCabinOrderedList.begin();
           itLegCabin != _legCabinOrderedList.end(); itLegCabin++) {
        LegCabin* lLegCabin_ptr = *itLegCabin;
        assert (lLegCabin_ptr != NULL);

        lLegCabin_ptr->updateCommitedSpaces();
      }
            
    }

    // //////////////////////////////////////////////////////////////////////
    void LegDate::updateAvailabilityPools() const {

      for (LegCabinOrderedList_T::const_iterator itLegCabin =
             _legCabinOrderedList.begin();
           itLegCabin != _legCabinOrderedList.end(); itLegCabin++) {
        LegCabin* lLegCabin_ptr = *itLegCabin;
        assert (lLegCabin_ptr != NULL);

        lLegCabin_ptr->updateAvailabilityPools();
      }
            
    }

    // //////////////////////////////////////////////////////////////////////
    void LegDate::updateAllAvailabilities() const {

      for (LegCabinOrderedList_T::const_iterator itLegCabin =
             _legCabinOrderedList.begin();
           itLegCabin != _legCabinOrderedList.end(); itLegCabin++) {
        LegCabin* lLegCabin_ptr = *itLegCabin;
        assert (lLegCabin_ptr != NULL);

        lLegCabin_ptr->updateAllAvailabilities();
      }
            
    }
    
    // //////////////////////////////////////////////////////////////////////
    const Duration_T LegDate::getTimeOffSet() const {
      // TimeOffSet = (OffTime - BoardTime) + (OffDate - BoardDate) * 24
      //              - ElapsedTime
      Duration_T oTimeOffSet = (_offTime - _boardTime);
      const DateOffSet_T& lDateOffSet = getDateOffSet();
      const Duration_T lDateOffSetInHours (lDateOffSet.days() * 24, 0, 0);
      oTimeOffSet += lDateOffSetInHours - _elapsedTime;
      return oTimeOffSet;
    }

    // //////////////////////////////////////////////////////////////////////
    LegCabin* LegDate::
    getLegCabinInternal (const std::string& iLegCabinKey) const {
      LegCabin* resultLegCabin_ptr = NULL;
      
      LegCabinList_T::const_iterator itLegCabin =
        _legCabinList.find (iLegCabinKey);

      if (itLegCabin != _legCabinList.end()) {
        resultLegCabin_ptr = itLegCabin->second;
      }

      return resultLegCabin_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    LegCabin* LegDate::getLegCabin (const CabinCode_T& iCabinCode) const {
      const LegDateKey_T& lLegDateKey = getPrimaryKey();
      const LegCabinKey_T lLegCabinKey (lLegDateKey, iCabinCode);
      const std::string& lLegCabinKeyString = lLegCabinKey.describeShort();
      return getLegCabinInternal (lLegCabinKeyString);
    }
    
    // //////////////////////////////////////////////////////////////////////
    SegmentDate* LegDate::
    getSegmentDate (const std::string& iSegmentDateKey) const {
      SegmentDate* resultSegmentDate_ptr = NULL;
      
      SegmentDateList_T::const_iterator itSegmentDate =
        _segmentDateList.find (iSegmentDateKey);

      if (itSegmentDate != _segmentDateList.end()) {
        resultSegmentDate_ptr = itSegmentDate->second;
      }

      return resultSegmentDate_ptr;
    }

  }
}
