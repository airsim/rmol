#ifndef __LATUS_COM_FAC_FACNETWORKDATE_HPP
#define __LATUS_COM_FAC_FACNETWORKDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    struct NetworkDateKey_T;
    class NetworkDate;
    class AirportDate;
    
    /** Factory for NetworkDate objects. */
    class FacNetworkDate : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacNetworkDate& */
      static FacNetworkDate& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacNetworkDate::instance() */
      virtual ~FacNetworkDate();

      /** Create a new NetworkDate object.
          <br>This new object is added to the list of instantiated objects.
          @return NetworkDate& The newly created object. */
      NetworkDate& create (const NetworkDateKey_T&);

      /** Initialise the link between a NetworkDate and a AirportDate.
          @param NetworkDate&
          @param AirportDate&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithAirportDate (NetworkDate&, AirportDate&);

      /** Create the routing between the airports and segments for the given
          NetworkDate object. */
      static void createPathList (NetworkDate& ioNetworkDate);


    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacNetworkDate () {}

    private:
      /** The unique instance.*/
      static FacNetworkDate* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACNETWORKDATE_HPP
