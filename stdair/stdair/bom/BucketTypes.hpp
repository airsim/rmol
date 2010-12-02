// //////////////////////////////////////////////////////////////////////
#ifndef __STDAIR_BOM_BUCKETTYPES_HPP
#define __STDAIR_BOM_BUCKETTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <list>
// StdAir
#include <stdair/bom/key_types.hpp>

namespace stdair {
  
  // Forward declarations
  class Bucket;

  /** Define the Inventory list. */
  typedef std::list<Bucket*> BucketList_T;
  
  /** Define the Inventory map. */
  typedef std::map<const MapKey_T, Bucket*> BucketMap_T;
  
}
#endif // __STDAIR_BOM_BUCKETTYPES_HPP

