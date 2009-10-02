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
  template <typename ITERATOR>
  struct BomIteratorAbstract {

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Normal constructor. */
    BomIteratorAbstract (ITERATOR iIterator)
      : _itBomStructureObject (iIterator) { }

    /** Default constructor. */
    BomIteratorAbstract () { }
    
    /** Default copy constructor. */
    BomIteratorAbstract (const BomIteratorAbstract& iBomIterator)
      : _itBomStructureObject (iBomIterator._itBomStructureObject) { }
    
    /** Destructor. */
    ~BomIteratorAbstract() { }

  public:
    // ///////////// Operators //////////////
    /** Incrementing (prefix and postfix) operators. */
    void operator++ () { ++_itBomStructureObject; }
    void operator++ (int) { ++_itBomStructureObject; }

    /** Decrementing (prefix and postfix) operators. */
    void operator-- () { --_itBomStructureObject; }
    void operator-- (int) { --_itBomStructureObject; }
    
    /** Equality operators. */
    bool operator== (const BomIteratorAbstract& iIt) {
      return _itBomStructureObject == iIt._itBomStructureObject;
    }
    bool operator!= (const BomIteratorAbstract& iIt) {
      return _itBomStructureObject != iIt._itBomStructureObject;
    }

    /** Relational operators. */
    bool operator< (const BomIteratorAbstract& iIt) {
      return _itBomStructureObject < iIt._itBomStructureObject;
    }
    bool operator> (const BomIteratorAbstract& iIt) {
      return _itBomStructureObject > iIt._itBomStructureObject;
    }
    bool operator<= (const BomIteratorAbstract& iIt) {
      return _itBomStructureObject <= iIt._itBomStructureObject;
    }
    bool operator>= (const BomIteratorAbstract& iIt) {
      return _itBomStructureObject >= iIt._itBomStructureObject;
    }


  public:
    ///////////// Attributes //////////////
    /** Iterator for the current BOM structure on the non-ordered list. */
    ITERATOR _itBomStructureObject;

  };


  /**
     Operators for BomIteratorAbstract that need to be implemented outside
     of BomIteratorAbstract scope.
   */
  template<typename ITERATOR>
  inline typename ITERATOR::difference_type
  operator-(const BomIteratorAbstract<ITERATOR>& l, 
            const BomIteratorAbstract<ITERATOR>& r) {
    return l._itBomStructureObject - r._itBomStructureObject;
  }

  
  /** Template class aimed at iterating a list or a map of children BOM
      structure of a dedicated type using const iterators.
      <br> This class aimed at implementing the specific operators for
      const iterators.
  */
  template <typename BOM_CONTENT, typename ITERATOR>
  struct BomConstIterator_T : public BomIteratorAbstract<ITERATOR> {

  public:
    // Definition allowing to retrieve the parent type.
    typedef BomIteratorAbstract<ITERATOR> Parent_T;
    
    // Definition allowing to retrieve the corresponding bom structure.
    typedef typename BOM_CONTENT::BomStructure_T BomStructure_T;
    
    // Define the pair of string and pointer of BOM_CONTENT.
    typedef typename std::pair<std::string, const BOM_CONTENT*> value_type;

    // Definition allowing the retrieve the difference type of the ITERATOR.
    typedef typename ITERATOR::difference_type difference_type;

  public:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Normal constructor. */
    BomConstIterator_T (ITERATOR iIterator)
      : Parent_T (iIterator) { }

    /** Default constructor. */
    BomConstIterator_T () { }
    
    /** Default copy constructor. */
    BomConstIterator_T (const BomConstIterator_T& iBomIterator)
      : Parent_T (iBomIterator._itBomStructureObject) { }
    
    /** Destructor. */
    ~BomConstIterator_T() { }
    
  public:
    // ////////////// Additive Operators ///////////////
    BomConstIterator_T operator+ (const difference_type iIndex) {
      return BomConstIterator_T(Parent_T::_itBomStructureObject + iIndex);
    } 
    BomConstIterator_T& operator+= (const difference_type iIndex) {
      Parent_T::_itBomStructureObject += iIndex;
      return *this;
    }
    BomConstIterator_T operator- (const difference_type iIndex) {
      return BomConstIterator_T(Parent_T::_itBomStructureObject - iIndex);
    }
    BomConstIterator_T& operator-= (const difference_type iIndex) {
      Parent_T::_itBomStructureObject -= iIndex;
      return *this;
    }
    
    // ////////////// Dereferencing Operators //////////////
    /** Dereferencing operator for iterators on a list. */
    const BOM_CONTENT& operator* () {
      BomStructure_T* lBomStruct_ptr = *Parent_T::_itBomStructureObject;
      assert (lBomStruct_ptr != NULL);
      BOM_CONTENT* lBomContent_ptr = 
        BomStructure::getBomContentPtr<BOM_CONTENT> (*lBomStruct_ptr);
      assert (lBomContent_ptr != NULL);
      return *lBomContent_ptr;
    }

    /** Dereferencing operator for iterators on a map. */
    value_type* operator-> () {
      const MapKey_T& lKey = Parent_T::_itBomStructureObject->first;
      BomStructure_T* lBomStruct_ptr = Parent_T::_itBomStructureObject->second;
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

  protected:
    /** Helper attribute.
        <br>It is necessary to define that value at the attribute
        level, because the operator->() method needs to return a
        pointer on it. If that value be temporary, i.e., created at
        the fly when the operator->() method returns, we would return
        a pointer on a temporary value, which is not good. */
    value_type _intermediateValue;
    
  };

  /**
     Operators for BomConstIterator_T that need to be implemented outside
     of BomConstIterator_T scope.
   */
  template<typename BOM_CONTENT, typename ITERATOR>
  inline BomConstIterator_T<BOM_CONTENT, ITERATOR>
  operator+(const typename ITERATOR::difference_type n, 
            const BomConstIterator_T<BOM_CONTENT, ITERATOR>& r) {
    // Definition allowing to retrieve the Parent_T of BomConstIterator_T.
    typedef typename BomConstIterator_T<BOM_CONTENT,ITERATOR>::Parent_T Parent_T;
    return BomConstIterator_T<BOM_CONTENT, ITERATOR>
      (n+r.Parent_T::_itBomStructureObject);
  }

}
#endif // __STDAIR_BOM_BOMITERATOR_T_HPP
