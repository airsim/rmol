#ifndef __RMOL_FAC_FACSERVICECONTEXT_HPP
#define __RMOL_FAC_FACSERVICECONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RmolTypes.hpp>
#include <rmol/factory/FacServiceAbstract.hpp>

namespace RMOL {

  /** Forward declarations. */
  class ServiceContext;

  /** Factory for Bucket. */
  class FacServiceContext : public FacServiceAbstract {
  public:

    /** Provide the unique instance.
        <br> The singleton is instantiated when first used
        @return FacServiceContext& */
    static FacServiceContext& instance();

    /** Destructor.
        <br> The Destruction put the _instance to NULL
        in order to be clean for the next FacServiceContext::instance() */
    virtual ~FacServiceContext();

    /** Create a new ServiceContext object.
        <br>This new object is added to the list of instantiated objects.
        @return ServiceContext& The newly created object. */
    ServiceContext& create ();

    /** Create a new ServiceContext object.
        <br>This new object is added to the list of instantiated objects.
        @return ServiceContext& The newly created object. */
    ServiceContext& create (const ResourceCapacity_T iResourceCapacity);

    
  protected:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacServiceContext () {}

  private:
    /** The unique instance.*/
    static FacServiceContext* _instance;

  };
}
#endif // __RMOL_FAC_FACSERVICECONTEXT_HPP
