// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/CityPairDate.hpp>
#include <latus/com/bom/DistributionDetails.hpp>
#include <latus/com/bom/WTP.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacCityPairDate.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {
    
    FacCityPairDate* FacCityPairDate::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacCityPairDate::~FacCityPairDate () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacCityPairDate& FacCityPairDate::instance () {

      if (_instance == NULL) {
        _instance = new FacCityPairDate();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    CityPairDate& FacCityPairDate::create (const DateTime_T& iDepDate) {
      CityPairDate* aCityPairDate_ptr = NULL;

      aCityPairDate_ptr = new CityPairDate (iDepDate);
      assert (aCityPairDate_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aCityPairDate_ptr);

      return *aCityPairDate_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void FacCityPairDate::initLinkWithWTP (CityPairDate& ioCityPairDate,
                                           WTP& ioWTP) {
      // Link the CityPairDate to the WTP, and vice versa
      ioWTP.setCityPairDate (&ioCityPairDate);

      // Link the CityPairDate to the WTP
      const bool insertSucceeded = ioCityPairDate._wtpList.
        insert (WTPList_T::value_type (ioWTP.getPrimaryKey(), &ioWTP)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for "
                         << ioCityPairDate.describeKey()
                         << " and " << ioWTP.describeKey());
        assert (insertSucceeded == true);
      }
    }

  }
}
