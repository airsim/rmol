#ifndef __STDAIR_BOM_BOMCHILDRENHOLDERIMP_HPP
#define __STDAIR_BOM_BOMCHILDRENHOLDERIMP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <vector>
#include <string>
#include <map>
//STDAIR 
#include <stdair/bom/BomChildrenHolder.hpp>
#include <stdair/bom/BomIterator.hpp>

namespace stdair {
  
  /** Template class aimed at holding a list and a map of children BOM
      structure of a dedicated type. */
  template <typename BOM_CONTENT_CHILD>
  class BomChildrenHolderImp : public BomChildrenHolder {
    friend class FacBomStructure;

    /** Retrieve associated bom structure type. */
    typedef typename BOM_CONTENT_CHILD::BomStructure_T BomStructure_T;
    
  public:
    /** Define lists of children BOM structures. */
    typedef std::vector<BomStructure_T*> BomChildrenOrderedList_T;
    typedef std::map<const std::string, BomStructure_T*> BomChildrenList_T;

    /** Define the different types of iterators. */
    typedef BomConstIterator_T<BOM_CONTENT_CHILD,
                               typename BomChildrenOrderedList_T::const_iterator> ListConstIterator_T;
    typedef BomConstIterator_T<BOM_CONTENT_CHILD,
                               typename BomChildrenOrderedList_T::const_reverse_iterator> ListConstReverseIterator_T;
    typedef BomIterator_T<BOM_CONTENT_CHILD,
                          typename BomChildrenOrderedList_T::iterator> ListIterator_T;
    typedef BomIterator_T<BOM_CONTENT_CHILD,
                          typename BomChildrenOrderedList_T::reverse_iterator> ListReverseIterator_T;
    typedef BomConstIterator_T<BOM_CONTENT_CHILD,
                               typename BomChildrenList_T::const_iterator> MapConstIterator_T;
    typedef BomConstIterator_T<BOM_CONTENT_CHILD,
                               typename BomChildrenList_T::const_reverse_iterator> MapConstReverseIterator_T;
    typedef BomIterator_T<BOM_CONTENT_CHILD,
                          typename BomChildrenList_T::iterator> MapIterator_T;
    typedef BomIterator_T<BOM_CONTENT_CHILD,
                          typename BomChildrenList_T::reverse_iterator> MapReverseIterator_T;

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return std::string (""); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return std::string (""); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return std::string (""); }

    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void describeFull (std::ostringstream& ioOut) const {
      // Initialise the index
      unsigned short lIdx = 0;
      
      for (typename BomChildrenOrderedList_T::const_iterator itChild =
             _bomChildrenOrderedList.begin();
           itChild != _bomChildrenOrderedList.end(); ++itChild, ++lIdx) {
        const BomStructure_T* lCurrentChild_ptr = *itChild;
        ioOut << "[" << lIdx << "]: ";
        lCurrentChild_ptr->describeFull (ioOut);
      }
    }

    // /////////// Iteration methods //////////
    /** Initialise the internal const iterators on bom objects:
        return the iterator at the begining of the list. */
    ListConstIterator_T listConstIteratorBegin () const {
      return _bomChildrenOrderedList.begin();
    }
    
    /** Initialise the internal const iterators on bom objects:
        return the iterator past the end of the list. */
    ListConstIterator_T listConstIteratorEnd () const {
      return _bomChildrenOrderedList.end();
    }

    /** Initialise the internal const reverse iterators on bom objects:
        return the reverse iterator at the rbegining of the list. */
    ListConstReverseIterator_T listConstIteratorRBegin () const {
      return _bomChildrenOrderedList.rbegin();
    }
    
    /** Initialise the internal const reverse iterators on bom objects:
        return the reverse iterator past the rend of the list. */
    ListConstReverseIterator_T listConstIteratorREnd () const {
      return _bomChildrenOrderedList.rend();
    }

    /** Initialise the internal iterators on bom objects:
        return the iterator at the begining of the list. */
    ListIterator_T listIteratorBegin () {
      typename BomChildrenOrderedList_T::iterator it =
        _bomChildrenOrderedList.begin();
      typename BomChildrenOrderedList_T::const_iterator it2 =
        _bomChildrenOrderedList.begin();
      return ListIterator_T (it);
    }
    
    /** Initialise the internal iterators on bom objects:
        return the iterator past the end of the list. */
    ListIterator_T listIteratorEnd () const {
      return _bomChildrenOrderedList.end();
    }

    /** Initialise the internal reverse iterators on bom objects:
        return the reverse iterator at the rbegining of the list. */
    ListReverseIterator_T listIteratorRBegin () const {
      return _bomChildrenOrderedList.rbegin();
    }
    
    /** Initialise the internal reverse iterators on bom objects:
        return the reverse iterator past the rend of the list. */
    ListReverseIterator_T listIteratorREnd () const {
      return _bomChildrenOrderedList.rend();
    }

    /** Initialise the internal const iterators on bom objects:
        return the iterator at the begining of the map. */
    MapConstIterator_T mapConstIteratorBegin () const {
      return _bomChildrenList.begin();
    }
    
    /** Initialise the internal const iterators on bom objects:
        return the iterator past the end of the map. */
    MapConstIterator_T mapConstIteratorEnd () const {
      return _bomChildrenList.end();
    }

    /** Initialise the internal const reverse iterators on bom objects:
        return the reverse iterator at the rbegining of the map. */
    MapConstReverseIterator_T mapConstIteratorRBegin () const {
      return _bomChildrenList.rbegin();
    }
    
    /** Initialise the internal const reverse iterators on bom objects:
        return the reverse iterator past the rend of the map. */
    MapConstReverseIterator_T mapConstIteratorREnd () const {
      return _bomChildrenList.rend();
    }

    /** Initialise the internal iterators on bom objects:
        return the iterator at the begining of the map. */
    MapIterator_T mapIteratorBegin () const {
      return _bomChildrenList.begin();
    }
    
    /** Initialise the internal iterators on bom objects:
        return the iterator past the end of the map. */
    MapIterator_T mapIteratorEnd () const {
      return _bomChildrenList.end();
    }

    /** Initialise the internal reverse iterators on bom objects:
        return the reverse iterator at the rbegining of the map. */
    MapReverseIterator_T mapIteratorRBegin () const {
      return _bomChildrenList.rbegin();
    }
    
    /** Initialise the internal reverse iterators on bom objects:
        return the reverse iterator past the rend of the map. */
    MapReverseIterator_T mapIteratorREnd () const {
      return _bomChildrenList.rend();
    }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomChildrenHolderImp () { }
    BomChildrenHolderImp (const BomChildrenHolderImp&);

    /** Destructor. */
    ~BomChildrenHolderImp() { }
    
  private:
    ///////////// Attributes //////////////
    /** List of children BOM structures. */
    BomChildrenList_T _bomChildrenList;

    /** Map of children BOM structures with their key. */
    BomChildrenOrderedList_T _bomChildrenOrderedList;
  };
  
}
#endif // __STDAIR_BOM_BOMCHILDRENHOLDERIMP_HPP

