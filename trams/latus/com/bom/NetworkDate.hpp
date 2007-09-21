#ifndef __LATUS_COM_BOM_NETWORKDATE_HPP
#define __LATUS_COM_BOM_NETWORKDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/NetworkDateKey.hpp>
#include <latus/com/bom/AirportDateList.hpp>

namespace LATUS {

  // Forward declarations
  namespace TSP {
    class NetworkGenerator;
  }
  
  namespace COM {

    // Forward declarations
    class Network;

    /** Class holding the graph of travel solutions for a givenr
        reference date. */
    class NetworkDate : public BomAbstract {
      friend class FacNetworkDate;
      friend class TSP::NetworkGenerator;
    public:
      // /////////// Getters //////////////
      /** Get the parent class. */
      Network* getParent() const {
        return getNetwork();
      }

      /** Get the Network (parent class). */
      Network* getNetwork() const {
        return _network;
      }

      /** Get the primary key. */
      const NetworkDateKey_T& getPrimaryKey() const {
        return getNetworkDateKey();
      }

      /** Get the network-date key. */
      const NetworkDateKey_T& getNetworkDateKey() const {
        return _key;
      }

      /** Retrieve, if existing, the AirportDate corresponding to the
          given board point (AirportDate key).
          <br>If not existing, return the NULL pointer. */
      AirportDate* getAirportDate (const AirportCode_T&) const;

      /** Get the NetworkDate (from the Network parent class) corresponding
          to the given key (reference date).
          <br>Note that that method may get a NetworkDate for a different
          date than the current object.
          <br>Return the NULL pointer if not existing. */
      NetworkDate* getNetworkDate (const DateTime_T&) const;

      /** Get the AirportDate (from the Network parent class) corresponding
          to the given key (reference date + airport code).
          <br>Note that that method may get an AirportDate from a different
          NetworkDate than the current object.
          <br>Return the NULL pointer if not existing. */
      AirportDate* getAirportDate (const AirportCode_T&,
                                   const DateTime_T&) const;


      // ///////// Setters //////////
      /** Set the Network (parent class). */
      void setNetwork (Network* ioNetworkPtr) {
        _network = ioNetworkPtr;
      }


      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Get a string describing the short key. */
      const std::string describeShortKey() const;

      /** Display the full NetworkDate context. */
      void display() const;

      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      NetworkDate (const NetworkDateKey_T&); 

      /** Default constructors. */
      NetworkDate ();
      NetworkDate (const NetworkDate&);
      
      /** Destructor. */
      virtual ~NetworkDate();


    private:
      /** Get the list of (children) AirportDate objects. */
      const AirportDateList_T& getAirportDateList () const {
        return _airportDateList;
      }

      /** Get the ordered list of (children) AirportDate objects. */
      const AirportDateOrderedList_T& getAirportDateOrderedList () const {
        return _airportDateOrderedList;
      }

      /** Retrieve, if existing, the AirportDate corresponding to the
          given AirportDate key (NetworkDateKey + board point).
          <br>If not existing, return the NULL pointer.
          <br>Note that the string must be formed thanks to the
          AirportDateKey::describeShort() method, as that latter is used when
          inserting the AirportDate within the NetworkDate dedicated list. */
      AirportDate* getAirportDateInternal (const std::string& iAirportDateKey) const;
      

    private:
      // Parent
      /** Parent class: Network. */
      Network* _network;
      
      // Primary Key
      /** Network-Date Key is composed of the reference date. */
      NetworkDateKey_T _key;

      // Children
      /** Children: lists of AirportDate objects. */
      AirportDateList_T _airportDateList;
      AirportDateOrderedList_T _airportDateOrderedList;
    };

  }
}
#endif // __LATUS_COM_BOM_NETWORKDATE_HPP
