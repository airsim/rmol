#ifndef __STRUCTURE_HPP
#define __STRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include "StructureTypes.hpp"
#include <stdair/bom/BomStructure.hpp>
// STL
#include <cassert>

namespace stdair {
  // Forward declarations.
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename CONTENT> class BomMap_T;
  template <typename CONTENT> class BomMultimap_T;
  template <typename CONTENT> class BomList_T;
}

/** Wrapper class aimed at holding the actual content, modeled
    by a specific BomContentRoot class. */
template <typename CONTENT>
class Structure : public stdair::BomStructure {

public:
  // Type definitions
  /** Definition allowing to retrieve the associated content. */
  typedef CONTENT Content_T;

  /** Definition allowing to retrieve the associated key type. */
  typedef typename Content_T::Key_T Key_T;

  /** Definition allowing to retrieve the map of children holder type. */
  typedef typename boost::mpl::at<
    ChildrenHolderMapMap_T, Content_T>::type ChildrenHolderMap_T;

  /** Definition allowing to retrieve the parent structure type. */
  typedef typename boost::mpl::at<
    ParentMap_T, Content_T>::type::Structure_T Parent_T;

public:
  // ////////// Getters ////////////
  /** Get the content object. */
  const Content_T& getContent () const {
    assert (_content != NULL);
    return *_content;
  }

  /** Get the key of the content object. */
  const Key_T& getKey () const {
    assert (_content != NULL);
    return _content->getKey();
  }

  /** Get the parent structure. */
  const Parent_T& getParent () const {
    assert (_parent != NULL);
    return *_parent;
  }
    
  /** The the holder which corresponds to the CHILD type. */
  template <typename CHILD>
  stdair::BomChildrenHolderImp<CHILD>& getChildrenHolder () const {

    stdair::BomChildrenHolderImp<CHILD>* lHolder_ptr =
      boost::fusion::at_key<CHILD> (_holderMap);

    assert (lHolder_ptr != NULL);
    return *lHolder_ptr;
  }

  /** Retrieve, if existing, the pointer of CHILD type corresponding to the
      given key.
      <br>If not exissting, return the NULL pointer. */
  template <typename CHILD>
  CHILD* getChildPtr (const std::string& iKey) const {
    CHILD* oContentChild_ptr = NULL;
      
    stdair::BomChildrenHolderImp<CHILD>* lHolder_ptr =
      boost::fusion::at_key<CHILD> (_holderMap);

    if (lHolder_ptr != NULL) {
      // Look for the child in the map, then in the multimap
      stdair::BomMap_T<CHILD> lChildrenMap (*lHolder_ptr);
      typename stdair::BomMap_T<CHILD>::iterator itContentChild = 
        lChildrenMap.find (iKey);
      if (itContentChild != lChildrenMap.end()) {
        oContentChild_ptr = itContentChild->second;
      }
    }
      
    return oContentChild_ptr;
  }

  /** Retrieve, child of CHILD type corresponding to the given key. */
  template <typename CHILD>
  CHILD& getChild (const std::string& iKey) const {
    CHILD* lChild_ptr = NULL;
      
    const stdair::BomChildrenHolderImp<CHILD>& lHolder = getChildrenHolder<CHILD>();
    stdair::BomMap_T<CHILD> lChildrenMap (lHolder);
      
    typename stdair::BomMap_T<CHILD>::iterator itContentChild =
      lChildrenMap.find (iKey);
      
    if (itContentChild != lChildrenMap.end()) {
      lChild_ptr = itContentChild->second;
    }

    assert (lChild_ptr != NULL);
    return *lChild_ptr;
  }

  // /////////// Business method ////////////
  /** Initialise the pointer of children holder to NULL. */
  template <typename CHILD>
  void initChildrenHolder() {

    stdair::BomChildrenHolderImp<CHILD>*& lHolder_ptr =
      boost::fusion::at_key<CHILD> (_holderMap);
    lHolder_ptr = NULL;
  }

public:
  // /////////// Display support methods /////////
  /** Dump a Business Object into an output stream.
      @param ostream& the output stream. */
  void toStream (std::ostream& ioOut) const {
    ioOut << toString() << std::endl;
  }

  /** Read a Business Object from an input stream.
      @param istream& the input stream. */
  void fromStream (std::istream& ioIn) { }

  /** Get the serialised version of the Business Object. */
  std::string toString() const { return describeShortKey(); }

  /** Get a string describing the short key (differentiating two objects
      at the same level). */
  const std::string describeShortKey() const { return getKey().toString(); }

  /** Get a string describing the parent's whole key
      (differentiating two objects at any level). */
  const std::string describeParentKey() const {
    assert (_parent != NULL);
    return _parent->getContent().describeKey();
  }

public:
  /** Constructors are private so as to force the usage of the Factory
      layer. */
  /** Default constructors. */
  Structure () : _parent (NULL), _content (NULL) { }
  Structure (const Structure&) { assert (false); };
  /** Destructor. */
  ~Structure () { }

public:
  // Attributes
  /** The parent structure. */
  Parent_T* _parent;
    
  /** The actual functional (Business Object) content. */
  Content_T* _content;

  /** The map of children holders. */
  ChildrenHolderMap_T _holderMap;
};

#endif // __STRUCTURE_HPP
