#ifndef __LATUS_CRS_SVC_LATUS_CRS_HPP
#define __LATUS_CRS_SVC_LATUS_CRS_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/service/LATUS_ServiceAbstract.hpp>

namespace LATUS {
  
  namespace CRS {

    /** Service (Interface) class for the CRS (Central Reservation System)
        module. */
    class LATUS_CRS : public COM::LATUS_ServiceAbstract {
      // Only FacCrsService_Service may instantiate LATUS_CRS
      friend class FacCrsService;
    public:

      /** Set the input file name (for test purposes). */
      void setInputFilename (const std::string&);

      /** Calculate and return the availabilities corresponding to a given
          product.
          @return The vector of Travel Solutions (TS). */
      void provideTravelSolution (const COM::AirportCode_T& iOrigin,
                                  const COM::AirportCode_T& iDestination,
                                  const COM::DateTime_T& iDate,
                                  COM::TravelSolutionList_T& ioTSL) const;

      /** Register the sell of a given number of travellers on a given
          Travel Solution.
          <br>The party size may be a floating number, so as to cope with
          overbooking. */
      bool sell (const COM::TravelSolutionList_T& iTS,
                 const COM::BookingNumber_T& iPartySize);

    private:
      /** Constructors. */
      LATUS_CRS (const std::string& iModuleName);
      /** Destructor. */
      ~LATUS_CRS();

    private:
      /** Initialiser (e.g., to load the BOM). */
      void initSpecificContext ();
      
    };
  }
}
#endif // __LATUS_CRS_SVC_LATUS_CRS_HPP
