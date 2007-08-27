#ifndef __LATUS_INV_SVC_LATUS_INV_HPP
#define __LATUS_INV_SVC_LATUS_INV_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/service/LATUS_ServiceAbstract.hpp>

namespace LATUS {
  
  namespace INV {

    /** Service (Interface) class for the Inventory module. */
    class LATUS_INV : public COM::LATUS_ServiceAbstract {
      // Only FacInvService_Service may instantiate LATUS_INV
      friend class FacInvService;
    public:
      /** Get the instance corresponding to the given name. */
      static LATUS_INV& instance (const std::string& iInventoryName);

    public:
      /** Calculate and return the availabilities corresponding to a given
          product.
          @return The vector of availabilities per class/bucket. */
      static void calculateAvailabilities (const std::string& iModuleName,
                                           const COM::AirportCode_T& iOrigin,
                                           const COM::AirportCode_T& iDestination,
                                           const COM::DateTime_T& iDate,
                                           COM::BucketAvailabilities_T& ioAvl);

      /** Register the sell of a given number of bookings.
          <br>The party size may be a floating number, so as to cope with
          overbooking. */
      static bool sell (const std::string& iModuleName,
                        const COM::AirportCode_T& iOrigin,
                        const COM::AirportCode_T& iDestination,
                        const COM::DateTime_T& iDate,
                        const COM::BookingNumber_T& iPartySize);

      
    private:
      /** Constructors. */
      LATUS_INV ();
      /** Destructor. */
      ~LATUS_INV();
      /** Initialiser. For example, load the BOM. */
      void initSpecificContext ();

    };
  }
}
#endif // __LATUS_INV_SVC_LATUS_INV_HPP
