#ifndef __LATUS_COM_FAC_FACCITYPAIR_HPP
#define __LATUS_COM_FAC_FACCITYPAIR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    struct CityPairKey_T;
    class CityPair;
    class CityPairDate;
    
    /** Factory for CityPair objects. */
    class FacCityPair : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacCityPair& */
      static FacCityPair& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacCityPair::instance() */
      virtual ~FacCityPair();

      /** Create a new CityPair object.
          <br>This new object is added to the list of instantiated objects.
          @return CityPair& The newly created object. */
      CityPair& create (const CityPairKey_T&);

      /** Initialise the link between a CityPair and a CityPairDate.
          @param CityPair&
          @param CityPairDate&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithCityPairDate (CityPair&, CityPairDate&);

    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacCityPair () {}

    private:
      /** The unique instance.*/
      static FacCityPair* _instance;
    };
  }
}
#endif // __LATUS_COM_FAC_FACCITYPAIR_HPP
