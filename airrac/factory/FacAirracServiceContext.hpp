#ifndef __AIRRAC_FAC_FACAIRRACSERVICECONTEXT_HPP
#define __AIRRAC_FAC_FACAIRRACSERVICECONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// AirRAC
#include <airrac/factory/FacServiceAbstract.hpp>

namespace AIRRAC {

  /** Forward declarations. */
  class AIRRAC_ServiceContext;

  /** Factory for Bucket. */
  class FacAirracServiceContext : public FacServiceAbstract {
  public:

    /** Provide the unique instance.
        <br> The singleton is instantiated when first used
        @return FacAirracServiceContext& */
    static FacAirracServiceContext& instance();

    /** Destructor.
        <br> The Destruction put the _instance to NULL
        in order to be clean for the next
        FacAirracServiceContext::instance() */
    ~FacAirracServiceContext();

    /** Create a new AIRRAC_ServiceContext object.
        <br>This new object is added to the list of instantiated objects.
        @return AIRRAC_ServiceContext& The newly created object. */
    AIRRAC_ServiceContext& create ();

    
  protected:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacAirracServiceContext () {}

  private:
    /** The unique instance.*/
    static FacAirracServiceContext* _instance;
  };

}
#endif // __AIRRAC_FAC_FACAIRRACSERVICECONTEXT_HPP
