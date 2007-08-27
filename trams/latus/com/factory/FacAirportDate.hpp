#ifndef __LATUS_COM_FAC_FACAIRPORTDATE_HPP
#define __LATUS_COM_FAC_FACAIRPORTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    struct AirportDateKey_T;
    class AirportDate;
    class OutboundPath;
    
    /** Factory for AirportDate objects. */
    class FacAirportDate : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacAirportDate& */
      static FacAirportDate& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacAirportDate::instance() */
      virtual ~FacAirportDate();

      /** Create a new AirportDate object.
          <br>This new object is added to the list of instantiated objects.
          @return AirportDate& The newly created object. */
      AirportDate& create (const AirportDateKey_T&);

      /** Initialise the link between a AirportDate and a OutboundPath.
          @param AirportDate&
          @param OutboundPath&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithOutboundPath (AirportDate&, OutboundPath&);

      /** Create the routing between the legs and segments for the given
          AirportDate object. */
      static void createPathList (AirportDate& ioAirportDate);


    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacAirportDate () {}

    private:
      /** The unique instance.*/
      static FacAirportDate* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACAIRPORTDATE_HPP
