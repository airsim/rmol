#ifndef __AIRRAC_FAC_FACSERVICEABSTRACT_HPP
#define __AIRRAC_FAC_FACSERVICEABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>

namespace AIRRAC {

  // Forward declarations
  class ServiceAbstract;

  /** Base class for the (Service) Factory layer. */
  class FacServiceAbstract {
  public:
    
    /** Define the list (pool) of Service objects. */
    typedef std::vector<ServiceAbstract*> ServicePool_T;
    
    /** Destructor. */
    virtual ~FacServiceAbstract();
    
    /** Destroyed all the object instantiated by this factory. */
    void clean();
    
  protected:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is abstract. */
    FacServiceAbstract() {}
    
    /** List of instantiated Business Objects*/
    ServicePool_T _pool;
  };
    
}
#endif // __AIRRAC_FAC_FACSERVICEABSTRACT_HPP
