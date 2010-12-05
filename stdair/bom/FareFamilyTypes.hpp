// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_FAREFAMILYTYPES_HPP
#define __STDAIR_BOM_FAREFAMILYTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// StdAir
#include <stdair/bom/key_types.hpp>

namespace stdair {

  // Forward declarations.
  class FareFamily;

  /** Define the fare family list. */
  typedef std::list<FareFamily*> FareFamilyList_T;

  /** Define the fare family map. */
  typedef std::map<const MapKey_T, FareFamily*> FareFamilyMap_T;      
}
#endif // __STDAIR_BOM_FAREFAMILYTYPES_HPP
