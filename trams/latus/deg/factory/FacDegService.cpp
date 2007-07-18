// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/basic/ModuleDescription.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
// LATUS Simulator Module
#include <latus/deg/service/LATUS_DEG.hpp>
#include <latus/deg/factory/FacDegService.hpp>

namespace LATUS {

  namespace DEG {

    FacDegService* FacDegService::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacDegService::~FacDegService () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacDegService& FacDegService::instance () {

      if (_instance == NULL) {
        _instance = new FacDegService();
        assert (_instance != NULL);
      
        COM::FacSupervisor::instance().registerServiceFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    LATUS_DEG& FacDegService::create (const std::string& iModuleName) {
      LATUS_DEG* aLATUS_DEG_ptr = NULL;

      aLATUS_DEG_ptr = new LATUS_DEG (iModuleName);
      assert (aLATUS_DEG_ptr != NULL);

      // The new object is added to the Service pool
      _pool.push_back (aLATUS_DEG_ptr);

      return *aLATUS_DEG_ptr;
    }

  }
}
