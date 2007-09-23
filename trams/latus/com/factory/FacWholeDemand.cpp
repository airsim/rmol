// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/WholeDemand.hpp>
#include <latus/com/bom/CityPair.hpp>
#include <latus/com/bom/CityPairList.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacWholeDemand.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacWholeDemand* FacWholeDemand::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacWholeDemand::~FacWholeDemand () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacWholeDemand& FacWholeDemand::instance () {

      if (_instance == NULL) {
        _instance = new FacWholeDemand();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    WholeDemand& FacWholeDemand::
    create (const boost::gregorian::date& iUpdateDate) {
      WholeDemand* aWholeDemand_ptr = NULL;

      aWholeDemand_ptr = new WholeDemand (iUpdateDate);
      assert (aWholeDemand_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aWholeDemand_ptr);

      return *aWholeDemand_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void FacWholeDemand::
    initLinkWithCityPair (WholeDemand& ioWholeDemand,
                           CityPair& ioCityPair) {
      // Link the WholeDemand to the CityPair, and vice versa
      ioCityPair.setWholeDemand (&ioWholeDemand);
      
      // Link the WholeDemand to the CityPair
      const bool insertSucceeded = ioWholeDemand._cityPairList.
        insert (CityPairList_T::value_type (ioCityPair.describeShortKey(),
                                            &ioCityPair)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for "
                         << ioWholeDemand.describeKey()
                         << " and " << ioCityPair.describeShortKey());
        assert (insertSucceeded == true);
      }
    }

  }
}
