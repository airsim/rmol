#ifndef __RMOL_BUCKETLIST_HPP
#define __RMOL_BUCKETLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
// RMOL
#include "Bucket.hpp"

namespace RMOL {

  /** Define a vector (ordered list) of N buckets/classes. */
  typedef std::list<Bucket*> BucketList_T;
  
}
#endif // __RMOL_BUCKETLIST_HPP
