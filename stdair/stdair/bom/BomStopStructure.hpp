#ifndef __STDAIR_BOM_BOMSTOPSTRUCTURE_HPP
#define __STDAIR_BOM_BOMSTOPSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/BomKey.hpp>
#include <stdair/bom/BomChildrenHolderImp.hpp>
// MPL
#include <boost/mpl/vector.hpp>

namespace stdair {
  // Forward declarations.
  class BomStopContent;

  /** Wrapper class aimed at holding the actual content, modeled
      by a specific BomStopContent class. */
  class BomStopStructure : public BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;

  private:
    // Type definitions
    /** Definition allowing to retrieve the associated BOM content type. */
    typedef BomStopContent Content_T;

    /** Definition allowing to retrieve the associated children type. */
    typedef boost::mpl::vector<> ChildrenBomTypeList_T;

    /** Definition allowing to retrive the default children bom holder type. */
    typedef BomChildrenHolderImp<mpl_::void_> DefaultChildrenBomHolder_T;
    
  public:

    // /////////// Getters /////////////
    /** Get the BomStopStructure key. */
    const BomKey_T& getKey() const {
      return _key;
    }

  private: 
    /////////////// Setters ////////////////
    /** Default children list setter. */
    void setChildrenList (DefaultChildrenBomHolder_T&) { }
    
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
    std::string toString() const { return describeKey(); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return _key.toString(); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return _key.toString(); }


  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomStopStructure ();
    BomStopStructure (const BomStopStructure&);
    BomStopStructure (const BomKey_T& iKey) { _key = iKey; }

    /** Destructor. */
    ~BomStopStructure () { }

  private:
    // Attributes
    /** The key of both the structure and content objects. */
    BomKey_T _key; 

    /** The actual functional (Business Object) content. */
    Content_T* _content;
  };

}
#endif // __STDAIR_BOM_BOMSTOPSTRUCTURE_HPP

