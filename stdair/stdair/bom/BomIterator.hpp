#ifndef __STDAIR_BOM_BOMITERATOR_T_HPP
#define __STDAIR_BOM_BOMITERATOR_T_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <vector>
#include <map>

namespace stdair {
  
  /** Template class aimed at iterating a list or a map of children BOM
      structure of a dedicated type.
      <br> This class aimed at implementing the "normal" operators except
      ones that needs to return a specific type (const/non-const) of iterator.
  */
  template <typename CONTENT, typename ITERATOR>
  struct BomIterator_T {

  public:
    // Definition allowing to retrieve the corresponding bom structure.
    typedef typename CONTENT::Structure_T Structure_T;
    
    // Define the pair of string and pointer of CONTENT.
    typedef typename std::pair<std::string, CONTENT*> value_type;

    // Definition allowing the retrieve the ITERATOR type.
    typedef ITERATOR iterator_type;
    
    // Definition allowing the retrieve the difference type of the ITERATOR.
    typedef typename ITERATOR::difference_type difference_type;

  public:
    /** Normal constructor. */
    BomIterator_T (iterator_type iIterator)
      : _itStructureObject (iIterator) { }

    /** Default constructor. */
    BomIterator_T () { }
    
    /** Default copy constructor. */
    BomIterator_T (const BomIterator_T& iBomIterator)
      : _itStructureObject (iBomIterator._itStructureObject) { }
    
    /** Destructor. */
    ~BomIterator_T() { }

  public:
    /** Return _itStructureObject, used for underlying work. */
      iterator_type  base() const { return _itStructureObject; }

  public:
    // ///////////// Operators //////////////
    /** Incrementing (prefix and postfix) operators. */
    void operator++ () { ++_itStructureObject; }
    void operator++ (int) { ++_itStructureObject; }

    /** Decrementing (prefix and postfix) operators. */
    void operator-- () { --_itStructureObject; }
    void operator-- (int) { --_itStructureObject; }
    
    /** Equality operators. */
    bool operator== (const BomIterator_T& iIt) {
      return _itStructureObject == iIt._itStructureObject;
    }
    bool operator!= (const BomIterator_T& iIt) {
      return _itStructureObject != iIt._itStructureObject;
    }

    /** Relational operators. */
    bool operator< (const BomIterator_T& iIt) {
      return _itStructureObject < iIt._itStructureObject;
    }
    bool operator> (const BomIterator_T& iIt) {
      return _itStructureObject > iIt._itStructureObject;
    }
    bool operator<= (const BomIterator_T& iIt) {
      return _itStructureObject <= iIt._itStructureObject;
    }
    bool operator>= (const BomIterator_T& iIt) {
      return _itStructureObject >= iIt._itStructureObject;
    }

    /** Additive Operators. */
    BomIterator_T operator+ (const difference_type iIndex) {
      return BomIterator_T(_itStructureObject + iIndex);
    } 
    BomIterator_T& operator+= (const difference_type iIndex) {
      _itStructureObject += iIndex;
      return *this;
    }
    BomIterator_T operator- (const difference_type iIndex) {
      return BomIterator_T(_itStructureObject - iIndex);
    }
    BomIterator_T& operator-= (const difference_type iIndex) {
      _itStructureObject -= iIndex;
      return *this;
    }

    // ////////////// Dereferencing Operators //////////////
    /** Dereferencing operator for iterators on a list. */
    CONTENT& operator* () {
      const Structure_T* lBomStruct_ptr = *_itStructureObject;
      assert (lBomStruct_ptr != NULL);
      CONTENT* lBomContent_ptr = 
        BomStructure::getContentPtr<CONTENT> (*lBomStruct_ptr);
      assert (lBomContent_ptr != NULL);
      return *lBomContent_ptr;
    }

    /** Dereferencing operator for iterators on a map. */
    value_type* operator-> () {
      const MapKey_T& lKey = _itStructureObject->first;
      const Structure_T* lBomStruct_ptr =
        _itStructureObject->second;
      assert (lBomStruct_ptr != NULL);
      CONTENT* lBomContent_ptr = 
        BomStructure::getContentPtr<CONTENT> (*lBomStruct_ptr);
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
    iterator_type _itStructureObject;

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
  template<typename CONTENT, typename ITERATOR>
  inline typename ITERATOR::difference_type
  operator-(const BomIterator_T<CONTENT, ITERATOR>& l, 
            const BomIterator_T<CONTENT, ITERATOR>& r) {
    return l.base() - r.base();
  }

  template<typename CONTENT, typename ITERATOR>
  inline BomIterator_T<CONTENT, ITERATOR>
  operator+(const typename ITERATOR::difference_type n, 
            const BomIterator_T<CONTENT, ITERATOR>& r) {
    return BomIterator_T<CONTENT, ITERATOR> (n+r.base());
  }
  
}
#endif // __STDAIR_BOM_BOMITERATOR_T_HPP
