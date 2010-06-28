#ifndef __STDAIR_BOM_BUCKET_HPP
#define __STDAIR_BOM_BUCKET_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost Fusion
#include <boost/version.hpp>
#if BOOST_VERSION >= 103500
#include <boost/fusion/include/map.hpp>
#else // BOOST_VERSION >= 103500
#include <boost/mpl/map.hpp>
#endif // BOOST_VERSION >= 103500
// StdAir 
#include <stdair/bom/BucketContent.hpp>
#include <stdair/bom/BucketTypes.hpp>

namespace stdair {
  // Forward declarations.
  class LegCabin;
  
  /** Class representing the actual functional/business content
      for the Bom root. */
  class Bucket : public BucketContent {
    friend class FacBomContent;
    
  public:
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef BucketStructure_T Structure_T;

    /** Definition allowing to retrieve the associated parent. */
    typedef LegCabin Parent_T;

    /** Definition allowing to retrieve the map/multimap type using by
        BomChildrenHolder. */
    typedef std::map<const MapKey_T, const Structure_T*> Map_T;
        
    /** Define the list of children holder types. */
#if BOOST_VERSION >= 103500
    typedef boost::fusion::map< > ChildrenHolderMap_T;
#else // BOOST_VERSION >= 103500
    typedef boost::mpl::map< > ChildrenHolderMap_T;
#endif // BOOST_VERSION >= 103500
    // //////////////////////////////////////////////////////////////////
    
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
    const std::string describeKey() const;

  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    Bucket (const Key_T& iKey, Structure_T& ioStructure);
    /** Destructor. */
    ~Bucket();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    Bucket ();
    Bucket (const Bucket&);

  private:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;

  };

}
#endif // __STDAIR_BOM_BUCKET_HPP
