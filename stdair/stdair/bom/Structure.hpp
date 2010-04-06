#ifndef __STDAIR_BOM_STRUCTURE_HPP
#define __STDAIR_BOM_STRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// STDAIR
#include <stdair/bom/BomStructure.hpp>

namespace stdair {
  /** Wrapper class aimed at holding the actual content, modeled
      by a specific BomContentRoot class. */
  template <typename CONTENT>
  class Structure : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;
    friend class BomStructure;

  public:
    // Type definitions
    /** Definition allowing to retrieve the associated key type. */
    typedef typename CONTENT::Key_T Key_T;

    /** Definition allowing to retrieve the map of children holder type. */
    typedef typename CONTENT::ChildrenHolderTypeMap_T ChildrenHolderTypeMap_T; 

  public:
    // ////////// GETTERS ////////////
    const Key_T& getKey () {
      assert (_content != NULL);
      return _content->getKey();
    }

  private: 
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
    Structure () : _content (NULL) { };
    Structure (const Structure&);

    /** Destructor. */
    ~Structure () { }

  private:
    // Attributes
    /** The actual functional (Business Object) content. */
    CONTENT* _content;

    /** The map of children holders. */
    ChildrenHolderTypeMap_T _holderMap;
  };

}
#endif // __STDAIR_BOM_STRUCTURE_HPP

