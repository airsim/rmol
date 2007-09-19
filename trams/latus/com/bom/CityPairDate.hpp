#ifndef __LATUS_COM_BOM_CITYPAIRDATE_HPP
#define __LATUS_COM_BOM_CITYPAIRDATE_HPP

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
#include <latus/com/bom/ClassPathList.hpp>

namespace LATUS {
  
  namespace COM {

    /** Forward declarations. */
    class CityPair;
    class ClassPath;

    /** Class storing the context of a CityPair for a given departure date.
        <br>Mainly, it stores the distributions (of traveller demand)
        for all the class paths/combinations. */
    class CityPairDate : public BomAbstract {
      friend class FacCityPairDate;
    private:
      /** Type, for a given CityPairDate, corresponding to the Class-Path
          probability distribution. */
      typedef std::map<double, ClassPath*> ClassPathDistribution_T;
      
    public:
      // /////////// Getters //////////////
      /** Get the parent class. */
      CityPair* getParent() const {
        return getCityPair();
      }

      /** Get the parent class. */
      CityPair& getParentRef() const {
        return getCityPairRef();
      }

      /** Get the CityPair (parent class). */
      CityPair* getCityPair() const {
        return _cityPair;
      }

      /** Get the CityPair (parent class). */
      CityPair& getCityPairRef() const;

      /** Get the primary key. */
      const DateTime_T& getPrimaryKey() const {
        return getDepartureDate();
      }

      /** Get the departure date. */
      const DateTime_T& getDepartureDate() const {
        return _departureDate;
      }

      /** Get the origin (from the parent class). */
      const AirportCode_T& getOrigin () const;

      /** Get the destination (from the parent class). */
      const AirportCode_T& getDestination () const;

      /** Get the current DTD. */
      const DateOffSet_T& getCurrentDTD() const {
        return _currentDTD;
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


      // ///////// Setters //////////
      /** Set the CityPair (parent class). */
      void setCityPair (CityPair* ioCityPairPtr) {
        _cityPair = ioCityPairPtr;
      }

      /** Set the current DTD. */
      void setCurrentDTD (const DateOffSet_T& iCurrentDTD) {
        _currentDTD = iCurrentDTD;
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
      /** Update the daily rates of each ClassPath, according to the
          current date (of the simulation).
          At the same time, build the daily rate distributions. */
      void updateDailyRate();
      
      /** Draw / generate a ClassPath corresponding to a
          reservation / event.
          <br>When there is no more demand event to generate, the NULL
          pointer is returned. */
      ClassPath* drawClassPath () const;
      

      // ///////// Display //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Display the structure in-depth, from the current
          CityPairDate object. */
      void display (const bool iIndented) const;
      
      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      CityPairDate (const DateTime_T& iDepartureDate);
      CityPairDate ();
      CityPairDate (const CityPairDate&);

      /** Destructor. */
      virtual ~CityPairDate();

      /** Initialise the CityPair context:
          <br>Mainly, the random generator is initialised. */
      void initRandomGenerator();

      /** Get the (children) list of ClassPath objects. */
      const ClassPathList_T& getClassPathList() const {
        return _classPathList;
      }

      /** Retrieve, if existing, the ClassPath corresponding to the
          given class path/combination description.
          <br>If not existing, return the NULL pointer. */
      ClassPath* getClassPath (const std::string& iDescription) const;

    private:
      // Attributes
      /** Parent class: CityPair. */
      CityPair* _cityPair;
      
      /** Departure Date (for the demand corresponding to the
          given CityPair). */
      DateTime_T _departureDate;

      /** States whether or not the departure date has been passed over. */
      bool _hasDeparted;

      /** Days-to-Departure (DTD), expressed as the number of days
          separating the current booking date from the departure date. */
      DateOffSet_T _currentDTD;

      /** Children: list of ClassPath objects (wrapping, for a given
          class path/combination, the final demand distribution). */
      ClassPathList_T _classPathList;

      /** Final demand for the whole city pair date (on the date range,
          and for all the class paths/combinations). */
      double _totalFinalDemand;

      /** Daily rate, corresponding to the final demand pro-rated/weighted
          according to the distribution in DTD/departure date. */
      double _dailyRate;

      /** List, for a given CityPairDate, holding the Class-Path probability
          (discrete) distribution. */
      ClassPathDistribution_T _classPathDistribution;

      /** (GSL) Random seed. */
      gsl_rng* _rngUniformIntPtr;
    };

  }
}
#endif // __LATUS_COM_BOM_CITYPAIRDATE_HPP
