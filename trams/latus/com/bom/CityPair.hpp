#ifndef __LATUS_COM_BOM_CITYPAIR_HPP
#define __LATUS_COM_BOM_CITYPAIR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>
// GSL Random Number Generation (GSL Reference Manual, version 1.7, Chapter 17)
#include <gsl/gsl_rng.h>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/CityPairKey.hpp>
#include <latus/com/bom/CityPairDateList.hpp>
#include <latus/com/bom/Event.hpp>

namespace LATUS {
  
  namespace COM {

    // Forward declarations
    class WholeDemand;
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
      WholeDemand* getParent() const {
        return getWholeDemand();
      }

      /** Get the WholeDemand (parent class). */
      WholeDemand* getWholeDemand() const {
        return _wholeDemand;
      }

      /** Get the primary key. */
      const CityPairKey_T& getPrimaryKey() const {
        return getCityPairKey();
      }

      /** Get the city pair key. */
      const CityPairKey_T& getCityPairKey() const {
        return _key;
      }

      /** Get the origin (part of the primary key). */
      const AirportCode_T& getOrigin () const {
        return _key.airportPairKey.boardPoint;
      }

      /** Get the destination (part of the primary key). */
      const AirportCode_T& getDestination () const {
        return _key.airportPairKey.offPoint;
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
      const DateTime_T& getCurrentDate() const;

      /** Get the current simulation/booking time (from BookingDay parent). */
      const Duration_T& getCurrentTime() const;

      /** Retrieve, if existing, the CityPairDate corresponding to the
          given departure date.
          <br>If not existing, return the NULL pointer. */
      CityPairDate* getCityPairDate (const DateTime_T& iDepDate) const;
      

      // ///////// Setters //////////
      /** Set the WholeDemand (parent class). */
      void setWholeDemand (WholeDemand* ioWholeDemandPtr) {
        _wholeDemand = ioWholeDemandPtr;
      }

      /** Set the total final demand. */
      void setTotalFinalDemand (const double iTotalFinalDemand) {
        _totalFinalDemand = iTotalFinalDemand;
      }

      /** Set the daily rate */
      void setDailyRate (const double iDailyRate) {
        _dailyRate = iDailyRate;
      }



      // ///////// Display //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Get a string describing the short key. */
      const std::string describeShortKey() const;

      /** Display the full CityPair context. */
      void display() const;

      /** Display the current CityPair context. */
      void displayCurrent() const;


      // //////////// Business Support Methods ///////////
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
      Duration_T drawNextEventTime ();

      /** Draw / generate a reservation / event for the given CityPair,
          and add it to the dedicated queue.
          <br>That encompasses the following steps:
          <br><ol>
            <li>Draw / generate the inter-arrival time of the next event.
            That inter-arrival time is then added to the current (booking)
            time (of the Booking Day) to give the (booking) time of the
            next event. For example, if the current booking time is 10:45:22
            and the inter-arrival time is 05:12:30, then the (booking) time
            of the next event is: 15:57:52.</li>
		    <li>Draw / generate a departure date, according to the uniform 
			daily rate distribution (helper object) attached to the given
			CityPair object.</li>
			<li>Draw / generate a class-path, according to the uniform
			daily rate distribution (helper object) attached to each of the
			CityPairDate objects of the given CityPair.</li>
			<li>Build a reservation / event object with those elements
			(booking time and the combination of departure date and 
			class-path).</li>
          </ol>. */
      void drawCityPairNextEvent (EventList_T&);
      

    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      CityPair (const CityPairKey_T&); 

      /** Destructor. */
      virtual ~CityPair();

      /** Initialise the CityPair context:
          <br>Mainly, the random generator is initialised. */
      void initRandomGenerator();

      /** Get the list of (children) CityPair objects. */
      const CityPairDateList_T& getCityPairDateList () const {
        return _cityPairDateList;
      }


    private:
      // Parent
      /** Parent class: BookingDay, WholeDemand. */
      WholeDemand* _wholeDemand;
      
      // Attributes
      /** City Pair Key is composed of the origin and destination (e.g.,
          "NCE-LAX"). */
      CityPairKey_T _key;

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
