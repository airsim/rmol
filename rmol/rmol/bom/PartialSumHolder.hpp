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
    // ///////// Getters /////////
    /** Get the k-th element (partial sum). */
    const double getPartialSum (const int k) const;

    /** Get the position of the first element that is equal or greater
        than the given value. */
    const int getLowerBound (const double& value) const;

    /** Reserve the space for K elements (partial sums). */
    void initSize (const int K);

    /** Add an element (partial sum). */
    void addPartialSum (const double iPartialSum);

    /** Sort the elements (partial sums).
	The STL implements the introsort algorithm, which has a worst case
	complexity of O (N log N): http://www.sgi.com/tech/stl/sort.html . */
    void sort ();

  public:
    // ///////// Display methods ////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream&) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream&);

    /** Get the serialised version of the Place object. */
    std::string toString() const;

    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const;
    
    /** Display the full Place context. */
    const std::string display() const;

    /** Display a short Place context. */
    const std::string shortDisplay() const;

    
  private:
    /** Constructors. */
    PartialSumHolder ();
    PartialSumHolder (const PartialSumHolder&);

    /** Destructor. */
    virtual ~PartialSumHolder();

    
  private:
    // ///////// Attributes /////////
    /** The vector of (K) partial sums. */
    PartialSumList_T _partialSumList;
  };
}
#endif // __RMOL_BOM_PARTIALSUMHOLDER_HPP
