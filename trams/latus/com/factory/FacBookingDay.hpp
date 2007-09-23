#ifndef __LATUS_COM_FAC_FACBOOKINGDAY_HPP
#define __LATUS_COM_FAC_FACBOOKINGDAY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {
  
  namespace COM {

    /** Forward declarations. */
    class BookingDay;
    class WholeDemand;
    
    /** Factory for BookingDay objects. */
    class FacBookingDay : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacBookingDay& */
      static FacBookingDay& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacBookingDay::instance() */
      virtual ~FacBookingDay();

      /** Create a new BookingDay object.
          <br>This new object is added to the list of instantiated objects.
          @return BookingDay& The newly created object. */
      BookingDay& create (const DateTime_T& iBookingDate);

      /** Initialise the link between a BookingDay and a WholeDemand.
          @param BookingDay&
          @param WholeDemand&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithWholeDemand (BookingDay&, WholeDemand&);

    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacBookingDay () {}

    private:
      /** The unique instance.*/
      static FacBookingDay* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACBOOKINGDAY_HPP
