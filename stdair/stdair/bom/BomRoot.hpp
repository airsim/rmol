#ifndef __STDAIR_BOM_BOMROOT_HPP
#define __STDAIR_BOM_BOMROOT_HPP

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
#include <stdair/bom/BomRootContent.hpp>
#include <stdair/bom/BomRootTypes.hpp>
#include <stdair/bom/InventoryTypes.hpp>
#include <stdair/bom/ReachableUniverseTypes.hpp>
#include <stdair/bom/DemandStreamTypes.hpp>
#include <stdair/bom/AirlineFeatureTypes.hpp>
#include <stdair/bom/YieldStoreTypes.hpp>

namespace stdair {
  
  /** Class representing the actual functional/business content
      for the Bom root. */
  class BomRoot : public BomRootContent {
    friend class FacBomContent;

    // //////////////////////////////////////////////////////////////////
    // Type definitions, compulsary for the STDAIR library to work correctly
    // //////////////////////////////////////////////////////////////////
    /** The following types must be defined:
        <ul>
          <li>Structure_T: Type of the corresponding BOM class within
          the stdair namespace</li>
          <li>Parent_T: Type corresponding to the parent BOM
          class within that namespace (e.g., AIRSCHED here)</li>
          <li>Map_T: Type corresponding to the map/multimap type using by the
          corresponding BomChildrenHolder
          <li>ChildrenHolderMap_T: The map between the type of children and 
          a pointer to the bom holder of this type (e.g., AIRSCHED here).
          All the pointers to the bom holder should be initialised to
          NULL in the init() function.</li>
        </ul>
        <br><br>
        Note that the parent type of BomRoot is its own type.
    */
    
  public:
    // //////////////////////////////////////////////////////////////////
    /** Definition allowing to retrieve the associated BOM structure type. */
    typedef BomRootStructure_T Structure_T;

    /** Definition allowing to retrieve the parent type. */
    typedef BomRoot Parent_T;

    /** Definition allowing to retrieve the map/multimap type using by
        BomChildrenHolder. */
    typedef std::map<const MapKey_T, const Structure_T*> Map_T;

    /** Define the list of children holder types. */
#if BOOST_VERSION >= 103500
    typedef boost::fusion::map<
      boost::fusion::pair<Inventory, InventoryHolder_T*>,
      boost::fusion::pair<ReachableUniverse, ReachableUniverseHolder_T*>,
      boost::fusion::pair<AirlineFeature, AirlineFeatureHolder_T*>,
      boost::fusion::pair<DemandStream, DemandStreamHolder_T*>,
      boost::fusion::pair<YieldStore, YieldStoreHolder_T*>
      > ChildrenHolderMap_T;
#else // BOOST_VERSION >= 103500
    typedef boost::mpl::map< > ChildrenHolderMap_T;
#endif // BOOST_VERSION >= 103500
    // //////////////////////////////////////////////////////////////////

  public:
    // /////////// Getters /////////////
    /** Get a list or map of a children type for iteration methods. */
    InventoryList_T getInventoryList () const;
    InventoryMap_T getInventoryMap () const;
    ReachableUniverseList_T getReachableUniverseList () const;
    ReachableUniverseMap_T getReachableUniverseMap () const;
    DemandStreamList_T getDemandStreamList () const;
    DemandStreamMap_T getDemandStreamMap () const;
    AirlineFeatureList_T getAirlineFeatureList () const;
    AirlineFeatureMap_T getAirlineFeatureMap () const;
    YieldStoreList_T getYieldStoreList () const;
    YieldStoreMap_T getYieldStoreMap () const;

    /** Retrieve, if existing, the Inventory corresponding to the
        given airline code (Inventory key).
        <br>If not existing, return the NULL pointer. */
    Inventory* getInventory (const AirlineCode_T&) const;

    /** Retrieve, if existing, the ReachableUniverse corresponding to the
        given airport.
        <br>If not existing, return the NULL pointer. */
    ReachableUniverse* getReachableUniverse (const AirportCode_T&) const;

    /** Retrieve, if existing, the YieldStore corresponding to the
        given airline code (YieldStore key).
        <br>If not existing, return the NULL pointer. */
    YieldStore* getYieldStore (const AirlineCode_T&) const;

    /** Retrieve, if existing, the Airline features corresponding to the
        given airline code.
        <br>If not existing, return the NULL pointer. */
    AirlineFeature* getAirlineFeature (const AirlineCode_T&) const;
    
    /** Retrieve the DemandStream which corresponds to the given key. */
    DemandStream& getDemandStream (const DemandStreamKeyStr_T&) const;

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
    
  protected:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    BomRoot (const Key_T&, Structure_T&);
    /** Destructor. */
     ~BomRoot();
    /** Initialise all the pointers of children holder to NULL. */
    void init();
    /** Default constructors. */
    BomRoot ();
    BomRoot (const BomRoot&);

  private:
    // Attributes
    /** Reference structure. */
    Structure_T& _structure;
  };

}
#endif // __STDAIR_BOM_BOMROOT_HPP
