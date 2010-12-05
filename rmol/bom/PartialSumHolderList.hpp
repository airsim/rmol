#ifndef __RMOL_BOM_PARTIALSUMLIST_HPP
#define __RMOL_BOM_PARTIALSUMLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>

namespace RMOL {

  /** Forward declarations. */
  class PartialSumHolder;

  /** Define a vector (ordered list) of N buckets/classes. */
  typedef std::list<PartialSumHolder*> PartialSumHolderList_T;

}
#endif // __RMOL_BOM_PARTIALSUMLIST_HPP
