// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/CityPair.hpp>
#include <latus/com/bom/CityPairDate.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacCityPair.hpp>
#include <latus/com/factory/FacCityPairDate.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacCityPair* FacCityPair::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacCityPair::~FacCityPair () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacCityPair& FacCityPair::instance () {

      if (_instance == NULL) {
        _instance = new FacCityPair();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    CityPair& FacCityPair::create (const CityPairKey_T& iKey) {
      CityPair* aCityPair_ptr = NULL;

      aCityPair_ptr = new CityPair (iKey);
      assert (aCityPair_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aCityPair_ptr);

      return *aCityPair_ptr;
    }

    // //////////////////////////////////////////////////////////////////////
    void FacCityPair::initLinkWithCityPairDate (CityPair& ioCityPair,
                                                CityPairDate& ioCityPairDate) {
      // Link the CityPair to the CityPairDate, and vice versa
      ioCityPairDate.setCityPair (&ioCityPair);
      
      // Link the CityPair to the CityPairDate
      const bool insertSucceeded = ioCityPair._cityPairDateList.
        insert (CityPairDateList_T::value_type (ioCityPairDate.getPrimaryKey(),
                                                &ioCityPairDate)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioCityPair.describeKey()
                         << " and " << ioCityPairDate.describeKey());
        assert (insertSucceeded == true);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void FacCityPair::createClassPath(CityPair& ioCityPair,
                                      const boost::gregorian::date& iDepDate,
                                      const std::string& iClassPathDescription,
                                      const double iDistributionMean,
                                      const double iDistributionStdDev) {

      // Check whether the CityPairDate exists
      CityPairDate* lCityPairDate_ptr = ioCityPair.getCityPairDate (iDepDate);

      // When not existing, create the CityPairDate object, and link it to
      // the CityPair (parent).
      if (lCityPairDate_ptr == NULL) {
        CityPairDate& lCityPairDate =
          FacCityPairDate::instance().create (iDepDate);
        lCityPairDate_ptr = &lCityPairDate;

        FacCityPair::initLinkWithCityPairDate (ioCityPair, lCityPairDate);
      }
      assert (lCityPairDate_ptr != NULL);
      
      // Forward the ClassPath object creation request to FacCityPairDate
      FacCityPairDate::createClassPath(*lCityPairDate_ptr,
                                       iClassPathDescription,
                                       iDistributionMean, iDistributionStdDev);

    }

  }
}
