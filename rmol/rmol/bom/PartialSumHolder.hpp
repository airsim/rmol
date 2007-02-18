#ifndef __RMOL_BOM_PARTIALSUMHOLDER_HPP
#define __RMOL_BOM_PARTIALSUMHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
// RMOL
#include <rmol/bom/BomAbstract.hpp>
#include <rmol/bom/PartialSumList.hpp>

namespace RMOL {

  /** Holder of a PartialSumList object (for memory allocation and
      recollection purposes). */
  class PartialSumHolder : public BomAbstract {
    /** Friend Classes
        <br>Those classes need to access the internal attributes of this object
        in order to construct and initialise it.*/
    friend class FacPartialSumHolder;
    
  public:
    /** Reserve the space for K elements (partial sums). */
    void initSize (const int K);

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

    /** Display on standard output. */
    void display () const;

    /** Destructor. */
    virtual ~PartialSumHolder();

  private:
    /** Constructors. */
    PartialSumHolder ();
    PartialSumHolder (const PartialSumHolder&);

    /** The vector of (K) partial sums. */
    PartialSumList_T _partialSumList;
  };
}
#endif // __RMOL_BOM_PARTIALSUMHOLDER_HPP
