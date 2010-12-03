#ifndef __STDAIR_BOM_BUCKET_HPP
#define __STDAIR_BOM_BUCKET_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <iosfwd>
// StdAir 
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/BomAbstract.hpp>
#include <stdair/bom/BucketKey.hpp>
#include <stdair/bom/BucketTypes.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline booking class. */
  class Bucket : public BomAbstract {
    template <typename BOM> friend class FacBom;
    friend class FacBomManager;
    
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BucketKey Key_T;

  public:
    // /////////// Getters ////////////
    /** Get the booking class key. */
    const Key_T& getKey() const { return _key; }

    /** Get the parent object. */
    BomAbstract* const getParent() const { return _parent; }

    /** Get the map of children holders. */
    const HolderMap_T& getHolderMap() const { return _holderMap; }

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const { ioOut << toString(); }

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn) { }

   /** Get the serialised version of the Business Object. */
    std::string toString() const;
    
    /** Get a string describing the  key. */
    const std::string describeKey() const { return _key.toString(); }
    
  protected:
    /** Default constructors. */
    Bucket (const Key_T&);
    Bucket (const Bucket&);
    /** Destructor. */
    ~Bucket();

  public:
    // Attributes
    Key_T _key;
    BomAbstract* _parent;
    HolderMap_T _holderMap;
    // test AIRINV
    stdair::Yield_T _yieldRangeUpperValue;
    stdair::CabinCapacity_T _availability;
    stdair::NbOfSeats_T _nbOfSeats;
    stdair::SeatIndex_T _seatIndex;
  };

}
#endif // __STDAIR_BOM_BUCKET_HPP

