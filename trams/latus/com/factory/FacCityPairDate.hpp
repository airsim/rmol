#ifndef __LATUS_COM_FAC_FACCITYPAIRDATE_HPP
#define __LATUS_COM_FAC_FACCITYPAIRDATE_HPP

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
    class CityPairDate;
    class WTP;
    
    /** Factory for CityPairDate objects. */
    class FacCityPairDate : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacCityPairDate& */
      static FacCityPairDate& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacCityPairDate::instance() */
      virtual ~FacCityPairDate();

      /** Create a new CityPairDate object.
          <br>This new object is added to the list of instantiated objects.
          @return CityPairDate& The newly created object. */
      CityPairDate& create (const DateTime_T& iDepDate);

      /** Initialise the link between a CityPairDate and a WTP.
          @param CityPairDate&
          @param WTP&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithWTP (CityPairDate&, WTP&);

    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacCityPairDate () {}

    private:
      /** The unique instance.*/
      static FacCityPairDate* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACCITYPAIRDATE_HPP
