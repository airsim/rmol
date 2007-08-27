#ifndef __LATUS_COM_FAC_FACNETWORK_HPP
#define __LATUS_COM_FAC_FACNETWORK_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class Network;
    
    /** Factory for Network objects. */
    class FacNetwork : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacNetwork& */
      static FacNetwork& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacNetwork::instance() */
      virtual ~FacNetwork();

      /** Create a new Network object.
          <br>This new object is added to the list of instantiated objects.
          @param const boost::gregorian::date& Creation/update date.
          @return Network& The newly created object. */
      Network& create ();

      /** Initialise the link between a Network and a Schedule.
          @param Network&
          @param Inventory&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithNetworkDate (Network&, NetworkDate&);

      /** Create the routing between the legs and segments for all the
          Inventories of the given Network object. */
      static void createPathList (Network&);
      

    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacNetwork () {}

    private:
      /** The unique instance.*/
      static FacNetwork* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACNETWORK_HPP
