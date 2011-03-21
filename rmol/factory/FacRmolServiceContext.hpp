#ifndef __RMOL_FAC_FACRMOLSERVICECONTEXT_HPP
#define __RMOL_FAC_FACRMOLSERVICECONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/service/FacServiceAbstract.hpp>

namespace RMOL {

  /// Forward declarations
  class RMOL_ServiceContext;


  /**
   * @brief Factory for the service context.
   */
  class FacRmolServiceContext : public stdair::FacServiceAbstract {
  public:

    /**
     * Provide the unique instance.
     *
     * The singleton is instantiated when first used.
     * @return FacServiceContext&
     */
    static FacRmolServiceContext& instance();

    /**
     * Destructor.
     *
     * The Destruction put the _instance to NULL in order to be clean
     * for the next FacSimfqtServiceContext::instance().
     */
    ~FacRmolServiceContext();

    /**
     * Create a new ServiceContext object.
     *
     * This new object is added to the list of instantiated objects.
     *
     * @return ServiceContext& The newly created object.
     */
    RMOL_ServiceContext& create();
    

  protected:
    /**
     * Default Constructor.
     *
     * This constructor is protected in order to ensure the singleton pattern.
     */
    FacRmolServiceContext() {}


  private:
    /**
     * The unique instance.
     */
    static FacRmolServiceContext* _instance;
  };

}
#endif // __RMOL_FAC_FACRMOLSERVICECONTEXT_HPP
