// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/basic/BasConst_LATUS_Service.hpp>
#include <latus/com/bom/AirportDateKey.hpp>
#include <latus/com/bom/AirportDate.hpp>
#include <latus/com/bom/OutboundPath.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacAirportDate.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacAirportDate* FacAirportDate::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacAirportDate::~FacAirportDate () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacAirportDate& FacAirportDate::instance () {

      if (_instance == NULL) {
        _instance = new FacAirportDate();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    AirportDate& FacAirportDate::create (const AirportDateKey_T& iKey) {
      AirportDate* aAirportDate_ptr = NULL;

      aAirportDate_ptr = new AirportDate (iKey);
      assert (aAirportDate_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aAirportDate_ptr);

      return *aAirportDate_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    void FacAirportDate::
    initLinkWithOutboundPath (AirportDate& ioAirportDate,
                              OutboundPath& ioOutboundPath) {
      // Link the AirportDate to the OutboundPath, and vice versa
      ioOutboundPath.setAirportDate (&ioAirportDate);
      
      // Add the OutboundPath to the AirportDate internal list (of fixed-length
      // list of OutboundPath objects)
      const COM::OutboundPathKey_T& lOutboundPathKey =
        ioOutboundPath.getPrimaryKey();
      const COM::SegmentNumber_T& lSegmentNumber =
        lOutboundPathKey.segmentNumber;
      assert (lSegmentNumber > 0
              && lSegmentNumber <= MAXIMUM_NUMBER_OF_SEGMENTS_IN_OND);

      // If needed, initialise the list of lists with empty fixed-length
      // outbound-path lists.
      while (ioAirportDate._outboundPathListList.size() <= lSegmentNumber-1) {
        OutboundPathLightList_T lOutboundPathLightList;
        ioAirportDate._outboundPathListList.push_back (lOutboundPathLightList);
      }

      // Retrieve the i-fixed-length Outbound-Path list (i = number of
      // segments).
      OutboundPathLightList_T& lOutboundPathLightList =
        ioAirportDate._outboundPathListList.at (lSegmentNumber-1);

      // Add the OutboundPath to that fixed-length-path list.
      lOutboundPathLightList.push_back (&ioOutboundPath);


      // Add the OutboundPath to the (general) AirportDate internal map (of
      // OutboundPath objects of all lengths).
      const bool insertSucceeded = ioAirportDate._outboundPathList.
        insert (OutboundPathList_T::value_type (ioOutboundPath.describeShortKey(),
                                                &ioOutboundPath)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioAirportDate.describeKey()
                         << " and " << ioOutboundPath.describeShortKey());
        assert (insertSucceeded == true);
      }

    }

    // //////////////////////////////////////////////////////////////////////
    void FacAirportDate::createPathList (AirportDate& ioAirportDate) {
    }
      
  }
}
