#ifndef __LATUS_COM_BOM_WHOLEDEMAND_HPP
#define __LATUS_COM_BOM_WHOLEDEMAND_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/CityPairList.hpp>
#include <latus/com/bom/Event.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class BookingDay;

    /** Class wrapping all the demand event generators (city-pair, departure
        date, WTP, etc.). */
    class WholeDemand : public BomAbstract {
      friend class FacWholeDemand;
    private:
      // Private type definitions
      /** Type, for a given BookingDay, corresponding to the City Pair
          probability distribution.
          <br>Note that that probability distribution is normally not used:
          it is here for debugging purpose only. */
      typedef std::map<double, std::string> CityPairDistribution_T;
                       
    public:
      // /////////// Getters //////////////
      /** Get the parent class. */
      BookingDay* getParent() const {
        return getBookingDay();
      }

      /** Get the BookingDay (parent class). */
      BookingDay* getBookingDay() const {
        return _bookingDay;
      }

      /** Get the primary key. */
      const DateTime_T& getPrimaryKey() const {
        return getUpdateDate();
      }

      /** Get the update/creation date for the world schedule data. */
      const DateTime_T& getUpdateDate() const {
        return _updateDate;
      }

      /** Get the daily rate. */
      const double getDailyRate() const {
        return _dailyRate;
      }
      
      /** Get the current simulation/booking date (from BookingDay parent). */
      const DateTime_T& getCurrentDate() const;

      /** Get the current simulation/booking time (from BookingDay parent). */
      const Duration_T& getCurrentTime() const;

      /** Get the reference on the CityPair object. */
      CityPair& getCityPair () const;
      
      /** Retrieve, if existing, the CityPair corresponding to the
          given airline code (CityPair key).
          <br>If not existing, return the NULL pointer. */
      CityPair* getCityPair (const AirportCode_T&, const AirportCode_T&) const;
      

      // ///////// Setters //////////
      /** Set the BookingDay (parent class). */
      void setBookingDay (BookingDay* ioBookingDayPtr) {
        _bookingDay = ioBookingDayPtr;
      }

      /** Set the update/creation date for the world schdule data. */
      void setUpdateDate (const DateTime_T& iUpdateDate) {
        _updateDate = iUpdateDate;
      }
      
      /** Set the daily rate. */
      void setDailyRate (const double iDailyRate) {
        _dailyRate = iDailyRate;
      }

      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Display the full CityPair context. */
      void display() const;


      // /////////// Main Business Methods ////////////
      /** Update the daily rates for all the CityPair objects.
          <br>The daily rate depends on:
          <br><ol>
          <li>The current / booking date.</li>
          <li>The departure date of each CityPairDate object.</li>
          </ol>
          Indeed, the daily rate depends on the remaining
          Days-To-Departure (DTD), calculated as being the difference between
          the departure date and the date at which the booking is made.
          <br>Note that that method also builds the daily rate
          distributions (helper objects) stored within the CityPair and
          CityPairDate objects. */
      void updateDailyRate();
      
      /** Initialisation of the reservation / event list.
          <br>Draw / generate a reservation / event for each CityPair object.
          <br>Each CityPair must get one (and only one) reservation / event. */
      void drawEventsForAllCityPairs (EventList_T&);
      

    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      WholeDemand (const DateTime_T& iUpdateDate); 

      /** Default constructors. */
      WholeDemand ();
      WholeDemand (const WholeDemand&);
      
      /** Destructor. */
      virtual ~WholeDemand();

      /** Get the list of (children) CityPair objects. */
      const CityPairList_T& getCityPairList () const {
        return _cityPairList;
      }

      /** Retrieve, if existing, the CityPair corresponding to the
          given CityPair key (airline code).
          <br>If not existing, return the NULL pointer.
          <br>Note that the string must be formed thanks to the
          CityPairKey::describeShort() method, as that latter is used when
          inserting the CityPair within the WholeDemand dedicated list. */
      CityPair* getCityPairInternal (const std::string& iCityPairKey) const;
      

    private:
      // Parent
      /** Parent class: BookingDay. */
      BookingDay* _bookingDay;

      // Attributes
      /** Children: list of CityPair objects. */
      CityPairList_T _cityPairList;

      /** Update/creation date for the WholeDemand data. */
      DateTime_T _updateDate;

      /** Daily rate, corresponding to the final demand pro-rated/weighted
          according to the distribution in City Pairs. */
      double _dailyRate;

      /** List, for a given BookingDay, holding the Departure date probability
          (discrete) distribution. */
      CityPairDistribution_T _cityPairDistribution;
    };

  }
}
#endif // __LATUS_COM_BOM_WHOLEDEMAND_HPP
