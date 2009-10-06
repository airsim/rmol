#ifndef __STDAIR_BOM_BOMITERATOR_T_HPP
#define __STDAIR_BOM_BOMITERATOR_T_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <vector>
#include <map>
// STDAIR
#include <stdair/basic/BasTypes.hpp>

namespace stdair {
  
  /** Template class aimed at iterating a list or a map of children BOM
      structure of a dedicated type.
      <br> This class aimed at implementing the "normal" operators except
      ones that needs to return a specific type (const/non-const) of iterator.
  */
  template <typename BOM_CONTENT, typename ITERATOR>
  struct BomIterator_T {

  public:
    // Definition allowing to retrieve the corresponding bom structure.
    typedef typename BOM_CONTENT::BomStructure_T BomStructure_T;
    
    // Define the pair of string and pointer of BOM_CONTENT.
    typedef typename std::pair<std::string, BOM_CONTENT*> value_type;

    // Definition allowing the retrieve the difference type of the ITERATOR.
    typedef typename ITERATOR::difference_type difference_type;

  protected:
    /** Normal constructor. */
    BomIterator_T (ITERATOR iIterator)
      : _itBomStructureObject (iIterator) { }

    /** Default constructor. */
    BomIterator_T () { }
    
    /** Default copy constructor. */
    BomIterator_T (const BomIterator_T& iBomIterator)
      : _itBomStructureObject (iBomIterator._itBomStructureObject) { }
    
    /** Destructor. */
    ~BomIterator_T() { }

  public:
    // ///////////// Operators //////////////
    /** Incrementing (prefix and postfix) operators. */
    void operator++ () { ++_itBomStructureObject; }
    void operator++ (int) { ++_itBomStructureObject; }

    /** Decrementing (prefix and postfix) operators. */
    void operator-- () { --_itBomStructureObject; }
    void operator-- (int) { --_itBomStructureObject; }
    
    /** Equality operators. */
    bool operator== (const BomIterator_T& iIt) {
      return _itBomStructureObject == iIt._itBomStructureObject;
    }
    bool operator!= (const BomIterator_T& iIt) {
      return _itBomStructureObject != iIt._itBomStructureObject;
    }

    /** Relational operators. */
    bool operator< (const BomIterator_T& iIt) {
      return _itBomStructureObject < iIt._itBomStructureObject;
    }
    bool operator> (const BomIterator_T& iIt) {
      return _itBomStructureObject > iIt._itBomStructureObject;
    }
    bool operator<= (const BomIterator_T& iIt) {
      return _itBomStructureObject <= iIt._itBomStructureObject;
    }
    bool operator>= (const BomIterator_T& iIt) {
      return _itBomStructureObject >= iIt._itBomStructureObject;
    }

    /** Additive Operators. */
    BomIterator_T operator+ (const difference_type iIndex) {
      return BomIterator_T(_itBomStructureObject + iIndex);
    } 
    BomIterator_T& operator+= (const difference_type iIndex) {
      _itBomStructureObject += iIndex;
      return *this;
    }
    BomIterator_T operator- (const difference_type iIndex) {
      return BomIterator_T(_itBomStructureObject - iIndex);
    }
    BomIterator_T& operator-= (const difference_type iIndex) {
      _itBomStructureObject -= iIndex;
      return *this;
    }

    // ////////////// Dereferencing Operators //////////////
    /** Dereferencing operator for iterators on a list. */
    BOM_CONTENT& operator* () {
      const BomStructure_T* lBomStruct_ptr = *_itBomStructureObject;
      assert (lBomStruct_ptr != NULL);
      BOM_CONTENT* lBomContent_ptr = 
        BomStructure::getBomContentPtr<BOM_CONTENT> (*lBomStruct_ptr);
      assert (lBomContent_ptr != NULL);
      return *lBomContent_ptr;
    }

    /** Dereferencing operator for iterators on a map. */
    value_type* operator-> () {
      const MapKey_T& lKey = _itBomStructureObject->first;
      const BomStructure_T* lBomStruct_ptr =
        _itBomStructureObject->second;
      assert (lBomStruct_ptr != NULL);
      BOM_CONTENT* lBomContent_ptr = 
        BomStructure::getBomContentPtr<BOM_CONTENT> (*lBomStruct_ptr);
      assert (lBomContent_ptr != NULL);

      // See the comment below, at the definition of the _intermediateValue
      // attribute
      _intermediateValue.first = lKey;
      _intermediateValue.second = lBomContent_ptr;
      
      return &_intermediateValue;
    }

  private:
    ///////////// Attributes //////////////
    /** Iterator for the current BOM structure on the non-ordered list. */
    ITERATOR _itBomStructureObject;

    /** Helper attribute.
        <br>It is necessary to define that value at the attribute
        level, because the operator->() method needs to return a
        pointer on it. If that value be temporary, i.e., created at
        the fly when the operator->() method returns, we would return
        a pointer on a temporary value, which is not good. */
    value_type _intermediateValue;
    
  };


  /**
     Operators for BomIterator_T that need to be implemented outside
     of BomIterator_T scope.
   */
  template<typename BOM_CONTENT, typename ITERATOR>
  inline typename ITERATOR::difference_type
  operator-(const BomIterator_T<BOM_CONTENT, ITERATOR>& l, 
            const BomIterator_T<BOM_CONTENT, ITERATOR>& r) {
    return l._itBomStructureObject - r._itBomStructureObject;
  }

  template<typename BOM_CONTENT, typename ITERATOR>
  inline BomIterator_T<BOM_CONTENT, ITERATOR>
  operator+(const typename ITERATOR::difference_type n, 
            const BomIterator_T<BOM_CONTENT, ITERATOR>& r) {
    // Definition allowing to retrieve the Parent_T of BomIterator_T.
    typedef typename BomIterator_T<BOM_CONTENT,ITERATOR>::Parent_T Parent_T;
    return BomIterator_T<BOM_CONTENT, ITERATOR>
      (n+r._itBomStructureObject);
  }
  
}
#endif // __STDAIR_BOM_BOMITERATOR_T_HPP
