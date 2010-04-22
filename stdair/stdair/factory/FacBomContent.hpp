#ifndef __STDAIR_FAC_FACBOMCONTENT_HPP
#define __STDAIR_FAC_FACBOMCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/DemandCharacteristicTypes.hpp>
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/Structure.hpp>
#include <stdair/factory/FacBomStructure.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  // Forward declarations
  template<typename BOM> struct BomList_T;
  class BomStructure;
  class BomContent;
  class EventQueue;
  struct OptimizerStruct_T;
  struct DemandCharacteristics;
  struct DemandDistribution;
  struct DemandStreamKey_T;
  
  /** Base class for Factory layer. */
  class FacBomContent {
    friend class FacSupervisor;
  public:
    /** Define the list (pool) of Bom objects. */
    typedef std::vector<BomContent*> BomContentPool_T;
    
  public:
    // //////////////////////////////////////////////////////////////////
    /** Create the root of the BOM tree, i.e., a pair of linked
        BomRootStructure and BomRoot objects. */
    template <typename BOM_ROOT>
    BOM_ROOT& create () {
      // Create the BOM root object.
      typename BOM_ROOT::Key_T lBomRootKey;
      BOM_ROOT& lBomRoot = createInternal<BOM_ROOT>(lBomRootKey);
      return lBomRoot;
    }

    // //////////////////////////////////////////////////////////////////
    /** Create a (child) content object, given a key.
        <br>A structure object is created, under the hood, with the given key.
        That structure object then gets a pointer on the content object. */
    template <typename CONTENT>
    CONTENT& create(const typename CONTENT::Key_T& ioKey){
      // Create the child structure object for the given key
      CONTENT& lBomContentChild = createInternal<CONTENT> (ioKey);
      return lBomContentChild;
    }

    // //////////////////////////////////////////////////////////////////
    /** Link a child content objet with his parent. */
    template <typename CHILD, typename PARENT>
    static void linkWithParent (CHILD& ioChild, PARENT& ioParent) {
           
      // Link both the parent and child structure objects
      const bool hasLinkBeenSuccessful = 
        FacBomStructure::linkParentWithChild (ioParent._structure,
                                              ioChild._structure);

      if (hasLinkBeenSuccessful == false) {
        throw ObjectLinkingException();
      }
    }

    // //////////////////////////////////////////////////////////////////
    /** Link two child content objects, the second one into the first one. */
    template <typename PARENT, typename CHILD>
    static void addObjectToTheDedicatedList (PARENT& ioParent,
                                             const CHILD& iChild) {
           
      // Link both the parent and child structure objects
      const bool hasLinkBeenSuccessful = 
        FacBomStructure::addObjectToTheDedicatedList (ioParent._structure,
                                                      iChild._structure);

      if (hasLinkBeenSuccessful == false) {
        throw ObjectLinkingException();
      }
    }

    // //////////////////////////////////////////////////////////////////
    /** Link two child content objects. */
    template <typename OBJECT1, typename OBJECT2>
    static void linkTwoObjects (OBJECT1& ioObject1, OBJECT2& ioObject2) {
      addObjectToTheDedicatedList (ioObject1, ioObject2);
      addObjectToTheDedicatedList (ioObject2, ioObject1);
    }

    // //////////////////////////////////////////////////////////////////
    /** Clone the children holder.*/
    template <typename PARENT, typename CHILD>    
    static void cloneChildrenHolder (PARENT& ioParent,
                                     const PARENT& iReferenceParent) {
      // Clone the list of children.
      typedef BomChildrenHolderImp<CHILD> CHILDREN_HOLDER_T;
      CHILDREN_HOLDER_T*& lChildrenHolder_ptr =
        boost::fusion::at_key<CHILD> (ioParent._structure._holderMap);
      lChildrenHolder_ptr =
        boost::fusion::at_key<CHILD> (iReferenceParent._structure._holderMap);
    }

  private:
    // //////////////////////////////////////////////////////////////////
    /** Create a content object, given a key.
        <br>A structure object is created, under the hood, with the given key.
        That structure object then gets a pointer on the content object. */
    template <typename CONTENT>
    CONTENT& createInternal (const typename CONTENT::Key_T& iKey) {
    
      // Create the structure/holder object
      typedef typename CONTENT::Structure_T STRUCTURE_T;
      STRUCTURE_T& lStructure =
        FacBomStructure::instance().create<STRUCTURE_T> ();

      // The created content object gets a constant reference on its
      // corresponding structure/holder object
      CONTENT* aContent_ptr = new CONTENT (iKey, lStructure);
      assert (aContent_ptr != NULL);

      // The new object is added to the pool of content objects
      _contentPool.push_back (aContent_ptr);

      // Link the structure/holder object with its corresponding content object
      lStructure._content = aContent_ptr;

      return *aContent_ptr;
    }
    
  public:
    /** Provide the unique instance.
        <br>The singleton is instantiated when first used.
        @return FacBomContent& */
    static FacBomContent& instance();
    
  private:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is content. */
    FacBomContent() {}
    /** Destructor. */
    virtual ~FacBomContent();
    /** Destroyed all the object instantiated by this factory. */
    void clean();
 
  private:
    /** The unique instance.*/
    static FacBomContent* _instance;

    /** List of instantiated Business Objects*/
    BomContentPool_T _contentPool;


  public:
    // //////////////////////////////////////////////////////////////////
    // /////////////////////// Dedicated factories //////////////////////
    // //////////////////////////////////////////////////////////////////
    /** Create a demand stream. */
    template <typename DEMAND_STREAM>
    DEMAND_STREAM& create
    (const DemandStreamKey_T& iKey,
     const ArrivalPatternCumulativeDistribution_T& iArrivalPattern,
     const POSProbabilityMassFunction_T& iPOSProbMass,
     const ChannelProbabilityMassFunction_T& iChannelProbMass,
     const TripTypeProbabilityMassFunction_T& iTripTypeProbMass,
     const StayDurationProbabilityMassFunction_T& iStayDurationProbMass,
     const FrequentFlyerProbabilityMassFunction_T& iFrequentFlyerProbMass,
     const PreferredDepartureTimeContinuousDistribution_T& iPreferredDepartureTimeContinuousDistribution,
     const WTPContinuousDistribution_T& iWTPContinuousDistribution,
     const ValueOfTimeContinuousDistribution_T& iValueOfTimeContinuousDistribution,
     const DemandDistribution& iDemandDistribution,
     const RandomSeed_T& iNumberOfRequestsSeed,
     const RandomSeed_T& iRequestDateTimeSeed,
     const RandomSeed_T& iDemandCharacteristicsSeed) {

      // Create the structure/holder object
      typedef typename DEMAND_STREAM::Structure_T DEMAND_STREAM_STRUCTURE_T;
      DEMAND_STREAM_STRUCTURE_T& lStructure =
        FacBomStructure::instance().create<typename DEMAND_STREAM::Structure_T> ();

      DEMAND_STREAM* aDemandStream_ptr =
        new DEMAND_STREAM (iKey, iArrivalPattern, iPOSProbMass,
                           iChannelProbMass, iTripTypeProbMass,
                           iStayDurationProbMass, iFrequentFlyerProbMass,
                           iPreferredDepartureTimeContinuousDistribution,
                           iWTPContinuousDistribution,
                           iValueOfTimeContinuousDistribution,
                           iDemandDistribution,
                           iNumberOfRequestsSeed, iRequestDateTimeSeed,
                           iDemandCharacteristicsSeed, lStructure);
      assert (aDemandStream_ptr != NULL);

      // The new object is added to the pool of content objects
      _contentPool.push_back (aDemandStream_ptr);
      // Link the structure/holder object with its corresponding content object
      lStructure._content = aDemandStream_ptr;
      
      return *aDemandStream_ptr;
    }

  };
}
#endif // __STDAIR_FAC_FACBOMCONTENT_HPP
