#ifndef __LATUS_COM_FAC_FACCITYPAIRDATE_HPP
#define __LATUS_COM_FAC_FACCITYPAIRDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {
  
  namespace COM {

    /** Forward declarations. */
    class BookingDay;
    class CityPair;
    
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
      BookingDay& create (const boost::gregorian::date& iBookingDate);

      /** Initialise the link between a BookingDay and a CityPair.
          @param BookingDay&
          @param CityPair&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithCityPair (BookingDay&, CityPair&);

      /** Create a new ClassPath object with the given parameters.
          <br>This new object is added to the list of instantiated objects.
          <br>Any missing intermediary object (CityPair and/or CityPairDate)
          will be created and added to the corresponding children list. */
      static void createClassPath (BookingDay&,
                                   const AirportCode_T& iOrigin,
                                   const AirportCode_T& iDestination,
                                   const boost::gregorian::date& iDepDate,
                                   const std::string& iCabinCode,
                                   const std::string& iClassCode,
                                   const double iDistributionMean,
                                   const double iDistributionStdDev);
      
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
#endif // __LATUS_COM_FAC_FACCITYPAIRDATE_HPP
