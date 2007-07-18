// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/CityPair.hpp>
#include <latus/com/bom/DistributionDetails.hpp>
#include <latus/com/bom/BookingDay.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacCityPair.hpp>
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
    BookingDay& FacBookingDay::
    create (const boost::gregorian::date& iBookingDate) {
      BookingDay* aBookingDay_ptr = NULL;

      aBookingDay_ptr = new BookingDay (iBookingDate);
      assert (aBookingDay_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aBookingDay_ptr);

      return *aBookingDay_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void FacBookingDay::initLinkWithCityPair (BookingDay& ioBookingDay,
                                              CityPair& ioCityPair) {
      // Link the BookingDay to the CityPair, and vice versa
      ioCityPair.setBookingDay (&ioBookingDay);
      
      // Link the BookingDay to the CityPair
      const bool insertSucceeded = ioBookingDay._cityPairList.
        insert (CityPairList_T::value_type (ioCityPair.getPrimaryKey(),
                                            &ioCityPair)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioBookingDay.describeKey()
                         << " and " << ioCityPair.describeKey());
        assert (insertSucceeded == true);
      }
    }
  
    // //////////////////////////////////////////////////////////////////////
    void FacBookingDay::
    createClassPath (BookingDay& ioBookingDay,
                     const std::string& iCityPairDescription,
                     const boost::gregorian::date& iDepDate,
                     const std::string& iClassPathDescription,
                     const double iDistributionMean,
                     const double iDistributionStdDev) {

      const CityPairList_T& lCityPairList = ioBookingDay.getCityPairList();
    
      CityPairList_T::const_iterator itCityPair =
        lCityPairList.find (iCityPairDescription);
    
      // If the CityPair instance does not exist yet, create it
      if (itCityPair == lCityPairList.end()) {
        CityPair& aCityPair =
          FacCityPair::instance().create (iCityPairDescription);

        initLinkWithCityPair (ioBookingDay, aCityPair);
      
        itCityPair = lCityPairList.find (iCityPairDescription);
        assert (itCityPair != lCityPairList.end());
      }
    
      CityPair* lCityPair_ptr = itCityPair->second;
      assert (lCityPair_ptr != NULL);
    
      // Forward the ClassPath object creation request to FacCityPair
      FacCityPair::createClassPath (*lCityPair_ptr, iDepDate,
                                    iClassPathDescription,
                                    iDistributionMean, iDistributionStdDev);
    }
  
  }
}
