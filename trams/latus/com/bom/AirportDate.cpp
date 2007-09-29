// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/NetworkDate.hpp>
#include <latus/com/bom/AirportDate.hpp>
#include <latus/com/bom/OutboundPath.hpp>
#include <latus/com/bom/TravelSolution.hpp>
#include <latus/com/factory/FacTravelSolution.hpp>
#include <latus/com/bom/TravelSolutionList.hpp>
#include <latus/com/bom/TravelSolutionBlock.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    AirportDate::AirportDate (const AirportDateKey_T& iKey)
      : _networkDate (NULL), _key (iKey) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    AirportDate::~AirportDate () {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string AirportDate::describeKey() const {
      return _key.describe();
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string AirportDate::describeShortKey() const {
      return _key.describeShort();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void AirportDate::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << describeKey() << std::endl;

      for (OutboundPathList_T::const_iterator itPath =
             _outboundPathList.begin();
           itPath != _outboundPathList.end(); ++itPath) {
        const OutboundPath* lOutboundPath_ptr = itPath->second;
        assert (lOutboundPath_ptr != NULL);
        
        lOutboundPath_ptr->display ();
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }

    // //////////////////////////////////////////////////////////////////////
    AirportDate* AirportDate::
    getAirportDate (const AirportCode_T& iAirport,
                    const DateTime_T& iReferenceDate) const {
      assert (_networkDate != NULL);
      return _networkDate->getAirportDate (iAirport, iReferenceDate);
    }
    
    // //////////////////////////////////////////////////////////////////////
    OutboundPath* AirportDate::
    getOutboundPathInternal (const std::string& iOutboundPathKey) const {
      OutboundPath* resultOutboundPath_ptr = NULL;
      
      OutboundPathList_T::const_iterator itOutboundPath =
        _outboundPathList.find (iOutboundPathKey);

      if (itOutboundPath != _outboundPathList.end()) {
        resultOutboundPath_ptr = itOutboundPath->second;
      }

      return resultOutboundPath_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    OutboundPath* AirportDate::
    getOutboundPath (const AirportCode_T& iDestination,
                     const Duration_T& iElapsedTime,
                     const SegmentNumber_T& iSegmentNumber,
                     const AirlineNumber_T& iAirlineNumber) const {
      const AirportDateKey_T& lAirportDateKey = getPrimaryKey();
      const OutboundPathKey_T lOutboundPathKey (lAirportDateKey, iDestination,
                                                iElapsedTime, iSegmentNumber,
                                                iAirlineNumber);
      const std::string& lOutboundPathKeyString =
        lOutboundPathKey.describeShort();
      return getOutboundPathInternal (lOutboundPathKeyString);
    }
    
    // //////////////////////////////////////////////////////////////////////
    void AirportDate::
    getOutboundPathList (const AirportCode_T& iDestination,
                         OutboundPathLightList_T& ioPathList) const {

      for (OutboundPathList_T::const_iterator itPath =
             _outboundPathList.begin();
           itPath != _outboundPathList.end(); ++itPath) {
        OutboundPath* lOutboundPath_ptr = itPath->second;
        assert (lOutboundPath_ptr != NULL);

        // Retrieve the destination of the outbound path
        const AirportCode_T& lDestination = lOutboundPath_ptr->getDestination();

        if (lDestination == iDestination) {
          ioPathList.push_back (lOutboundPath_ptr);
        }
      }
      
    }

     // //////////////////////////////////////////////////////////////////////
    void AirportDate::
    createTravelSolutionList (const AirportCode_T& iDestination,
                         TravelSolutionBlock& ioTravelSolutionBlock) const {
      
      for (OutboundPathList_T::const_iterator itPath =
             _outboundPathList.begin();
           itPath != _outboundPathList.end(); ++itPath) {
        OutboundPath* lOutboundPath_ptr = itPath->second;
        assert (lOutboundPath_ptr != NULL);

        // Retrieve the destination of the outbound path
        const AirportCode_T& lDestination = lOutboundPath_ptr->getDestination();

        if (lDestination == iDestination) {          
          // Creation of a new TravelSolution only made by the outbound path. */
          const COM::OutboundPathKey_T& lOutboundPathKey = lOutboundPath_ptr->getOutboundPathKey();
          const COM::TravelSolutionKey_T lTravelSolutionKey (lOutboundPathKey);

          // TODO (Action Item blardeux): Remove any call to Factory within the BOM layer!
          COM::TravelSolution& lTravelSolution =
          COM::FacTravelSolution::instance().create (lTravelSolutionKey);

          lTravelSolution.setOutboundPath(lOutboundPath_ptr);

          COM::TravelSolutionList_T& lTravelSolutionList = ioTravelSolutionBlock.getTravelSolutionList();
          
          lTravelSolutionList.insert (TravelSolutionList_T::
                value_type (lTravelSolution.describeShortKey(),
                            &lTravelSolution));
          
           ioTravelSolutionBlock.incrementTravelSolutionNumber();
        }
      }
      
    }

     // //////////////////////////////////////////////////////////////////////
    OutboundPath* AirportDate::
    getOutboundPath (const std::string& iOutboundPathKeyS) const {
      return getOutboundPathInternal (iOutboundPathKeyS);
    }
    
  }
}
