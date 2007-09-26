#ifndef __LATUS_COM_BOM_AIRPORTDATE_HPP
#define __LATUS_COM_BOM_AIRPORTDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/AirportDateKey.hpp>
#include <latus/com/bom/OutboundPathList.hpp>
#include <latus/com/bom/SegmentDateList.hpp>

namespace LATUS {

  // Forward declarations
  namespace TSP {
    class NetworkGenerator;
  }
  
  namespace COM {

    // Forward declarations
    class NetworkDate;

    /** Class representing a graph node of a Network for the
        TSP-related (Travel Solution Provider) business. */
    class AirportDate : public BomAbstract {
      friend class FacAirportDate;
      friend class TSP::NetworkGenerator;
    public:
      // /////////// Getters //////////////
      /** Get the parent class. */
      NetworkDate* getParent() const {
        return getNetworkDate();
      }

      /** Get the NetworkDate (parent class). */
      NetworkDate* getNetworkDate() const {
        return _networkDate;
      }

      /** Get the primary key. */
      const AirportDateKey_T& getPrimaryKey() const {
        return getAirportDateKey();
      }

      /** Get the flight-date key. */
      const AirportDateKey_T& getAirportDateKey() const {
        return _key;
      }

      /** Get the (origin) airport (part of the primary key). */
      const AirportCode_T& getOrigin() const {
        return _key.origin;
      }

      /** Get the AirportDate (from the Network parent class) corresponding
          to the given key (reference date + airport code).
          <br>Return the NULL pointer if not existing. */
      AirportDate* getAirportDate (const AirportCode_T&,
                                   const DateTime_T&) const;

      /** Retrieve, if existing, an OutboundPath corresponding to the
          given origin, elapsed time, number of segments and number of
          airlines (OutboundPath key).
          <br>Note that several OutboundPath objects may correspond to the
          given characteristics. Only the first one is returned here.
          <br>If not existing, return the NULL pointer. */
      OutboundPath* getOutboundPath (const AirportCode_T&, const Duration_T&,
                                     const SegmentNumber_T&,
                                     const AirlineNumber_T&) const;

      /** Get the list of Outbound-Path objects (if any) corresponding to
          the given destination. */
      void getOutboundPathList (const AirportCode_T& iDestination,
                                OutboundPathLightList_T&) const;
      

      // ///////// Setters //////////
      /** Set the NetworkDate (parent class). */
      void setNetworkDate (NetworkDate* ioNetworkDatePtr) {
        _networkDate = ioNetworkDatePtr;
      }


      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Get a string describing the short key. */
      const std::string describeShortKey() const;

       /** Retrieve, if existing, the OutboundPath corresponding to the
          given OutboundPath key (AirportDateKey + destination + elapsed time
          + number of segments + number of airlines).
          <br>Note that several OutboundPath objects may correspond to the
          given characteristics. Only the first one is returned here.
          <br>If not existing, return the NULL pointer.
          <br>Note that the string must be formed thanks to the
          OutboundPathKey::describeShort() method, as that latter is used when
          inserting the OutboundPath within the FlightDate dedicated list. */
      OutboundPath*
      getOutboundPath (const std::string& iOutboundPathKey) const;

      /** Display the full AirportDate context. */
      void display() const;

      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      AirportDate (const AirportDateKey_T&); 

      /** Default constructors. */
      AirportDate ();
      AirportDate (const AirportDate&);
      
      /** Destructor. */
      virtual ~AirportDate();


    private:
      /** Get the list of (children) Outbound-Path objects. */
      const OutboundPathList_T& getOutboundPathList () const {
        return _outboundPathList;
      }

      /** Get the list of list of (children) Outbound-Path objects. */
      const OutboundPathListList_T& getOutboundPathListList () const {
        return _outboundPathListList;
      }

      /** Retrieve, if existing, the OutboundPath corresponding to the
          given OutboundPath key (AirportDateKey + destination + elapsed time
          + number of segments + number of airlines).
          <br>Note that several OutboundPath objects may correspond to the
          given characteristics. Only the first one is returned here.
          <br>If not existing, return the NULL pointer.
          <br>Note that the string must be formed thanks to the
          OutboundPathKey::describeShort() method, as that latter is used when
          inserting the OutboundPath within the FlightDate dedicated list. */
      OutboundPath*
      getOutboundPathInternal (const std::string& iOutboundPathKey) const;
      

    private:
      // Parent
      /** Parent class: NetworkDate. */
      NetworkDate* _networkDate;
      
      // Primary Key
      /** Airport-Date Key is composed of the airport code and the
          reference date. */
      AirportDateKey_T _key;


      // Children: There are two types of lists:
      // one with fixed-length pathes (in terms of the number of
      // SegmentDates), and one with all the possible pathes
      // (encompassing the fixed-length pathes all-together)
            
      /** Children: list of all-length Outbound-Path objects.
          <br>That list (indeed, a STL map) allows to keep track of every
          OutboundPath stored in the AirportDate object, and thus avoids
          duplicated OutboundPath objects within the other list:
          OutboundPathLightList_T (which is a STL list, not a STL map)
          embedded within the OutboundPathListList. */
      OutboundPathList_T _outboundPathList;

      /** Children: random-access list of list of Outbound-Path objects.
          <br>The following vector contains, for each i, the list of
          i-fixed-length pathes. So, the first item, for example, is the list
          of pathes made of single SegmentDates. */
      OutboundPathListList_T _outboundPathListList;
    };

  }
}
#endif // __LATUS_COM_BOM_AIRPORTDATE_HPP
