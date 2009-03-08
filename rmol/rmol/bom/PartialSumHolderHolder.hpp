#ifndef __RMOL_BOM_PARTIALSUMHOLDERHOLDER_HPP
#define __RMOL_BOM_PARTIALSUMHOLDERHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
// RMOL
#include <rmol/bom/BomAbstract.hpp>
#include <rmol/bom/PartialSumHolderList.hpp>

namespace RMOL {

  /** Holder of a PartialSumHolder object (for memory allocation and
      recollection purposes). */
  class PartialSumHolderHolder : public BomAbstract {
    /** Friend Classes
        <br>Those classes need to access the internal attributes of this object
        in order to construct and initialise it.*/
    friend class FacPartialSumHolderHolder;
    
  public:
    // ///////// Getters /////////
    /** Get the size of the internal list (i.e., number of partial sum
	lists). */
    const short getSize () const;
    
    /** Get the previous element (partial sum holder/list). */
    PartialSumHolder& getPreviousPartialSumHolder () const;

    /** Get the current element (partial sum holder/list). */
    PartialSumHolder& getCurrentPartialSumHolder () const;

    /** Initialise the internal iterators on PartialSumHolder:
	The current iterator is set on the first PartialSumHolder,
	the next iterator is set on the second PartialSumHolder. */
    void begin ();

    /** Iterate for one element (partial sum holder/list): 
	increment both internal iterators on PartialSumHolder. */
    void iterate ();

    /** States whether or not the end of the (partial sum holder/list) 
	list has been reached. */
    bool hasNotReachedEnd () const;

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
    PartialSumHolderHolder();
    /** Reserve the space for iSize elements (partial sum holders). */
    PartialSumHolderHolder (const int iSize);

    /** Destructor. */
    virtual ~PartialSumHolderHolder();

    
  private:
    /** Add an element (partial sum holder/list).
        <br>Note that the Bucket object may be altered by subsequent
        operations.
	<br>Protected to force the use of the Factory. */
    void addPartialSumHolder (PartialSumHolder&);

    
  private:
    // //////// Attributes /////////
    /** The vector of (K) partial sums. */
    PartialSumHolderList_T _partialSumHolderList;

    /** Iterator for the current bucket/class. */
    PartialSumHolderList_T::iterator _itPreviousPartialSumHolder;
    PartialSumHolderList_T::iterator _itCurrentPartialSumHolder;
  };
}
#endif // __RMOL_BOM_PARTIALSUMHOLDERHOLDER_HPP
