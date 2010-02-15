#ifndef __STDAIR_BOM_AIRLINEFEATURE_HPP
#define __STDAIR_BOM_AIRLINEFEATURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// STDAIR 
#include <stdair/bom/AirlineFeatureSet.hpp>
#include <stdair/bom/AirlineFeatureStructure.hpp>
#include <stdair/bom/AirlineFeatureContent.hpp>
#include <stdair/bom/AirlineFeatureSetTypes.hpp>
#include <stdair/bom/AirlineFeatureTypes.hpp>

namespace stdair {

  // Forward declarations
  struct AirlineFeatureKey_T;

  
  /** Class representing the actual functional/business content for a
      segment-cabin. */
  class AirlineFeature : public AirlineFeatureContent {
    friend class FacBomContent;

    
  public:
    // //////////// Type definitions //////////////
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef AirlineFeatureSet Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef AirlineFeatureStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef AirlineFeatureKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef AirlineFeature ContentChild_T;

    
  public:
    // //////////// Setters /////////////
    /** Intialisation method. */
    void init (const ForecasterMode_T&, const HistoricalDataLimit_T&,
               const OptimizerStruct_T&, const ControlMode_T&);

    
  public:
    // /////////// Display support methods /////////////
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

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const;

    /** Give a description of the structure (for display purposes). */
    const std::string describe() const;

    
  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _airlineFeatureStructure;
    }

    
  protected:
    // ///////////////// Constructors and destructors /////////////////
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    AirlineFeature ();
    AirlineFeature (const AirlineFeature&);
    AirlineFeature (const BomKey_T&, BomStructure_T&);

    /** Destructor. */
    virtual ~AirlineFeature();

    
  protected:
    // ////////////////////// Attributes ///////////////////////////
    /** Reference structure. */
    BomStructure_T& _airlineFeatureStructure;
  };

}
#endif // __STDAIR_BOM_AIRLINEFEATURE_HPP

