#ifndef __LATUS_DEG_FAC_FACDEGSERVICE_HPP
#define __LATUS_DEG_FAC_FACDEGSERVICE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS General
#include <latus/LatusTypes.hpp>
// LATUS Common
#include <latus/com/factory/FacServiceAbstract.hpp>

namespace LATUS {

  namespace DEG {

    /** Forward declarations. */
    class LATUS_DEG;
    class ModuleDescription;

    /** Factory for Bucket. */
    class FacDegService : public COM::FacServiceAbstract {
    public:

      /** Provide the unique instance.
          <br> The singleton is instantiated when first used
          @return FacServiceContext& */
      static FacDegService& instance();

      /** Destructor.
          <br> The Destruction put the _instance to NULL
          in order to be clean for the next FacServiceContext::instance() */
      virtual ~FacDegService();

      /** Create a new ServiceContext object.
          <br>This new object is added to the list of instantiated objects.
          @return ServiceContext& The newly created object. */
      LATUS_DEG& create (const std::string& iModuleName);

    
    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacDegService () {}

    private:
      /** The unique instance.*/
      static FacDegService* _instance;

    };

  }
}
#endif // __LATUS_DEG_FAC_FACDEGSERVICE_HPP
