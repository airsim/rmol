#ifndef __STDAIR_BOM_BOMSTRUCTURELIST_HPP
#define __STDAIR_BOM_BOMSTRUCTURELIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>
#include <vector>
#include <list>

namespace stdair {

  /** Forward declarations. */
  class BomStructure;

  /** Define lists of Bom-Structure objects. */
  typedef std::map<std::string, BomStructure*> BomStructureList_T;
  typedef std::vector<BomStructure*> BomStructureOrderedList_T;
  typedef std::list<const BomStructure*> BomStructureLightList_T;

}
#endif // __STDAIR_BOM_BOMSTRUCTURELIST_HPP
