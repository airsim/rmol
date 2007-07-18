// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/basic/ModuleDescription.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
// LATUS Simulator Module
#include <latus/sim/service/LATUS_SIM.hpp>
#include <latus/sim/factory/FacSimService.hpp>

namespace LATUS {

  namespace SIM {

    FacSimService* FacSimService::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacSimService::~FacSimService () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacSimService& FacSimService::instance () {

      if (_instance == NULL) {
        _instance = new FacSimService();
        assert (_instance != NULL);
      
        COM::FacSupervisor::instance().registerServiceFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    LATUS_SIM& FacSimService::create (const std::string& iModuleName) {
      LATUS_SIM* aLATUS_SIM_ptr = NULL;

      aLATUS_SIM_ptr = new LATUS_SIM (iModuleName);
      assert (aLATUS_SIM_ptr != NULL);

      // The new object is added to the Service pool
      _pool.push_back (aLATUS_SIM_ptr);

      return *aLATUS_SIM_ptr;
    }

  }
}
