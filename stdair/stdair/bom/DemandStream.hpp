#ifndef __STDAIR_BOM_DEMANDSTREAM_HPP
#define __STDAIR_BOM_DEMANDSTREAM_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost
#include <boost/shared_ptr.hpp>
// STL
#include <iosfwd>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/DemandStreamStructure.hpp>
#include <stdair/bom/DemandStreamContent.hpp>
#include <stdair/bom/BomRootTypes.hpp>
#include <stdair/bom/DemandStreamTypes.hpp>

namespace stdair {

  // Forward declarations
  struct DemandStreamKey_T;
  
  /** Class modeling a demand stream. */
  class DemandStream  : public DemandStreamContent {
    friend class FacBomContent;
    
  public:
    // //////////// Type definitions //////////////
    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef BomRoot Parent_T;

    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef DemandStreamStructure_T BomStructure_T;

    /** Definition allowing to retrieve the associated BOM key type. */
    typedef DemandStreamKey_T BomKey_T;

    /** Definition allowing to retrieve the associated 
         BOM content child type. */
    typedef DemandStream ContentChild_T;

  private:
    /** Retrieve the BOM structure object. */
    BomStructure_T& getBomStructure () {
      return _demandStreamStructure;
    }
    
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


  protected:
    // ////////// Constructors and destructors /////////
    /** Constructor by default */
    DemandStream (const BomKey_T&,
                  const ArrivalPatternCumulativeDistribution_T&,
                  const POSProbabilityMassFunction_T&,
                  const ChannelProbabilityMassFunction_T&,
                  const TripTypeProbabilityMassFunction_T&,
                  const StayDurationProbabilityMassFunction_T&,
                  const FrequentFlyerProbabilityMassFunction_T&,
                  const PreferredDepartureTimeContinuousDistribution_T&,
                  const WTPContinuousDistribution_T&,
                  const ValueOfTimeContinuousDistribution_T&,
                  const DemandDistribution&,
                  const RandomSeed_T& iNumberOfRequestsSeed,
                  const RandomSeed_T& iRequestDateTimeSeed,
                  const RandomSeed_T& iDemandCharacteristicsSeed,
                  BomStructure_T&);
    /** Default constructors. */
    DemandStream ();
    DemandStream (const DemandStream&);
    /** Initialization. */
    void init();
    /** Destructor. */
    ~DemandStream ();

    
  protected:
    // ////////// Attributes //////////
    /** Reference structure. */
    BomStructure_T& _demandStreamStructure;
  };

}
#endif // __STDAIR_BOM_DEMANDSTREAM_HPP
