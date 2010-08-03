#ifndef __STDAIR_BOM_DEMANDSTREAM_HPP
#define __STDAIR_BOM_DEMANDSTREAM_HPP

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
#include <stdair/bom/DemandStreamContent.hpp>
#include <stdair/bom/DemandStreamTypes.hpp>

namespace stdair {
  // Forward declarations.
  class BomRoot;
  
  /** Class modeling a demand stream. */
  class DemandStream  : public DemandStreamContent {
    friend class FacBomContent;
    
  public:
    // //////////////////////////////////////////////////////////////////
    // See the explanations, within the BomRoot class, for all
    // the types which require to be specified below
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef DemandStreamStructure_T Structure_T;

    /** Definition allowing to retrieve the associated parent
        BOM content type. */
    typedef BomRoot Parent_T;

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
    const std::string describeKey() const { return _key.toString(); }

  public:
    // ////////// Business Methods //////////
    /** Reset all the contexts of the demand stream. */
    void reset ();
    
  protected:
    // ////////// Constructors and destructors /////////
    /** Constructor by default */
    DemandStream (const Key_T&,
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
                  Structure_T&);
    /** Destructor. */
    ~DemandStream ();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    DemandStream ();
    DemandStream (const DemandStream&);

    
  protected:
    // ////////// Attributes //////////
    /** Reference structure. */
    Structure_T& _structure;
  };

}
#endif // __STDAIR_BOM_DEMANDSTREAM_HPP
