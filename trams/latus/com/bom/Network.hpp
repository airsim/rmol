#ifndef __LATUS_COM_BOM_NETWORK_HPP
#define __LATUS_COM_BOM_NETWORK_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/NetworkDateList.hpp>
#include <latus/com/bom/OutboundPathList.hpp>

namespace LATUS {

  // Forward declarations
  namespace TSP {
    class NetworkGenerator;
  }
  
  namespace COM {

    /** Class wrapping the airline networks for all the dates. */
    class Network : public BomAbstract {
      friend class FacNetwork;
      friend class TSP::NetworkGenerator;
    public:
      // /////////// Getters //////////////
      /** Retrieve, if existing, the NetworkDate corresponding to the
          given reference date (NetworkDate key).
          <br>If not existing, return the NULL pointer. */
      NetworkDate* getNetworkDate (const DateTime_T&) const;
      

      // ///////// Setters //////////

      
      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Display the full BookingDay context. */
      void display() const;

      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      Network (); 

      /** Default constructors. */
      Network (const Network&);
      
      /** Destructor. */
      virtual ~Network();

      /** Get the list of (children) Network objects. */
      const NetworkDateList_T& getNetworkDateList () const {
        return _networkDateList;
      }

      /** Retrieve, if existing, the NetworkDate corresponding to the
          given NetworkDate key (reference date).
          <br>If not existing, return the NULL pointer.
          <br>Note that the string must be formed thanks to the
          NetworkDateKey::describeShort() method, as that latter is used when
          inserting the NetworkDate within the Network dedicated list. */
      NetworkDate*
      getNetworkDateInternal (const std::string& iNetworkDateKey) const;
      

    private:
      // Attributes
      /** Children: list of NetworkDate objects. */
      NetworkDateList_T _networkDateList;

      /** Helper structure: list, for each (airport, date) combination, of
          Outbound-Single-Pathes (an Outbound-Single-Path is an Ountbound-Path
          encompassing a single Segment-Date). That list is filled when the
          Segment-Date objects are built, i.e., during the parsing of
          the schedule input file. Hence, for each airport-date
          combination, the full list of possible outbound-pathes is
          stored and directly accessible. */
      OutboundPathList_T _outboundSinglePathList;
    };

  }
}
#endif // __LATUS_COM_BOM_NETWORK_HPP
