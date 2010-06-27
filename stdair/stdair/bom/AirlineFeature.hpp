#ifndef __STDAIR_BOM_AIRLINEFEATURE_HPP
#define __STDAIR_BOM_AIRLINEFEATURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost Fusion
#include <boost/fusion/include/map.hpp>
// StdAir 
#include <stdair/bom/AirlineFeatureContent.hpp>
#include <stdair/bom/AirlineFeatureTypes.hpp>

namespace stdair {
  // Forward declarations
  class BomRoot;

  /** Class representing the actual functional/business content for a
      segment-cabin. */
  class AirlineFeature : public AirlineFeatureContent {
    friend class FacBomContent;

  public:
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef AirlineFeatureStructure_T Structure_T;

    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef BomRoot Parent_T;

    /** Definition allowing to retrieve the map/multimap type using by
        BomChildrenHolder. */
    typedef std::map<const MapKey_T, const Structure_T*> Map_T;

    /** Define the list of children holder types. */
    typedef boost::fusion::map< > ChildrenHolderMap_T;
    // //////////////////////////////////////////////////////////////////

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

    /** Give a description of the structure (for display purposes). */
    const std::string describe() const;
    
  protected:
    // ///////////////// Constructors and destructors /////////////////
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    AirlineFeature (const Key_T&, Structure_T&);
    /** Destructor. */
    ~AirlineFeature();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    AirlineFeature ();
    AirlineFeature (const AirlineFeature&);

    
  protected:
    // ////////////////////// Attributes ///////////////////////////
    /** Reference structure. */
    Structure_T& _structure;
  };

}
#endif // __STDAIR_BOM_AIRLINEFEATURE_HPP

