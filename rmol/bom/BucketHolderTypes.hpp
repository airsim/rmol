#ifndef __RMOL_BUCKETHOLDERTYPES_HPP
#define __RMOL_BUCKETHOLDERTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
#include <map>
// STDAIR
#include <stdair/stdair_basic_types.hpp>

namespace RMOL {

  /** Forward declarations. */
  class BucketHolder;

  /** Define a vector (ordered list) of N bucket/classe holders. */
  typedef std::list<BucketHolder*> BucketHolderList_T;

  /** Define a map of bucket holders. The key should be the key of the
      corresponding leg-cabin. */
  typedef std::map<const stdair::MapKey_T, BucketHolder*>;
}
#endif // __RMOL_BUCKETHOLDERTYPES_HPP
