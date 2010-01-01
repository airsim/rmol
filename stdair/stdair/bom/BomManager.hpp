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
    /** Recursively display (dump in the underlying output log stream)
        the objects of the given BOM tree.
        @param std::ostream& Output stream in which the BOM tree should be
               logged/dumped.
        @param const BomRoot& Root of the BOM tree to be displayed. */
    static void display (std::ostream&, const BomRoot&);
  };

}
#endif // __STDAIR_BOM_BOMMANAGER_HPP
