#ifndef __STDAIR_BOM_LEGCABIN_HPP
#define __STDAIR_BOM_LEGCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/LegCabinContent.hpp>
#include <stdair/bom/LegCabinTypes.hpp>
#include <stdair/bom/BucketTypes.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>

namespace stdair {
  // Forward declarations
  class LegDate;
  class Bucket;
  class SegmentCabin;
  
  /** Class representing the actual functional/business content for a
      leg-date. */
  class LegCabin : public LegCabinContent {
    friend class FacBomContent;

  public:
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef LegCabinStructure_T Structure_T;

    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef LegDate Parent_T;

    /** Define the list of children holder types. */
    typedef boost::fusion::map<
      boost::fusion::pair<Bucket, BucketHolder_T*>,
      boost::fusion::pair<SegmentCabin, SegmentCabinHolder_T*>
      > ChildrenHolderMap_T;
    // //////////////////////////////////////////////////////////////////

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    LegCabin (const Key_T& iKey, Structure_T&);
    /** Destructor. */
    ~LegCabin();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    LegCabin ();
    LegCabin (const LegCabin&);

  protected:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;
  };

}
#endif // __STDAIR_BOM_LEGCABIN_HPP

