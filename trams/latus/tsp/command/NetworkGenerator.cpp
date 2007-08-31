// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/basic/BasConst_LATUS_Service.hpp>
#include <latus/com/bom/Network.hpp>
#include <latus/com/bom/NetworkDate.hpp>
#include <latus/com/bom/AirportDate.hpp>
#include <latus/com/bom/OutboundPath.hpp>
#include <latus/com/bom/WorldSchedule.hpp>
#include <latus/com/bom/Inventory.hpp>
#include <latus/com/bom/FlightDate.hpp>
#include <latus/com/bom/SegmentDate.hpp>
#include <latus/com/factory/FacNetwork.hpp>
#include <latus/com/factory/FacNetworkDate.hpp>
#include <latus/com/factory/FacAirportDate.hpp>
#include <latus/com/factory/FacOutboundPath.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS TSP
#include <latus/tsp/command/NetworkGenerator.hpp>

namespace LATUS {

  namespace TSP {

    // //////////////////////////////////////////////////////////////////////
    COM::Network& NetworkGenerator::
    createNetwork (const COM::WorldSchedule& iWorldSchedule) {
      // Create a mere Network object.
      COM::Network& lNetwork = COM::FacNetwork::instance().create ();

      // Create the rest of the Network BOM (NetworkDate, AirportDate and
      // Outbound-Path objects).
      createNetwork (lNetwork, iWorldSchedule);

      return lNetwork;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void NetworkGenerator::
    createNetwork (COM::Network& ioNetwork,
                   const COM::WorldSchedule& iWorldSchedule) {
      // Build the single-segment OutboundPath objects, and the corresponding
      // list of those objects.
      const COM::InventoryList_T& lInventoryList =
        iWorldSchedule.getInventoryList();
      for (COM::InventoryList_T::const_iterator itInventory =
             lInventoryList.begin();
           itInventory != lInventoryList.end(); ++itInventory) {
        const COM::Inventory* lInventory_ptr = itInventory->second;
        assert (lInventory_ptr != NULL);

        createSinglePaths (ioNetwork, *lInventory_ptr);
      }

      // Build the i-fixed-length lists of OutboundPath objects, and the lists
      // of lists. In other words, build the whole Network.
      for (COM::SegmentNumber_T i = 2;
           i <= COM::MAXIMUM_NUMBER_OF_SEGMENTS_IN_OND; ++i) {
        createNetwork (ioNetwork, i);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void NetworkGenerator::
    createSinglePaths (COM::Network& ioNetwork,
                       const COM::Inventory& iInventory) {
      const COM::FlightDateList_T& lFlightDateList =
        iInventory.getFlightDateList();
      for (COM::FlightDateList_T::const_iterator itFlightDate =
             lFlightDateList.begin();
           itFlightDate != lFlightDateList.end(); ++itFlightDate) {
        const COM::FlightDate* lFlightDate_ptr = itFlightDate->second;
        assert (lFlightDate_ptr != NULL);

        createSinglePaths (ioNetwork, *lFlightDate_ptr);
      }
    }
    
    // //////////////////////////////////////////////////////////////////////
    void NetworkGenerator::
    createSinglePaths (COM::Network& ioNetwork,
                       const COM::FlightDate& iFlightDate) {
      const COM::SegmentDateList_T& lSegmentDateList =
        iFlightDate.getSegmentDateList();      
      for (COM::SegmentDateList_T::const_iterator itSegmentDate =
             lSegmentDateList.begin();
           itSegmentDate != lSegmentDateList.end(); ++itSegmentDate) {
        const COM::SegmentDate* lSegmentDate_ptr = itSegmentDate->second;
        assert (lSegmentDate_ptr != NULL);

        createSinglePaths (ioNetwork, *lSegmentDate_ptr);
      }
    }
    
    // //////////////////////////////////////////////////////////////////////
    void NetworkGenerator::
    createSinglePaths (COM::Network& ioNetwork,
                       const COM::SegmentDate& iSegmentDate) {
      // Retrieve the reference date for the AirportDate, which is also
      // the board date for the SegmentDate.
      const COM::DateTime_T& lReferenceDate = iSegmentDate.getBoardDate();

      // If a NetworkDate with that reference date does not exist yet,
      // create one.
      COM::NetworkDate* lNetworkDate_ptr =
        ioNetwork.getNetworkDate (lReferenceDate);
      if (lNetworkDate_ptr == NULL) {
        // Create the NetworkDate with the primary key (reference date)
        const COM::NetworkDateKey_T lNetworkDateKey (lReferenceDate);
        lNetworkDate_ptr = 
          &COM::FacNetworkDate::instance().create (lNetworkDateKey);
        assert (lNetworkDate_ptr != NULL);

        // Link the NetworkDate with the Network
        COM::FacNetwork::initLinkWithNetworkDate (ioNetwork, *lNetworkDate_ptr);
      }
      assert (lNetworkDate_ptr != NULL);

      // Go down recursively in the Network-BOM depth for the origin
      // (board point of the SegmentDate), but not for the destination (off
      // point of the SegmentDate), as the Network is made of origin nodes
      // and outbound pathes.
      createSinglePaths (*lNetworkDate_ptr, iSegmentDate);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void NetworkGenerator::
    createSinglePaths (COM::NetworkDate& ioNetworkDate,
                       const COM::SegmentDate& iSegmentDate) {
      // Retrieve the origin for the AirportDate, which is also
      // the board point for the SegmentDate.
      const COM::AirportCode_T& lOrigin = iSegmentDate.getBoardPoint();

      // If an AirportDate with that reference date does not exist yet,
      // create one.
      COM::AirportDate* lAirportDate_ptr =
        ioNetworkDate.getAirportDate (lOrigin);
      if (lAirportDate_ptr == NULL) {
        // Create the AirportDate with the primary key (NetworkDateKey + origin)
        const COM::NetworkDateKey_T& lNetworkDateKey =
          ioNetworkDate.getPrimaryKey();
        const COM::AirportDateKey_T lAirportDateKey (lNetworkDateKey, lOrigin);
        lAirportDate_ptr = 
          &COM::FacAirportDate::instance().create (lAirportDateKey);
        assert (lAirportDate_ptr != NULL);

        // Link the AirportDate with the NetworkDate
        COM::FacNetworkDate::initLinkWithAirportDate (ioNetworkDate,
                                                      *lAirportDate_ptr);
      }
      assert (lAirportDate_ptr != NULL);

      // Go down recursively in the Network-BOM depth for the origin
      // (board point of the SegmentDate), but not for the destination (off
      // point of the SegmentDate), as the Network is made of origin nodes
      // and outbound pathes.
      createSinglePaths (*lAirportDate_ptr, iSegmentDate);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void NetworkGenerator::
    createSinglePaths (COM::AirportDate& ioAirportDate,
                       const COM::SegmentDate& iSegmentDate) {
      // Build the OutboundPath key elements
      const COM::AirportDateKey_T& lAirportDateKey =
        ioAirportDate.getPrimaryKey();
      const COM::AirportCode_T& lDestination = iSegmentDate.getOffPoint();
      const COM::Duration_T& lElapsedTime = iSegmentDate.getElapsedTime();
      // There is a single segment in the list
      const COM::SegmentNumber_T lSegmentNumber = 1;
      // There is a single airline in the list (since there is a single segment)
      const COM::AirlineNumber_T lAirlineNumber = 1;

      // If an OutboundPath with those parameters does not exist yet,
      // create one.
      COM::OutboundPath* lOutboundPath_ptr =
        ioAirportDate.getOutboundPath (lDestination, lElapsedTime,
                                       lSegmentNumber, lAirlineNumber);

      if (lOutboundPath_ptr == NULL) {
        const COM::OutboundPathKey_T lOutboundPathKey (lAirportDateKey,
                                                       lDestination,
                                                       lElapsedTime,
                                                       lSegmentNumber,
                                                       lAirlineNumber);
        lOutboundPath_ptr =
          &COM::FacOutboundPath::instance().create (lOutboundPathKey);
        assert (lOutboundPath_ptr != NULL);

        // Add the SegmentDate reference to the dedicated list within
        // the OutboundPath. Note that this must be done before the
        // link between the OutboundPath and AirportDate, as that latter
        // method uses the number of segments within the OutboundPath
        // object.
        COM::FacOutboundPath::initLinkWithSegmentDate (*lOutboundPath_ptr,
                                                       iSegmentDate);
        
        // Link the OutboundPath to the AirportDate
        COM::FacAirportDate::initLinkWithOutboundPath (ioAirportDate,
                                                       *lOutboundPath_ptr);
      }
    }
    
    // //////////////////////////////////////////////////////////////////////
    void NetworkGenerator::
    createNetwork (COM::Network& ioNetwork,
                   const COM::SegmentNumber_T& iSegmentNumber) {

      // Iterate on the NetworkDate objects
      const COM::NetworkDateList_T& lNetworkDateList =
        ioNetwork.getNetworkDateList();
      for (COM::NetworkDateList_T::const_iterator itNetworkDate =
             lNetworkDateList.begin();
           itNetworkDate != lNetworkDateList.end(); ++itNetworkDate) {
        COM::NetworkDate* lNetworkDate_ptr = itNetworkDate->second;
        assert (lNetworkDate_ptr != NULL);

        createNetwork (*lNetworkDate_ptr, iSegmentNumber);
      }
    }
    
    // //////////////////////////////////////////////////////////////////////
    void NetworkGenerator::
    createNetwork (COM::NetworkDate& ioNetworkDate,
                   const COM::SegmentNumber_T& iSegmentNumber) {
      assert (iSegmentNumber >= 2
              && iSegmentNumber <= COM::MAXIMUM_NUMBER_OF_SEGMENTS_IN_OND);
      
      // Iterate on the AirportDate objects
      const COM::AirportDateList_T& lAirportList =
        ioNetworkDate.getAirportDateList();
      for (COM::AirportDateList_T::const_iterator itAirportDate =
             lAirportList.begin();
           itAirportDate != lAirportList.end(); ++itAirportDate) {
        COM::AirportDate* lAirportDate_ptr = itAirportDate->second;
        assert (lAirportDate_ptr != NULL);

        createNetwork (*lAirportDate_ptr, iSegmentNumber);
      }
    }
    
    // //////////////////////////////////////////////////////////////////////
    void NetworkGenerator::
    createNetwork (COM::AirportDate& ioAirportDate,
                   const COM::SegmentNumber_T& iSegmentNumber) {

      // The goal of that method is to build the i-fixed-length
      // Outbound-Path objects, knowing that all the
      // lower-fixed-length Outbound-Path objects have already been
      // built during the previous steps. Once an i-fixed-length
      // Outbound-Path object is created, it is added to the list of
      // the (fixed-length Outbound-Path object) lists.
      //
      // Hence, at that iteration, by construction, the list of the
      // (fixed-length Outbound-Path object) lists should already get
      // a size of i-1, if there were such possibilities (in terms of
      // Outbound Pathes). In that case, at the end of the method, its
      // size should be of i.
      //
      // If the size of the list of the (fixed-length Outbound-Path
      // object) lists is (strictly) less than i-1, it means that that
      // airport date has no more possibilities of destinations. We
      // are thus done at that stage.
      const COM::OutboundPathListList_T& lOutboundPathListList =
        ioAirportDate.getOutboundPathListList();
      if (lOutboundPathListList.size() < iSegmentNumber - 1) {
        return;
      }
      
      // Retrieve the (i-1)-fixed-length Outbound-Path list (i = number of
      // segments).
      //
      // Note that a STL vector starts at 0, whereas the number of segments
      // starts at 1. Hence, (i-1) for the length (in number of segments)
      // corresponds to [iSegmentNumber-2] for the STL vector.
      //  
      // As the lOutboundPathListList may change during the next loop
      // iterations (as some OutboundPath objects are created and linked to
      // AirportDate), we need to take the initial copy of that list.
      const COM::OutboundPathLightList_T lOutboundPathLightList_im1 =
        lOutboundPathListList.at (iSegmentNumber-2);

      // Iterate on the (i-1)-fixed-length Outbound-Path objects, in order
      // to build a i-fixed-length Outbound-Path objects. There are two steps:
      // 1. Retrieve the airport-dates at a (i-1) length (in number of segments)
      //    of the origin airport-date.
      // 2. From each of such (i-1) airport-date, add the single-segment pathes
      //    to the (i-1)-length pathes, so as to make i-length pathes.
      for (COM::OutboundPathLightList_T::const_iterator itOutboundList =
             lOutboundPathLightList_im1.begin();
           itOutboundList != lOutboundPathLightList_im1.end();
           ++itOutboundList) {
        const COM::OutboundPath* lOutboundPath_im1_ptr = *itOutboundList;
        assert (lOutboundPath_im1_ptr != NULL);

        // Get the off point of the (i-1)-length OutboundPath attached to
        // the current AirportDate (*lAirportDate_ptr).
        // Note that "im1" stands for "i minus 1", i.e., (i-1).
        const COM::AirportDate* lDestination_im1_ptr =
          lOutboundPath_im1_ptr->getDestinationAirportDate();

        // If there is no AirportDate corresponding to the destination (off
        // point of the last SegmentDate), it means that the destination is
        // an end point (no other SegmentDate is starting from there).
        // Hence, there is nothing else to do for now for that AirportDate.
        if (lDestination_im1_ptr == NULL) {
          return;
        }
        assert (lDestination_im1_ptr != NULL);
        
        // Retrieve the single-segment Outbound-Path list,
        // so as to make a i-length OutboundPath.
        const COM::OutboundPathListList_T& lDestinationOutboundPathListList =
          lDestination_im1_ptr->getOutboundPathListList();
        assert (lDestinationOutboundPathListList.size() >= 1);

        // As the lDestinationOutboundPathListList may change during
        // the next loop iterations (as some OutboundPath objects are
        // created and linked to AirportDate), we need to take the initial
        // copy of that list.
        const COM::OutboundPathLightList_T lDestinationOutboundPathLightList_1 =
          lDestinationOutboundPathListList.at (0);

        for (COM::OutboundPathLightList_T::const_iterator
               itDestinationOutboundList =
               lDestinationOutboundPathLightList_1.begin();
             itDestinationOutboundList
               != lDestinationOutboundPathLightList_1.end();
             ++itDestinationOutboundList) {
          COM::OutboundPath* lOutboundPath_1_ptr =
            *itDestinationOutboundList;
          assert (lOutboundPath_1_ptr != NULL);

          // Check that a passenger can connect (i.e., be able to do the
          // transfer from one plane to another). If the transfer/connection
          // is not feasible, then the current single-segment outbound-path
          // must not be added. And there is nothing more to do at that stage.
          const bool isConnectable =
            lOutboundPath_im1_ptr->isConnectable (*lOutboundPath_1_ptr);
          if (isConnectable == false) {
            continue;
          }
          
          // Get the off point of the single-segment OutboundPath
          // attached to the intermediate destination (im1). That off point is
          // at a length i of the initial AirportDate: (i-1) + 1.
          const COM::AirportCode_T& lDestination_i =
            lOutboundPath_1_ptr->getDestination();

          // If the new destination leads the full outbound path (length of i)
          // back to the origin (even if the dates are different), it is
          // useless to add that single-segment to the (i-1) outbound path:
          // there is nothing more to be done at that stage, and we can handle
          // the next single-segment outbound-path.
          if (lDestination_i == ioAirportDate.getOrigin()) {
            continue;
          }

          // Build the i-length OutboundPath
          const COM::AirportDateKey_T& lAirportDateKey =
            ioAirportDate.getPrimaryKey();

          // Get the parameters of the last segment
          const COM::SegmentDate* lSegmentDate_1_ptr =
            lOutboundPath_1_ptr->getFirstSegmentDate();
          assert (lSegmentDate_1_ptr != NULL);
          
          // Calculate the number of airlines flown by the i-length
          // outbound path
          const COM::AirlineCode_T& lAirlineCode_1 =
            lSegmentDate_1_ptr->getAirlineCode();
          COM::AirlineNumber_T lAirlineNumber_i =
            lOutboundPath_im1_ptr->getAirlineNumber();
          if (lOutboundPath_im1_ptr->isAirlineFlown(lAirlineCode_1) == false) {
            ++lAirlineNumber_i;
          }

          // It may happen, when i=2 (=> i-1 = 1), that the combination
          // of the (single-segment) outbound path with the segment-date
          // produces a segment-date of the same flight-date. For instance,
          // BA9 LHR-BKK and BA9 BKK-SYD add up to BA9 LHR-SYD, which is
          // already a segment-date of the BA9 flight-date.
          // In that case, there is no need to add up the segment-date
          // to the (single-segment) outbound-path.
          const COM::SegmentNumber_T& lSegmentNumber_im1 =
            lOutboundPath_im1_ptr->getSegmentNumber();
          if (lSegmentNumber_im1 == 1) {
            const COM::SegmentDate* lSegment_im1_ptr =
              lOutboundPath_im1_ptr->getFirstSegmentDate();
            assert (lSegment_im1_ptr != NULL);
            if (lSegment_im1_ptr->getAirlineCode() == lAirlineCode_1
                && lSegment_im1_ptr->getFlightNumber()
                == lSegmentDate_1_ptr->getFlightNumber()) {
              continue;
            }
          }
            
          // Calculate the total elapsed time flown by the i-length
          // outbound path
          const COM::Duration_T lElapsedTime_i =
            lOutboundPath_im1_ptr->calculateElapsedTimeFromRouting (*lSegmentDate_1_ptr);
          
          const COM::OutboundPathKey_T lOutboundPathKey_i (lAirportDateKey,
                                                           lDestination_i,
                                                           lElapsedTime_i,
                                                           iSegmentNumber,
                                                           lAirlineNumber_i);
          COM::OutboundPath& lOutboundPath_i =
            COM::FacOutboundPath::instance().create (lOutboundPathKey_i);

          // Clone the list of SegmentDate references of the given OutboundPath
          // object (passed as the second parameter).
          COM::FacOutboundPath::cloneSegmentDateLinks (lOutboundPath_i,
                                                       *lOutboundPath_im1_ptr);
          
          // Add the SegmentDate reference to the dedicated list within
          // the OutboundPath. Note that this must be done before the
          // link between the OutboundPath and AirportDate, as that latter
          // method uses the number of segments within the OutboundPath
          // object.
          COM::FacOutboundPath::initLinkWithSegmentDate (lOutboundPath_i,
                                                         *lSegmentDate_1_ptr);
          
          // Link the OutboundPath to the AirportDate
          COM::FacAirportDate::initLinkWithOutboundPath (ioAirportDate,
                                                         lOutboundPath_i);
        }
      }
    }
    
  }
}
