#ifndef __LATUS_COM_FAC_FACCLASSPATH_HPP
#define __LATUS_COM_FAC_FACCLASSPATH_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/DistributionDetails.hpp>
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {
  
  namespace COM {

    /** Forward declarations. */
    class ClassPath;
    
    /** Factory for ClassPath objects. */
    class FacClassPath : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacClassPath& */
      static FacClassPath& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacClassPath::instance() */
      virtual ~FacClassPath();

      /** Create a new ClassPath object.
          <br>This new object is added to the list of instantiated objects.
          @return ClassPath& The newly created object. */
      ClassPath& create (const std::string& iDescription,
                         const DistributionDetails_T&);

    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacClassPath () {}

    private:
      /** The unique instance.*/
      static FacClassPath* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACCLASSPATH_HPP
