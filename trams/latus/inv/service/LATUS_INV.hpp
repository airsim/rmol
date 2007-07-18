#ifndef __LATUS_INV_SVC_LATUS_INV_HPP
#define __LATUS_INV_SVC_LATUS_INV_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/service/LATUS_ServiceAbstract.hpp>

namespace LATUS {
  
  namespace INV {

    /** Service (Interface) class for the Inventory module. */
    class LATUS_INV : public COM::LATUS_ServiceAbstract {
    public:

      /** Initialise the context (e.g., load the BOM). */
      void initialise();

      /** Calculate and return the availabilities corresponding to a given
          product.
          @return The vector of availabilities per class/bucket. */
      void calculateAvailabilities (const COM::AirportCode_T& iOrigin,
                                    const COM::AirportCode_T& iDestination,
                                    const COM::DateTime_T& iDate,
                                    COM::BucketAvailabilities_T& ioAvl) const;

      /** Register the sell of a given number of bookings.
          <br>The party size may be a floating number, so as to cope with
          overbooking. */
      bool sell (const COM::AirportCode_T& iOrigin,
                 const COM::AirportCode_T& iDestination,
                 const COM::DateTime_T& iDate,
                 const COM::BookingNumber_T& iPartySize);

    };
  }
}
#endif // __LATUS_INV_SVC_LATUS_INV_HPP
