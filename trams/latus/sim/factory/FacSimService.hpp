#ifndef __LATUS_SIM_FAC_FACSIMSERVICE_HPP
#define __LATUS_SIM_FAC_FACSIMSERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS General
#include <latus/LatusTypes.hpp>
// LATUS Common
#include <latus/com/factory/FacServiceAbstract.hpp>

namespace LATUS {

  namespace SIM {

    /** Forward declarations. */
    class LATUS_SIM;
    class ModuleDescription;

    /** Factory for Bucket. */
    class FacSimService : public COM::FacServiceAbstract {
    public:

      /** Provide the unique instance.
          <br> The singleton is instantiated when first used
          @return FacServiceContext& */
      static FacSimService& instance();

      /** Destructor.
          <br> The Destruction put the _instance to NULL
          in order to be clean for the next FacServiceContext::instance() */
      virtual ~FacSimService();

      /** Create a new ServiceContext object.
          <br>This new object is added to the list of instantiated objects.
          @return ServiceContext& The newly created object. */
      LATUS_SIM& create (const std::string& iModuleName);

    
    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacSimService () {}

    private:
      /** The unique instance.*/
      static FacSimService* _instance;

    };

  }
}
#endif // __LATUS_SIM_FAC_FACSIMSERVICE_HPP
