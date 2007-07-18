#ifndef __LATUS_COM_BOM_CITYPAIR_HPP
#define __LATUS_COM_BOM_CITYPAIR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>
// Boost (Extended STL)
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
// GSL Random Number Generation (GSL Reference Manual, version 1.7, Chapter 17)
#include <gsl/gsl_rng.h>
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/CityPairDateList.hpp>

namespace LATUS {
  
  namespace COM {

    // Forward declarations
    class BookingDay;
    class CityPairDate;
    
    /** Class storing the context for City Pairs. */
    class CityPair : public BomAbstract {
      friend class FacCityPair;
    private:
      // Private type definitions
      /** Type, for a given CityPair, corresponding to the Departure date
          probability distribution. */
      typedef std::map<double, CityPairDate*> DepDateDistribution_T;
                       
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
      const std::string& getPrimaryKey() const {
        return getDescription();
      }

      /** Get the description, e.g., "NCE-LAX". */
      const std::string& getDescription() const {
        return _description;
      }

      /** Get the total final demand. */
      const double getTotalFinalDemand() const {
        return _totalFinalDemand;
      }

      /** Get the daily rate. */
      const double getDailyRate() const {
        return _dailyRate;
      }

      /** Get the current simulation/booking date (from BookingDay parent). */
      const boost::gregorian::date& getCurrentDate() const;

      /** Get the current simulation/booking time (from BookingDay parent). */
      const boost::posix_time::time_duration& getCurrentTime() const;


      // ///////// Setters //////////
      /** Set the BookingDay (parent class). */
      void setBookingDay (BookingDay* ioBookingDayPtr) {
        _bookingDay = ioBookingDayPtr;
      }

      /** Set the total final demand. */
      void setTotalFinalDemand (const double iTotalFinalDemand) {
        _totalFinalDemand = iTotalFinalDemand;
      }

      /** Set the daily rate */
      void setDailyRate (const double iDailyRate) {
        _dailyRate = iDailyRate;
      }


      // ////////////
      /** Update the daily rates of each CityPairDate, according to the
          current date (of the simulation).
          At the same time, build the daily rate distributions. */
      void updateDailyRate();
      
      /** Draw/generate the inter-arrival time (according to the daily rate
          of the CityPair) corresponding to a reservation/event. */
      double generateExponentialVariate (const double iLambda);

      /** Draw / generate a CityPairDate corresponding to
          a reservation / event.
          <br>When there is no more demand event to generate, the NULL
          pointer is returned. */
      CityPairDate* drawCityPairDate () const;
      
      /** Draw / generate the inter-arrival time, derived from the current
          daily rate, and return the resulting time, i.e.,
          the current time + inter-arrival time. */
      boost::posix_time::time_duration drawNextEventTime ();


      // ///////// Display //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Display the full CityPair context. */
      void display() const;

      /** Display the current CityPair context. */
      void displayCurrent() const;

    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      CityPair (const std::string& iDescription); 

      /** Destructor. */
      virtual ~CityPair();

      /** Initialise the CityPair context:
          <br>Mainly, the random generator is initialised. */
      void initRandomGenerator();

      /** Get the list of (children) CityPair objects. */
      const CityPairDateList_T& getCityPairDateList () const {
        return _cityPairDateList;
      }

      /** Retrieve, if existing, the CityPairDate corresponding to the
          given departure date.
          <br>If not existing, return the NULL pointer. */
      CityPairDate* getCityPairDate (const boost::gregorian::date& iDepDate) const;
      
    private:
      // Parent
      /** Parent class: BookingDay. */
      BookingDay* _bookingDay;
      
      // Attributes
      /** City Pair Description, e.g., "NCE-LAX". */
      const std::string _description;

      /** Children: list of CityPairDate objects (wrapping, for a given
          departure date, the distributions for the corresponding class
          paths/combinations). */
      CityPairDateList_T _cityPairDateList;

      /** Final demand for the whole city pair date (on the date range,
          and for all the class paths/combinations). */
      double _totalFinalDemand;

      /** Daily rate, corresponding to the final demand pro-rated/weighted
          according to the distribution in DTD/departure date. */
      double _dailyRate;

      /** Number of reservations/events made during the simulation day. */
      int _dailyEventNumber;

      /** List, for a given CityPair, holding the Departure date probability
          (discrete) distribution. */
      DepDateDistribution_T _depDateDistribution;
      
      /** (GSL) Random seed. */
      gsl_rng* _rngExponentialPtr;
      gsl_rng* _rngUniformIntPtr;
    };
  }
}
#endif // __LATUS_COM_BOM_CITYPAIR_HPP
