// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS COM
#include <latus/com/bom/Network.hpp>
#include <latus/com/bom/NetworkDate.hpp>

namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    Network::Network () {
    }

    // //////////////////////////////////////////////////////////////////////
    Network::~Network() {
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string Network::describeKey() const {
      std::ostringstream ostr;
      ostr << "No key";
      return ostr.str();
    }
    
    // //////////////////////////////////////////////////////////////////////
    void Network::display() const {

      // Store current formatting flags of std::cout
      std::ios::fmtflags oldFlags = std::cout.flags();

      std::cout << "Network: " << std::endl;
      
      int j = 1;
      for (NetworkDateList_T::const_iterator itNetworkDate =
             _networkDateList.begin();
           itNetworkDate != _networkDateList.end(); ++itNetworkDate, ++j) {
        const NetworkDate* lNetworkDate_ptr = itNetworkDate->second;
        assert (lNetworkDate_ptr != NULL);

        lNetworkDate_ptr->display ();
      }
      
      // Reset formatting flags of std::cout
      std::cout.flags (oldFlags);
    }
    
    // //////////////////////////////////////////////////////////////////////
    NetworkDate* Network::
    getNetworkDateInternal (const std::string& iNetworkDateKey) const {
      NetworkDate* resultNetworkDate_ptr = NULL;
      
      NetworkDateList_T::const_iterator itNetworkDate =
        _networkDateList.find (iNetworkDateKey);

      if (itNetworkDate != _networkDateList.end()) {
        resultNetworkDate_ptr = itNetworkDate->second;
      }

      return resultNetworkDate_ptr;
    }
    
    // //////////////////////////////////////////////////////////////////////
    NetworkDate* Network::
    getNetworkDate (const DateTime_T& iReferenceDate) const {
      const NetworkDateKey_T lNetworkDateKey (iReferenceDate);
      const std::string& lNetworkDateKeyString =
        lNetworkDateKey.describeShort();
      return getNetworkDateInternal (lNetworkDateKeyString);
    }
    
  }
}
