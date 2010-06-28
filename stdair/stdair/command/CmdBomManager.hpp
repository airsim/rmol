#ifndef __STDAIR_CMD_CMDBOMMANAGER_HPP
#define __STDAIR_CMD_CMDBOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/STDAIR_Types.hpp>
#include <stdair/command/CmdAbstract.hpp>

namespace stdair {

  // Forward declarations
  class BomRoot;
  class Inventory;
  class FlightDate;
  class SegmentDate;
  class SegmentCabin;
  class BookingClass;
  class LegDate;
  class LegCabin;
  class FlightPeriod;
  class SegmentPeriod;
  class ReachableUniverse;
  class OriginDestinationSet;
  class SegmentPathPeriod;
  class Network;
  class NetworkDate;
  class AirportDate;
  class OutboundPath;
  class YieldStore;
  class DemandStream;
  struct FlightDateKey_T;
  struct SegmentDateKey_T;
  struct FlightPeriodKey_T;
  struct SegmentPeriodKey_T;
  struct SegmentPathPeriodKey_T;
  struct NetworkKey_T;
  struct OutboundPathKey_T;

  /** Class wrapping utility functions for handling the BOM tree objects. */
  class CmdBomManager : public CmdAbstract {
  public:
    
    /** Create the airline-specific AirlineFeature object to the BomRoot
        and its corresponding Inventory.
        @param BomRoot& Root of the BOM tree.
        @param const AirlineCode_T& Airline code for the inventory to be
               created . */
    static void createAirlineFeature (const BomRoot&, const AirlineCode_T&);
      
    /** Create the YieldStore corresponding to the given airline code
        (YieldStore key). */
    static YieldStore& createYieldStore (const BomRoot&, const AirlineCode_T&);

    /** Create the inventory corresponding to the given airline code
        (Inventory key), link it to the BomRoot object and to the
        associated AirlineFeature object. */
    static Inventory& createInventory (const BomRoot&, const AirlineCode_T&);

    /** Create the flight-date corresponding to the given key. */
    static FlightDate& createFlightDate (const Inventory&,
                                         const FlightDateKey_T&);

    /** Create the leg-date corresponding to the given boarding point. */
    static LegDate& createLegDate (const FlightDate&, const AirportCode_T&);

    /** Create the leg-cabin corresponding to the given cabin code. */
    static LegCabin& createLegCabin (const LegDate&, const CabinCode_T&);
    
    /** Create the segment-date corresponding to the given key. */
    static SegmentDate& createSegmentDate (const FlightDate&,
                                           const SegmentDateKey_T&);

    /** Create the segment-cabin corresponding to the given cabin code. */
    static SegmentCabin& createSegmentCabin (const SegmentDate&, 
                                             const CabinCode_T&);

    /** Create the booking class corresponding to the given class code. */
    static BookingClass& createBookingClass (const SegmentCabin&,
                                             const ClassCode_T&);

    /** Create the flight-period corresponding to the given key. */
    static FlightPeriod& createFlightPeriod (const Inventory&,
                                             const FlightPeriodKey_T&);

    /** Create the segment-period corresponding to the given key. */
    static SegmentPeriod& createSegmentPeriod (const FlightPeriod&,
                                               const SegmentPeriodKey_T&);

    /** Create the reachable-universe corresponding to the origin airport. */
    static ReachableUniverse& createReachableUniverse (const BomRoot&,
                                                       const AirportCode_T&);

    /** Create the origin-destination set corresponding to the
        destination airport. */
    static OriginDestinationSet&
    createOriginDestinationSet (const ReachableUniverse&, const AirportCode_T&);

    /** Create the segment path period corresponding to the given key. */
    static SegmentPathPeriod&
    createSegmentPathPeriod (const OriginDestinationSet&,
                             const SegmentPathPeriodKey_T&);

    /** Create the inventory corresponding to the given network key,
        then link it to the BomRoot object. */
    static Network& createNetwork (const BomRoot&, const NetworkKey_T&);
    
    /** Create the network-date corresponding to the given date. */
    static NetworkDate& createNetworkDate (const Network&, const Date_T&);

    /** Create the airport-date corresponding to the given boarding point. */
    static AirportDate& createAirportDate (const NetworkDate&,
                                           const AirportCode_T&);
    
    /** Create the outbound path  corresponding to the given key. */
    static OutboundPath& createOutboundPath (const AirportDate&,
                                             const OutboundPathKey_T&);
    
  };

}
#endif // ___STDAIR_CMD_CMDBOMMANAGER_HPP
