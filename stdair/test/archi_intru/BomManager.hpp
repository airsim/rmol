#ifndef __INTRUSIVE_BOM_BOMMANAGER_HPP
#define __INTRUSIVE_BOM_BOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>

namespace stdair {

  /** Utility class. */
  class BomManager {
  public:
    /** Display the full BOM tree. */
    static std::string display (const BomRoot&);
    
  private:
    
  };

}
#endif // __INTRUSIVE_BOM_BOMMANAGER_HPP
