#ifndef __AIRRAC_FAC_FACAIRRACSERVICECONTEXT_HPP
#define __AIRRAC_FAC_FACAIRRACSERVICECONTEXT_HPP
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/service/FacServiceAbstract.hpp>

namespace AIRRAC {

  /// Forward declarations
  class AIRRAC_ServiceContext;


  /**
   * @brief Factory for the service context.
   */
  class FacAirracServiceContext : public stdair::FacServiceAbstract {
  public:

    /**
     * Provide the unique instance.
     *
     * The singleton is instantiated when first used.
     * @return FacServiceContext&
     */
    static FacAirracServiceContext& instance();

    /**
     * Destructor.
     *
     * The Destruction put the _instance to NULL in order to be clean
     * for the next FacSimfqtServiceContext::instance().
     */
    ~FacAirracServiceContext();

    /**
     * Create a new ServiceContext object.
     *
     * This new object is added to the list of instantiated objects.
     *
     * @return ServiceContext& The newly created object.
     */
    AIRRAC_ServiceContext& create();
    

  protected:
    /**
     * Default Constructor.
     *
     * This constructor is protected in order to ensure the singleton pattern.
     */
    FacAirracServiceContext() {}


  private:
    /**
     * The unique instance.
     */
    static FacAirracServiceContext* _instance;
  };

}
#endif // __AIRRAC_FAC_FACAIRRACSERVICECONTEXT_HPP
