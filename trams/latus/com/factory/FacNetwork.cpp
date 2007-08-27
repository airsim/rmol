// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/Network.hpp>
#include <latus/com/bom/NetworkDate.hpp>
#include <latus/com/bom/NetworkDateList.hpp>
#include <latus/com/factory/FacSupervisor.hpp>
#include <latus/com/factory/FacNetwork.hpp>
#include <latus/com/factory/FacNetworkDate.hpp>
#include <latus/com/service/Logger.hpp>

namespace LATUS {

  namespace COM {

    FacNetwork* FacNetwork::_instance = NULL;

    // //////////////////////////////////////////////////////////////////////
    FacNetwork::~FacNetwork () {
      _instance = NULL;
    }

    // //////////////////////////////////////////////////////////////////////
    FacNetwork& FacNetwork::instance () {

      if (_instance == NULL) {
        _instance = new FacNetwork();
        assert (_instance != NULL);
      
        FacSupervisor::instance().registerBomFactory (_instance);
      }
      return *_instance;
    }

    // //////////////////////////////////////////////////////////////////////
    Network& FacNetwork::create () {
      Network* aNetwork_ptr = NULL;

      aNetwork_ptr = new Network ();
      assert (aNetwork_ptr != NULL);

      // The new object is added to the Bom pool
      _pool.push_back (aNetwork_ptr);

      return *aNetwork_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    void FacNetwork::
    initLinkWithNetworkDate (Network& ioNetwork, NetworkDate& ioNetworkDate) {
      // Link the Network to the NetworkDate, and vice versa
      ioNetworkDate.setNetwork (&ioNetwork);
      
      // Link the Network to the NetworkDate
      const bool insertSucceeded = ioNetwork._networkDateList.
        insert (NetworkDateList_T::value_type (ioNetworkDate.describeShortKey(),
                                               &ioNetworkDate)).second;
      if (insertSucceeded == false) {
        LATUS_LOG_ERROR ("Insertion failed for " << ioNetwork.describeKey()
                         << " and " << ioNetworkDate.describeShortKey());
        assert (insertSucceeded == true);
      }
    }
  
    // //////////////////////////////////////////////////////////////////////
    void FacNetwork::createPathList (Network& ioNetwork) {
      const NetworkDateList_T& lNetworkDateList =
        ioNetwork.getNetworkDateList();
      for (NetworkDateList_T::const_iterator itNetworkDate =
             lNetworkDateList.begin();
           itNetworkDate != lNetworkDateList.end(); itNetworkDate++) {
        NetworkDate* lNetworkDate_ptr = itNetworkDate->second;
        assert (lNetworkDate_ptr != NULL);
        
        FacNetworkDate::createPathList (*lNetworkDate_ptr);
      }
    }
      
  }
}
