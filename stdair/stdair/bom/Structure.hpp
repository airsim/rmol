#ifndef __STDAIR_BOM_STRUCTURE_HPP
#define __STDAIR_BOM_STRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iostream>
// BOOST Fusion
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomStructure.hpp>

namespace stdair {
  // Forward declarations.
  template <typename CONTENT> class BomChildrenHolderImp;
  
  /** Wrapper class aimed at holding the actual content, modeled
      by a specific BomContentRoot class. */
  template <typename CONTENT>
  class Structure : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;
    friend class BomStructure;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated content. */
    typedef CONTENT Content_T;
    
    /** Definition allowing to retrieve the associated key type. */
    typedef typename Content_T::BomKey_T BomKey_T;

    /** Definition allowing to retrieve the map of children holder type. */
    typedef typename Content_T::ChildrenHolderTypeMap_T ChildrenHolderTypeMap_T;

    /** Definition allowing to retrieve the parent structure type. */
    typedef typename Content_T::Parent_T::BomStructure_T Parent_T;

  public:
    // ////////// GETTERS ////////////
    const BomKey_T& getKey () const {
      assert (_content != NULL);
      return _content->getKey();
    }

    template <typename CHILD>
    BomChildrenHolderImp<CHILD>& getChildrenHolder () {
      BomChildrenHolderImp<CHILD>* lHolder_ptr =
        boost::fusion::at_key<CHILD> (_holderMap);
      assert (lHolder_ptr != NULL);

      return *lHolder_ptr;
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
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return getKey().describe(); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return getKey().toString(); }

  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    Structure () : _parent (NULL), _content (NULL) { };
    Structure (const Structure&);

    /** Destructor. */
    ~Structure () { }

  private:
    // Attributes
    /** The parent structure. */
    Parent_T* _parent;
    
    /** The actual functional (Business Object) content. */
    Content_T* _content;

    /** The map of children holders. */
    ChildrenHolderTypeMap_T _holderMap;
  };

}
#endif // __STDAIR_BOM_STRUCTURE_HPP

