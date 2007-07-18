#ifndef __LATUS_COM_FAC_FACSERVICECONTEXT_HPP
#define __LATUS_COM_FAC_FACSERVICECONTEXT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS General
#include <latus/LatusTypes.hpp>
// LATUS Common
#include <latus/com/factory/FacServiceAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    class ServiceContext;
    class ModuleDescription;

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
      ServiceContext& create (const ModuleDescription&);

    
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
}
#endif // __LATUS_COM_FAC_FACSERVICECONTEXT_HPP
