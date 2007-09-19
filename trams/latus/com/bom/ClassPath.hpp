#ifndef __LATUS_COM_BOM_CLASSPATH_HPP
#define __LATUS_COM_BOM_CLASSPATH_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/DistributionDetails.hpp>

namespace LATUS {
  
  namespace COM {

    /** Forward declarations. */
    class CityPairDate;

    /** Class storing the context for Class Path associated
        to departure dates. */
    class ClassPath : public BomAbstract {
      friend class FacClassPath;
    public:
      // /////////// Getters //////////////
      /** Get the parent class. */
      CityPairDate* getParent() const {
        return getCityPairDate();
      }

      /** Get the parent class. */
      CityPairDate& getParentRef() const {
        return getCityPairDateRef();
      }

      /** Get the CityPairDate (parent class). */
      CityPairDate* getCityPairDate() const {
        return _cityPairDate;
      }

      /** Get the CityPairDateRef (parent class). */
      CityPairDate& getCityPairDateRef() const;

      /** Get the primary key. */
      const std::string& getPrimaryKey() const {
        return getDescription();
      }

      /** Get the description, e.g., "H-H". */
      const std::string& getDescription() const {
        return _description;
      }

      /** Get the mean value of the final demand distribution. */
      const double getDistributionMean() const {
        return _distributionDetails.first;
      }

      /** Get the standard deviation of the final demand distribution. */
      const double getDistributionStdDev() const {
        return _distributionDetails.second;
      }

      /** Get the daily rate. */
      const double getDailyRate() const {
        return _dailyRate;
      }

      /** Get the origin (from CityPair parent). */
      const AirportCode_T& getOrigin () const;

      /** Get the destination (from CityPair parent). */
      const AirportCode_T& getDestination () const;

      /** Get the current simulation/booking date (from CityPair parent). */
      const DateTime_T& getCurrentDate() const;

      /** Get the departure date (from CityPairDate parent). */
      const DateTime_T& getDepartureDate() const;

      /** Get the current DTD (from the CityPairDate parent). */
      const DateOffSet_T& getCurrentDTD() const;

      
      // ///////// Setters //////////
      /** Set the CityPairDate (parent class). */
      void setCityPairDate (CityPairDate* ioCityPairDatePtr) {
        _cityPairDate = ioCityPairDatePtr;
      }

      /** Set the daily rate */
      void setDailyRate (const double iDailyRate) {
        _dailyRate = iDailyRate;
      }


      // ///////// Display //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Display the structure in-depth, from the current ClassPath object. */
      void display (const bool iIndented) const;


      // //////////
      /** Update the daily rate according to a given distribution (e.g., here,
          Weibull). */
      void updateDailyRate();

      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      ClassPath (const std::string& iDescription,
                 const DistributionDetails_T&);

      /** Destructor. */
      virtual ~ClassPath();

    private:
      // Attributes
      /** Parent class: CityPairDate. */
      CityPairDate* _cityPairDate;
      
      /** Class Path Description, e.g., "H-H". */
      const std::string _description;

      /** Mean value and standard deviation of the Final Demand Distribution.*/
      const DistributionDetails_T _distributionDetails;

      /** Daily rate, corresponding to the final demand pro-rated/weighted
          according to the distribution in DTD/departure date. */
      double _dailyRate;
    };
    
  }
}
#endif // __LATUS_COM_BOM_CLASSPATH_HPP
