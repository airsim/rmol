// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/CityPairDate.hpp>
#include <latus/com/bom/DistributionDetails.hpp>
#include <latus/com/bom/ClassPath.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacCityPairDate.hpp>
#include <latus/com/factory/FacClassPath.hpp>
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
    CityPairDate& FacCityPairDate::
    create (const boost::gregorian::date& iDepDate) {
      CityPairDate* aCityPairDate_ptr = NULL;

      aCityPairDate_ptr = new CityPairDate (iDepDate);
      assert (aCityPairDate_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aCityPairDate_ptr);

      return *aCityPairDate_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void FacCityPairDate::initLinkWithClassPath (CityPairDate& ioCityPairDate,
                                                 ClassPath& ioClassPath) {
      // Link the CityPairDate to the ClassPath, and vice versa
      ioClassPath.setCityPairDate (&ioCityPairDate);

      // Link the CityPairDate to the ClassPath
      const bool insertSucceeded = ioCityPairDate._classPathList.
        insert (ClassPathList_T::value_type (ioClassPath.getPrimaryKey(),
                                             &ioClassPath)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for "
                         << ioCityPairDate.describeKey()
                         << " and " << ioClassPath.describeKey());
        assert (insertSucceeded == true);
      }
    }

    // //////////////////////////////////////////////////////////////////////
    void FacCityPairDate::
    createClassPath (CityPairDate& ioCityPairDate,
                     const std::string& iCabinCode,
                     const std::string& iClassCode,
                     const double iDistributionMean,
                     const double iDistributionStdDev) {

      std::ostringstream ostr;
      ostr << iCabinCode << "-" << iClassCode;

      ClassPath* lClassPath_ptr =
        ioCityPairDate.getClassPath (ostr.str());

      if (lClassPath_ptr == NULL) {
        ClassPath& lClassPath = FacClassPath::instance().
          create (iCabinCode, iClassCode,
                  DistributionDetails_T (iDistributionMean,
                                         iDistributionStdDev));
        std::cout << iCabinCode << "-" << iClassCode << std::endl;
        lClassPath_ptr = &lClassPath;
        FacCityPairDate::initLinkWithClassPath (ioCityPairDate, lClassPath);
      }
      assert (lClassPath_ptr != NULL);
    }

  }
  
}
