#ifndef __STDAIR_BOM_AIRLINEFEATURESET_HPP
#define __STDAIR_BOM_AIRLINEFEATURESET_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/AirlineFeatureSetStructure.hpp>
#include <stdair/bom/AirlineFeatureSetContent.hpp>
#include <stdair/bom/AirlineFeatureSetTypes.hpp>
#include <stdair/bom/AirlineFeatureTypes.hpp>

namespace stdair {
  // Forward declarations.
  class FacBomContent;
  class AirlineFeature;
  struct AirlineFeatureSetKey_T;
  struct AirlineFeatureList_T;
  struct AirlineFeatureMap_T;
  
  /** Class representing the actual functional/business content
      for the Bom root. */
  class AirlineFeatureSet : public AirlineFeatureSetContent {
    friend class FacBomContent;
    
  public:
    // /////////////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef AirlineFeatureSetStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef AirlineFeatureSetKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef AirlineFeature ContentChild_T;
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

    /** Display the full context of the set of airline features. */
    const std::string display() const;
    
  public:
    // /////////// Getters /////////////
    /** Retrieve, if existing, the Airline features corresponding to the
        given airline code.
        <br>If not existing, return the NULL pointer. */
    const AirlineFeature* getAirlineFeature (const AirlineCode_T&) const;

    /** Get a AirlineFeatureList_T for iteration methods. */
    AirlineFeatureList_T getAirlineFeatureList () const;

    /** Get a AirlineFeatureMap_T for iteration methods. */
    AirlineFeatureMap_T getAirlineFeatureMap () const;

  private:     
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _bomRootStructure;
    }
    
  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    AirlineFeatureSet ();
    AirlineFeatureSet (const AirlineFeatureSet&);
    AirlineFeatureSet (const BomKey_T&, BomStructure_T&);
    /** Destructor. */
    virtual ~AirlineFeatureSet();

  private:
    // Attributes
    /** Reference structure. */
    BomStructure_T& _bomRootStructure;
  };

}
#endif // __STDAIR_BOM_AIRLINEFEATURESET_HPP
