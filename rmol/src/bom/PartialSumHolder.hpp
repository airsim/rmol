#ifndef __RMOL_PARTIALSUMHOLDER_HPP
#define __RMOL_PARTIALSUMHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
// RMOL
#include "BomAbstract.hpp"
#include "PartialSumList.hpp"

namespace RMOL {

  /** Holder of a PartialSumList object (for memory allocation and
      recollection purposes). */
  class PartialSumHolder : public BomAbstract {
    /** Friend Classes
        <br>Those classes need to access the internal attributes of this object
        in order to construct and initialise it.*/
    friend class FacPartialSumHolder;
    
  public:
    /** Destructor. */
    ~PartialSumHolder();

    /** Get the k-th element (partial sum). */
    const double getPartialSum (const int k) const;

    /** Add an element (partial sum). */
    void addPartialSum (const double iPartialSum);

    /** Sort the elements (partial sums).
	The STL implements the introsort algorithm, which has a worst case
	complexity of O (N log N): http://www.sgi.com/tech/stl/sort.html . */
    void sort ();

    /** Dump a Business Object into an output stream.
        @param ostream& the output stream
        @return ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

  private:
    /** Constructors. */
    PartialSumHolder();
    /** Reserve the space for K elements (partial sums). */
    PartialSumHolder (const int K);

    /** The vector of (K) partial sums. */
    PartialSumList_T _partialSumList;
  };
}
#endif // __RMOL_PARTIALSUMHOLDER_HPP
