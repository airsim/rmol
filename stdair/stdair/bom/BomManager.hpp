#ifndef __STDAIR_BOM_BOMMANAGER_HPP
#define __STDAIR_BOM_BOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>

namespace stdair {

  // Forward declarations
  class BomRoot;
  class Inventory;
  class FlightDate;
  class LegDate;
  class LegCabin;
  class SegmentDate;
  class SegmentCabin;
  class BookingClass;
  class ReachableUniverse;
  class OriginDestinationSet;
  class SegmentPathPeriod;
  class FlightPeriod;
  class SegmentPeriod;
  class Network;
  class NetworkDate;
  class AirportDate;
  class OutboundPath;
  struct BookingRequestStruct;

  /** Utility class for StdAir objects. */
  class BomManager {
  public:
    // //////////////// Display support methods /////////////////
    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const BomRoot& Root of the BOM tree to be displayed. */
    static void display (std::ostream&, const BomRoot&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const Inventory& Root of the BOM tree to be displayed. */
    static void display (std::ostream&, const Inventory&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const FlightDate& Root of the BOM tree to be displayed. */
    static void csvFlightDateDisplay (std::ostream&, const FlightDate&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const LegDate& Root of the BOM tree to be displayed. */
    static void csvLegDateDisplay (std::ostream&, const FlightDate&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const LegCabin& Root of the BOM tree to be displayed. */
    static void csvLegCabinDisplay (std::ostream&, const FlightDate&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const LegCabin& Root of the BOM tree to be displayed. */
    static void csvBPVDisplay (std::ostream&, const FlightDate&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const SegmentDate& Root of the BOM tree to be displayed. */
    static void csvSegmentCabinDisplay (std::ostream&, const FlightDate&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const SegmentCabin& Root of the BOM tree to be displayed. */
    static void display (std::ostream&, const SegmentCabin&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const BookingClass& Root of the BOM tree to be displayed. */
    static void display (std::ostream&, const BookingClass&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const Network& Root of the BOM tree to be displayed. */
    static void display (std::ostream&, const Network&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const NetworkDate& Root of the BOM tree to be displayed. */
    static void display (std::ostream&, const NetworkDate&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const AirportDate& Root of the BOM tree to be displayed. */
    static void display (std::ostream&, const AirportDate&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const OutboundPath& Root of the BOM tree to be displayed. */
    static void display (std::ostream&, const OutboundPath&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const LegCabin& Root of the BOM tree to be displayed. */
    static void csvDisplay (std::ostream&,
                            const BookingRequestStruct& iBookingRequest);
    /** Helper fuction to display an interger. */
    static void intDisplay (std::ostream&, const int&);
    
    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const BomRoot& Root of the BOM tree to be displayed. */
    static void displaySegmentPathNetwork (std::ostream&, const BomRoot&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree. */
    static void display (std::ostream&, const ReachableUniverse&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree. */
    static void display (std::ostream&, const OriginDestinationSet&);
    
    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree. */
    static void display (std::ostream&, const SegmentPathPeriod&);
  };    

}
#endif // __STDAIR_BOM_BOMMANAGER_HPP
