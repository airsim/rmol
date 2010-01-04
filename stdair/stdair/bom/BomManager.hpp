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
    static void display (std::ostream&, const FlightDate&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const LegDate& Root of the BOM tree to be displayed. */
    static void display (std::ostream&, const LegDate&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const LegCabin& Root of the BOM tree to be displayed. */
    static void display (std::ostream&, const LegCabin&);

    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const SegmentDate& Root of the BOM tree to be displayed. */
    static void display (std::ostream&, const SegmentDate&);

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
  };

}
#endif // __STDAIR_BOM_BOMMANAGER_HPP
