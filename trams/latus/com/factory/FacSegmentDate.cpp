// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/SegmentDateKey.hpp>
#include <latus/com/bom/SegmentDate.hpp>
#include <latus/com/bom/SegmentCabin.hpp>
#include <latus/com/bom/LegDate.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacSegmentDate.hpp>
#include <latus/com/factory/FacSegmentCabin.hpp>
#include <latus/com/factory/FacLegDate.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacSegmentDate* FacSegmentDate::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacSegmentDate::~FacSegmentDate () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacSegmentDate& FacSegmentDate::instance () {

      if (_instance == NULL) {
        _instance = new FacSegmentDate();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    SegmentDate& FacSegmentDate::create (const SegmentDateKey_T& iKey) {
      SegmentDate* aSegmentDate_ptr = NULL;

      aSegmentDate_ptr = new SegmentDate (iKey);
      assert (aSegmentDate_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aSegmentDate_ptr);

      return *aSegmentDate_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    void FacSegmentDate::initLinkWithSegmentCabin (SegmentDate& ioSegmentDate,
                                             SegmentCabin& ioSegmentCabin) {
      // Link the SegmentDate to the SegmentCabin, and vice versa
      ioSegmentCabin.setSegmentDate (&ioSegmentDate);
      
      // Add the SegmentCabin to the SegmentDate internal map (of SegmentCabin
      // objects)
      const bool insertSucceeded = ioSegmentDate._segmentCabinList.
        insert (SegmentCabinList_T::value_type (ioSegmentCabin.describeShortKey(),
                                           &ioSegmentCabin)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioSegmentDate.describeKey()
                         << " and " << ioSegmentCabin.describeShortKey());
        assert (insertSucceeded == true);
      }

      // Add the SegmentCabin to the SegmentDate internal vector (of
      // SegmentCabin objects)
      ioSegmentDate._segmentCabinOrderedList.push_back (&ioSegmentCabin);
    }

    // //////////////////////////////////////////////////////////////////////
    void FacSegmentDate::initLinkWithLegDate (SegmentDate& ioSegmentDate,
                                              LegDate& ioLegDate) {
      // Link the SegmentDate to the routing LegDate
      ioSegmentDate._legDateList.push_back (&ioLegDate);

      // Link the crossing SegmentDate to the LegDate.
      FacLegDate::initLinkWithSegmentDate (ioLegDate, ioSegmentDate);
    }

    // //////////////////////////////////////////////////////////////////////
    void FacSegmentDate::createRouting (SegmentDate& ioSegmentDate) {
      // Set the attributes derived from the routing legs (e.g., board and
      // off dates)
      ioSegmentDate.fillFromRouting();

      // Iterate on the Segment-Cabins
      const SegmentCabinList_T& lCabinList = ioSegmentDate._segmentCabinList;
      for (SegmentCabinList_T::const_iterator itCabin = lCabinList.begin();
           itCabin != lCabinList.end(); ++itCabin) {
        SegmentCabin* lSegmentCabin_ptr = itCabin->second;
        assert (lSegmentCabin_ptr != NULL);

        // Iterate on the routing legs
        const LegDateOrderedList_T& lLegDateList =
          ioSegmentDate.getLegDateList();
        for (LegDateOrderedList_T::const_iterator itLegDate =
               lLegDateList.begin();
             itLegDate != lLegDateList.end(); ++itLegDate) {
          const LegDate* lLegDate_ptr = *itLegDate;
          assert (lLegDate_ptr != NULL);

          // Retrieve the LegCabin getting the same class of service
          // (cabin code) as the SegmentCabin.
          const CabinCode_T& lCabinCode = lSegmentCabin_ptr->getCabinCode();
          LegCabin* lLegCabin_ptr = lLegDate_ptr->getLegCabin (lCabinCode);

          // In fact, the following assertion corresponds to the assumption
          // that the cabins are the same on the segments AND on their routing
          // legs. For some actual airline, that is not always true. If needed,
          // we may implement the cabin mapping feature.
          if (lLegCabin_ptr == NULL) {
            LATUS_LOG_ERROR ("The cabin of the Segment: "
                             << lSegmentCabin_ptr->describeKey()
                             << " can not be found on the routing Legs."
                             << " The mapping of Segment-Cabins onto "
                             << "distinct Leg-Cabins is a feature not "
                             << "supported by LATUS.");
          }
          assert (lLegCabin_ptr != NULL);
          
          // Link the SegmentCabin and LegCabin together
          FacSegmentCabin::initLinkWithLegCabin (*lSegmentCabin_ptr,
                                                 *lLegCabin_ptr);
        }
      }

    }
    
  }
}
