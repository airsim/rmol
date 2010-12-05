#ifndef __RMOL_FAC_FACRMOLSERVICECONTEXT_HPP
#define __RMOL_FAC_FACRMOLSERVICECONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
// RMOL
#include <rmol/RMOL_Types.hpp>
#include <rmol/factory/FacServiceAbstract.hpp>

namespace RMOL {

  /** Forward declarations. */
  class RMOL_ServiceContext;

  /** Factory for Bucket. */
  class FacRmolServiceContext : public FacServiceAbstract {
  public:

    /** Provide the unique instance.
        <br> The singleton is instantiated when first used
        @return FacServiceContext& */
    static FacRmolServiceContext& instance();

    /** Destructor.
        <br> The Destruction put the _instance to NULL
        in order to be clean for the next FacServiceContext::instance() */
    virtual ~FacRmolServiceContext();

    /** Create a new ServiceContext object.
        <br>This new object is added to the list of instantiated objects.
        @return ServiceContext& The newly created object. */
    RMOL_ServiceContext& create (const stdair::AirlineCode_T&);

    /** Create a new ServiceContext object.
        <br>This new object is added to the list of instantiated objects.
        @return ServiceContext& The newly created object. */
    RMOL_ServiceContext& create (const stdair::AirlineCode_T&,
                                 const ResourceCapacity_T);

    
  protected:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacRmolServiceContext () {}

  private:
    /** The unique instance.*/
    static FacRmolServiceContext* _instance;

  };
}
#endif // __RMOL_FAC_FACRMOLSERVICECONTEXT_HPP
