// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/WTP.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacWTP.hpp>

namespace LATUS {

  namespace COM {

    FacWTP* FacWTP::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacWTP::~FacWTP () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacWTP& FacWTP::instance () {

      if (_instance == NULL) {
        _instance = new FacWTP();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    WTP& FacWTP::
    create (const PriceValue_T& iWTPValue, const PriceCurrency_T& iWTPCurrency,
            const DistributionDetails_T& iDistributionDetails) {
      WTP* aWTP_ptr = NULL;
      
      aWTP_ptr = new WTP (iWTPValue, iWTPCurrency, iDistributionDetails);
      assert (aWTP_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aWTP_ptr);

      return *aWTP_ptr;
    }

  }
}
