#ifndef __STDAIR_BOM_BOMCONTENTROOT_HPP
#define __STDAIR_BOM_BOMCONTENTROOT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomContent.hpp>

namespace stdair {
  // Forward declarations.
  template <typename BOM_CONTENT> class BomStructureRoot;
  template <typename BOM_CONTENT> class BomStructureRootKey;

  /** Class representing the actual functional/business content
      for the Bom root.
      <br>That class is just an utility tool to mark the root
      of the Bom tree. */
  template <typename BOM_CHILD>
  class BomContentRoot : public BomContent {
    friend class FacBomContent;

    // /////////////////////////////////////////////////////////////////////////
    // Type definitions, compulsary for the STDAIR library to work correctly
    // /////////////////////////////////////////////////////////////////////////
    /** The following types must be defined:
        <ul>
          <li>ParentBomContent_T: Type corresponding to the parent BOM
          class within that namespace (e.g., AIRSCHED here)</li>
          <li>BomStructure_T: Type of the corresponding BOM class within
          the stdair namespace</li>
          <li>BomKey_T: Type of the corresponding BOM Key structure within
          the stdair namespace</li>
          <li>ContentChild_T: Type corresponding to the child BOM
          class within that namespace (e.g., AIRSCHED here)</li>
        </ul>
        <br><br>
        Note that the BomContentRoot has no parent. So, there is no need for
        that class to define a ParentBomContent_T type.
        <br><br>
        Note that when there is a second type of children (for instance,
        the FlightDate object contains two types of children, namely LegDate
        and SegmentDate), an additional type definition must be given, namely
        SecondContentChild_T. As, by default, there is a single type of
        children, there is no need to specify "First" in the ContentChild_T
        type.
    */
    
  public:
    // /////////////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef BomStructureRoot<BomContentRoot> BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BomStructureRootKey<BomContentRoot> BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef BOM_CHILD ContentChild_T;
    // /////////////////////////////////////////////////////////////////////////


    // /////////////////////////////////////////////////////////////////////////
    // In order to enable STL-iterator-like browsing of children objects,
    // extra type definitions may be specified, such as the ones commented
    // below. Hence, although those type definitions may appear not so simple
    // (some will say "idiomatic"), they allow for a very simple use.
    // /////////////////////////////////////////////////////////////////////////
    /** Define the const iterator on the list of children objects . */
    // typedef stdair::BomIterator_T<BomContent,
    //                        BomStructureList_T::const_iterator> const_iterator;
    // where BomStructureList_T is defined as std::vector<BomStructure_T*>
    // /////////////////////////////////////////////////////////////////////////

    
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const { return describeKey(); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return std::string (""); }

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return std::string (""); }

    private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _bomStructure;
    }
    
  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    BomContentRoot ();
    BomContentRoot (const BomContentRoot&);
    BomContentRoot (BomStructure_T& ioBomStructure)
      : _bomStructure (ioBomStructure) { }

    /** Destructor. */
    virtual ~BomContentRoot() { }

  private:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _bomStructure;
  };

}
#endif // __STDAIR_BOM_BOMCONTENTROOT_HPP
