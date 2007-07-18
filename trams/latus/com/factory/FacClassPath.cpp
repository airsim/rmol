// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/ClassPath.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacClassPath.hpp>

namespace LATUS {
  
  namespace COM {

    FacClassPath* FacClassPath::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacClassPath::~FacClassPath () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacClassPath& FacClassPath::instance () {

      if (_instance == NULL) {
        _instance = new FacClassPath();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    ClassPath& FacClassPath::
    create (const std::string& iDescription,
            const DistributionDetails_T& iDistributionDetails) {
      ClassPath* aClassPath_ptr = NULL;

      aClassPath_ptr = new ClassPath (iDescription, iDistributionDetails);
      assert (aClassPath_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aClassPath_ptr);

      return *aClassPath_ptr;
    }

  }
  
}
