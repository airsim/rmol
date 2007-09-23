#ifndef __LATUS_COM_FAC_FACWHOLEDEMAND_HPP
#define __LATUS_COM_FAC_FACWHOLEDEMAND_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class WholeDemand;
    class CityPair;
    
    /** Factory for WholeDemand objects. */
    class FacWholeDemand : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacWholeDemand& */
      static FacWholeDemand& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacWholeDemand::instance() */
      virtual ~FacWholeDemand();

      /** Create a new WholeDemand object.
          <br>This new object is added to the list of instantiated objects.
          @param const boost::gregorian::date& Creation/update date.
          @return WholeDemand& The newly created object. */
      WholeDemand& create (const DateTime_T& iUpdateDate);

      /** Initialise the link between a WholeDemand and a Schedule.
          @param WholeDemand&
          @param CityPair&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithCityPair (WholeDemand&, CityPair&);


    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacWholeDemand () {}

    private:
      /** The unique instance.*/
      static FacWholeDemand* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACWHOLEDEMAND_HPP
