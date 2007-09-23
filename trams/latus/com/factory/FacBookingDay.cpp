// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/WholeDemand.hpp>
#include <latus/com/bom/BookingDay.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacBookingDay.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {
    
    FacBookingDay* FacBookingDay::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacBookingDay::~FacBookingDay () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacBookingDay& FacBookingDay::instance () {

      if (_instance == NULL) {
        _instance = new FacBookingDay();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    BookingDay& FacBookingDay::create (const DateTime_T& iBookingDate) {
      BookingDay* aBookingDay_ptr = NULL;

      aBookingDay_ptr = new BookingDay (iBookingDate);
      assert (aBookingDay_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aBookingDay_ptr);

      return *aBookingDay_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void FacBookingDay::initLinkWithWholeDemand (BookingDay& ioBookingDay,
                                                 WholeDemand& ioWholeDemand) {
      // Link the BookingDay to the WholeDemand, and vice versa
      ioWholeDemand.setBookingDay (&ioBookingDay);
      ioBookingDay.setWholeDemand (&ioWholeDemand);
    }
    
  }
}
