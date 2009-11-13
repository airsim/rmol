#ifndef __STDAIR_FAC_FACBOMCONTENT_HPP
#define __STDAIR_FAC_FACBOMCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
// MPL
#include <boost/mpl/vector.hpp>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomStructure.hpp>
#include <stdair/factory/FacBomStructure.hpp>

namespace stdair {

  // Forward declarations
  template<typename BOM> struct BomList_T;
  class BomStructure;
  class BomContent;
  struct OptimizerStruct_T;
  
  /** Base class for Factory layer. */
  class FacBomContent {
    friend class FacSupervisor;
  public:
    /** Define the list (pool) of Bom objects. */
    typedef std::vector<BomContent*> BomContentPool_T;
  public:
    /** Create the root of the BOM tree, i.e., a pair of linked
        BomRootStructure and BomRoot objects. */
    template <typename BOM_ROOT>
    BOM_ROOT& create () {
      // Define the typename for BomRootKey.
      typedef typename BOM_ROOT::BomKey_T BOM_ROOT_KEY_T;
      // Create the BOM root object.
      BOM_ROOT_KEY_T lBomRootKey;
      BOM_ROOT& lBomRoot = createInternal<BOM_ROOT>(lBomRootKey);
      return lBomRoot;
    }
    
    /** Create a (child) content object, given a key.
        <br>A structure object is created, under the hood, with the given key.
        That structure object then gets a pointer on the content object. */
    template <typename BOM_CONTENT_CHILD>
    BOM_CONTENT_CHILD& create (typename BOM_CONTENT_CHILD::Parent_T& ioContentParent, typename BOM_CONTENT_CHILD::BomKey_T& ioKey) {

      // Define the parent key type.
      typedef typename BOM_CONTENT_CHILD::Parent_T::BomKey_T ParentKey_T;

      // Finish the construction of the child key by setting its parent.
      const ParentKey_T& lParentKey = ioContentParent.getKey();
      ioKey.setParentKey (lParentKey);
      
      // Create the child structure object for the given key
      BOM_CONTENT_CHILD& lBomContentChild =
        createInternal<BOM_CONTENT_CHILD> (ioKey);

      // Retrieve the child structure object
      typename BOM_CONTENT_CHILD::BomStructure_T& lBomStructureChild =
        lBomContentChild.getBomStructure ();

      // Type for the parent Bom content
      typedef typename BOM_CONTENT_CHILD::Parent_T PARENT_CONTENT_T;
      
      // Type for the parent Bom structure
      typedef typename PARENT_CONTENT_T::BomStructure_T PARENT_STRUCTURE_T;
      
      // Retrieve the parent structure object
      PARENT_STRUCTURE_T& lBomStructureParent =
        ioContentParent.getBomStructure ();
           
      // Type for the child Bom structure
      typedef typename BOM_CONTENT_CHILD::BomStructure_T CHILD_STRUCTURE_T;
      
      // Link both the parent and child structure objects
      const bool hasLinkBeenSuccessful = FacBomStructure::
        linkBomParentWithBomChild<CHILD_STRUCTURE_T> (lBomStructureParent,
                                                      lBomStructureChild);

      if (hasLinkBeenSuccessful == false) {
        throw new MemoryAllocationException();
      }

      return lBomContentChild;
    }

  private:
    /** Create a content object, given a key.
        <br>A structure object is created, under the hood, with the given key.
        That structure object then gets a pointer on the content object. */
    template <typename BOM_CONTENT>
    BOM_CONTENT& createInternal (const typename BOM_CONTENT::BomKey_T& iKey) {
    
      // Create the structure/holder object
      typedef typename BOM_CONTENT::BomStructure_T BOM_STRUCTURE_T;
      BOM_STRUCTURE_T& lBomStructure =
        FacBomStructure::instance().create<BOM_STRUCTURE_T> ();

      // The created flight-date content (BomContent) object gets a constant
      // reference on its corresponding flight-date structure/holder object
      BOM_CONTENT* aBomContent_ptr = new BOM_CONTENT (iKey, lBomStructure);
      assert (aBomContent_ptr != NULL);

      // The new object is added to the pool of content objects
      _contentPool.push_back (aBomContent_ptr);

      // Link the structure/holder object with its corresponding content object
      setContent<BOM_STRUCTURE_T, BOM_CONTENT> (lBomStructure, *aBomContent_ptr);

      return *aBomContent_ptr;
    }

    // //////////////////////////////////////////////////////////////////
    // Section reserved for the building the direct accesses such as
    // booking class holder directly in inventory or flight-date, ect.
    // //////////////////////////////////////////////////////////////////
  public:
    template <typename BOM_ROOT>
    static void createDirectAccesses (const BOM_ROOT& iBomRoot) {
      // Retrieve the inventory type.
      typedef typename BOM_ROOT::ContentChild_T INVENTORY_T;
      // Define the list of inventories.
      typedef BomList_T<INVENTORY_T> INVENTORY_LIST_T;

      // Browse the BomRoot and build direct accesses within each inventory.
      const INVENTORY_LIST_T lInventoryList = iBomRoot.getInventoryList();
      for (typename INVENTORY_LIST_T::iterator itInv = lInventoryList.begin();
           itInv != lInventoryList.end(); ++itInv) {
        INVENTORY_T& lCurrentInv = *itInv;

        createDirectAccessesWithinInventory (lCurrentInv);
      }
    }

  private:
    /** Create a holder of all booking classes within the given inventory. */
    template <typename INVENTORY>
    static void createDirectAccessesWithinInventory(const INVENTORY& iInventory){
      // Retrieve the flight-date type.
      typedef typename INVENTORY::ContentChild_T FLIGHT_DATE_T;
      // Define the list of flight-dates.
      typedef BomList_T<FLIGHT_DATE_T> FLIGHT_DATE_LIST_T;
      // Retrieve the booking class type.
      typedef typename INVENTORY::BookingClassContent_T BOOKING_CLASS_T;
      // Define the bom holder of booking classes.
      typedef BomChildrenHolderImp<BOOKING_CLASS_T> BOOKING_CLASS_HOLDER_T;
      
      // Initialize the booking class holder within the inventory.
      BOOKING_CLASS_HOLDER_T& lBookingClassHolder =
        FacBomStructure::instance().createBomHolder<BOOKING_CLASS_T> ();
      iInventory._inventoryStructure.setBookingClassHolder(lBookingClassHolder);
      
      // Browse the inventory and build direct accesses within each
      // flight-date, then build the booking class holder within the
      // inventory.
      const FLIGHT_DATE_LIST_T lFlightDateList = iInventory.getFlightDateList();
      for (typename FLIGHT_DATE_LIST_T::iterator itFlightDate =
             lFlightDateList.begin(); itFlightDate != lFlightDateList.end();
           ++itFlightDate) {
        FLIGHT_DATE_T& lCurrentFlightDate = *itFlightDate;
        createDirectAccessesWithinFlightDate (lCurrentFlightDate);
      }
    }

    /** Create the direct acceeses within the given flight-date, and, at the
        same time, build the class holder for the parent inventory. */
    template <typename FLIGHT_DATE>
    static void createDirectAccessesWithinFlightDate (const FLIGHT_DATE& iFlightDate) {
      // Retrieve the booking class type.
      typedef typename FLIGHT_DATE::BookingClassContent_T BOOKING_CLASS_T;
      // Define the bom holder of booking classes.
      typedef BomChildrenHolderImp<BOOKING_CLASS_T> BOOKING_CLASS_HOLDER_T;
    
      // Initialize the booking class holder within the flight-date.
      BOOKING_CLASS_HOLDER_T& lBookingClassHolder =
        FacBomStructure::instance().createBomHolder<BOOKING_CLASS_T> ();
      iFlightDate._flightDateStructure.setBookingClassHolder(lBookingClassHolder);
      // Retrieve the leg-date type.
      typedef typename FLIGHT_DATE::SecondContentChild_T LEG_DATE_T;
      // Define the holder of leg-dates.
      typedef BomChildrenHolderImp<LEG_DATE_T> LEG_DATE_HOLDER_T;
      // Retrieve the leg-date key type.
      typedef typename LEG_DATE_T::BomKey_T LEG_DATE_KEY_T;
      // Retrieve the segment-date type.
      typedef typename FLIGHT_DATE::ContentChild_T SEGMENT_DATE_T;
      // Define the list of segment-dates.
      typedef BomList_T<SEGMENT_DATE_T> SEGMENT_DATE_LIST_T;
      SEGMENT_DATE_LIST_T lSegmentDateList = iFlightDate.getSegmentDateList();
      for (typename SEGMENT_DATE_LIST_T::iterator itSegmentDate =
             lSegmentDateList.begin();
           itSegmentDate != lSegmentDateList.end(); ++itSegmentDate) {
        SEGMENT_DATE_T& lCurrentSegmentDate = *itSegmentDate;

        // Initialize the leg-date holder within the segment-date.
        LEG_DATE_HOLDER_T& lLegDateHolder =
          FacBomStructure::instance().createBomHolder<LEG_DATE_T> ();
        lCurrentSegmentDate._segmentDateStructure.setLegDateHolder(lLegDateHolder);

        const AirportCode_T& lBoardPoint =
          lCurrentSegmentDate.getBoardPoint();
        AirportCode_T currentBoardPoint = lBoardPoint;
        const AirportCode_T& lOffPoint = lCurrentSegmentDate.getOffPoint();
        AirportCode_T currentOffPoint = lBoardPoint;
        
        // Add a sanity check so as to ensure that the loop stops. If
        // there are more than MAXIMUM_NUMBER_OF_LEGS legs, there is
        // an issue somewhere in the code (not in the parser, as the
        // segments are derived from the legs thanks to the
        // FlightPeriodStruct::buildSegments() method).
        unsigned short i = 1;
        while (currentOffPoint != lOffPoint
               && i <= MAXIMUM_NUMBER_OF_LEGS_IN_FLIGHT) {
          // Retrieve the (unique) LegDate getting that Board Point
          const LEG_DATE_KEY_T lLegDateKey (currentOffPoint);
          LEG_DATE_T* lLegDate_ptr = iFlightDate.getLegDate (lLegDateKey);
          assert (lLegDate_ptr != NULL);

          // Link the SegmentDate and LegDate together
          initLinkSegmentDateWithLegDate<SEGMENT_DATE_T> (lCurrentSegmentDate, *lLegDate_ptr);
          
          // Prepare the next iteration
          currentBoardPoint = lLegDate_ptr->getOffPoint();
          currentOffPoint = lLegDate_ptr->getOffPoint();
          ++i;
        }
        assert (i <= MAXIMUM_NUMBER_OF_LEGS_IN_FLIGHT);

        // Create the routing for the leg- and segment-cabins.
        // At the same time, set the SegmentDate attributes derived from
        // its routing legs (e.g., board and off dates).
        createDirectAccessesWithinSegmentDate (lCurrentSegmentDate);
      }             
    }

    /** Create the direct acceeses within the given segment-date, and, at the
        same time, build the class holder for the corresponding flight-date
        and inventory. */
    template <typename SEGMENT_DATE>
    static void createDirectAccessesWithinSegmentDate (const SEGMENT_DATE& iSegmentDate) {
      // Retrieve the segment-cabin type.
      typedef typename SEGMENT_DATE::ContentChild_T SEGMENT_CABIN_T;
      // Define the list of sement-cabin.
      typedef BomList_T<SEGMENT_CABIN_T> SEGMENT_CABIN_LIST_T;
      // Retrieve the leg-date type.
      typedef typename SEGMENT_DATE::LegDateContent_T LEG_DATE_T;
      // Define the list of leg-date.
      typedef BomList_T<LEG_DATE_T> LEG_DATE_LIST_T;
      // Retrieve the leg-cabin type.
      typedef typename LEG_DATE_T::ContentChild_T LEG_CABIN_T;
      // Define the leg-cabin holder.
      typedef BomChildrenHolderImp<LEG_CABIN_T> LEG_CABIN_HOLDER_T;
      // Retrieve the type of leg-cabin key.
      typedef typename LEG_CABIN_T::BomKey_T LEG_CABIN_KEY_T;
      
      // Browse the segment-cabin list.
      const SEGMENT_CABIN_LIST_T lSegmentCabinList =
        iSegmentDate.getSegmentCabinList();
      for (typename SEGMENT_CABIN_LIST_T::iterator itSegmentCabin =
             lSegmentCabinList.begin();
           itSegmentCabin != lSegmentCabinList.end(); ++itSegmentCabin) {
        SEGMENT_CABIN_T& lSegmentCabin = *itSegmentCabin;

        // Initialize the leg-cabin holder for the current segment-cabin.
        LEG_CABIN_HOLDER_T& lLegCabinHolder = FacBomStructure::
          instance().createBomHolder<LEG_CABIN_T> ();
        lSegmentCabin._segmentCabinStructure.setLegCabinHolder (lLegCabinHolder);
        
        // Iterate on the routing legs
        const LEG_DATE_LIST_T& lLegDateList = iSegmentDate.getLegDateList();
        for (typename LEG_DATE_LIST_T::iterator itLegDate =
               lLegDateList.begin();
             itLegDate != lLegDateList.end(); ++itLegDate) {
          const LEG_DATE_T& lLegDate = *itLegDate;

          // Retrieve the LegCabin getting the same class of service
          // (cabin code) as the SegmentCabin.
          const CabinCode_T& lCabinCode = lSegmentCabin.getCabinCode();
          const LEG_CABIN_KEY_T lLegCabinKey (lCabinCode);
      
          LEG_CABIN_T* lLegCabin_ptr = lLegDate.getLegCabin (lLegCabinKey);

          // In fact, the following assertion corresponds to the assumption
          // that the cabins are the same on the segments AND on their routing
          // legs. For some actual airline, that is not always true. If needed,
          // we may implement the cabin mapping feature.
          /*
          if (lLegCabin_ptr == NULL) {
            STDAIR_LOG_ERROR ("The cabin of the Segment: "
                              << lSegmentCabin._key.describe()
                              << " can not be found on the routing Legs."
                              << " The mapping of Segment-Cabins onto "
                              << "distinct Leg-Cabins is a feature not "
                              << "supported by LATUS.");
          }
          */
          assert (lLegCabin_ptr != NULL);
          
          // Link the SegmentCabin and LegCabin together
          initLinkSegmentCabinWithLegCabin<SEGMENT_CABIN_T> (lSegmentCabin, *lLegCabin_ptr);

          // Build the class holders for the corresponding flight-date and
          // inventory.
          buildBookingClassHolders (lSegmentCabin);
        }
      }
    }

    /** Build the booking class holders of the corresponding inventory
        and flight-date of the given segment-cabin. */
    template <typename SEGMENT_CABIN>
    static void buildBookingClassHolders (const SEGMENT_CABIN& iSegmentCabin) {
      // Retrieve the flight-date structure type.
      typedef typename SEGMENT_CABIN::Parent_T::Parent_T::BomStructure_T FLIGHT_DATE_STRUCTURE_T;
      // Retrieve the booking class type.
      typedef typename SEGMENT_CABIN::ContentChild_T BOOKING_CLASS_T;

      FLIGHT_DATE_STRUCTURE_T& lFDStructure =
        iSegmentCabin._segmentCabinStructure.getSegmentDateStructure().
        getFlightDateStructure();

      // Define the holder of booking classes.
      typedef BomChildrenHolderImp<BOOKING_CLASS_T> BOOKING_CLASS_HOLDER_T;

      // Retrieve the booking class holders of the flight-date and the
      // inventory.
      BOOKING_CLASS_HOLDER_T& lFDBookingClassHolder =
        lFDStructure.getBookingClassHolder();
      BOOKING_CLASS_HOLDER_T& lInvBookingClassHolder =
        lFDStructure.getInventoryStructure().getBookingClassHolder();

      // Define the list of booking classes.
      typedef BomList_T<BOOKING_CLASS_T> BOOKING_CLASS_LIST_T;
      BOOKING_CLASS_LIST_T lBookingClassList=iSegmentCabin.getBookingClassList();
      for (typename BOOKING_CLASS_LIST_T::iterator itBookingClass =
             lBookingClassList.begin();
           itBookingClass != lBookingClassList.end(); ++itBookingClass) {
        BOOKING_CLASS_T& lBookingClass = *itBookingClass;

       //  bool addingSucceeded = FacBomStructure::
//           addFullBomObjecdToBomHolder<BOOKING_CLASS_T> (lFDBookingClassHolder,
//                                                         lBookingClass);
//         assert (addingSucceeded == true);
//         addingSucceeded = FacBomStructure::
//           addFullBomObjecdToBomHolder<BOOKING_CLASS_T> (lInvBookingClassHolder,
//                                                         lBookingClass);
//         assert (addingSucceeded == true);
      }
    }
    
    /** Build the link between the given segment-date and the given leg-date. */
    template <typename SEGMENT_DATE>
    static void initLinkSegmentDateWithLegDate (SEGMENT_DATE& ioSegmentDate,
                                                typename SEGMENT_DATE::LegDateContent_T& ioLegDate) {
      // Retrieve the leg-date type.
      typedef typename SEGMENT_DATE::LegDateContent_T LEG_DATE_T;
      // Define the segment-date holder type.
      typedef BomChildrenHolderImp<SEGMENT_DATE> SEGMENT_DATE_HOLDER_T;
      // Define the leg-date holder type.
      typedef BomChildrenHolderImp<LEG_DATE_T> LEG_DATE_HOLDER_T;

      LEG_DATE_HOLDER_T* lLegDateHolder_ptr =
        ioSegmentDate._segmentDateStructure._legDateHolder;
      assert (lLegDateHolder_ptr != NULL);

     //  bool addingSucceeded = FacBomStructure::
//         addBomObjecdToBomHolder<LEG_DATE_T> (*lLegDateHolder_ptr, ioLegDate);
//       assert (addingSucceeded == true);
      
      SEGMENT_DATE_HOLDER_T* lSegmentDateHolder_ptr =
        ioLegDate._legDateStructure._segmentDateHolder;
      if (lSegmentDateHolder_ptr == NULL) {
        lSegmentDateHolder_ptr = &FacBomStructure::
          instance().createBomHolder<SEGMENT_DATE> ();
      }
      // addingSucceeded = FacBomStructure::
//         addBomObjecdToBomHolder<SEGMENT_DATE> (*lSegmentDateHolder_ptr,
//                                                ioSegmentDate);
//       assert (addingSucceeded == true);
    }

    /** Build the link between the given segment-cabin and the given
        leg-cabin. */
    template <typename SEGMENT_CABIN>
    static void initLinkSegmentCabinWithLegCabin (SEGMENT_CABIN& ioSegmentCabin,
                                                  typename SEGMENT_CABIN::LegCabinContent_T& ioLegCabin) {
      // Retrieve the leg-cabin type.
      typedef typename SEGMENT_CABIN::LegCabinContent_T LEG_CABIN_T;
      // Define the segment-cabin holder type.
      typedef BomChildrenHolderImp<SEGMENT_CABIN> SEGMENT_CABIN_HOLDER_T;
      // Define the leg-cabin holder type.
      typedef BomChildrenHolderImp<LEG_CABIN_T> LEG_CABIN_HOLDER_T;

      LEG_CABIN_HOLDER_T* lLegCabinHolder_ptr =
        ioSegmentCabin._segmentCabinStructure._legCabinHolder;
      assert (lLegCabinHolder_ptr != NULL);

     //  bool addingSucceeded = FacBomStructure::
//         addBomObjecdToBomHolder<LEG_CABIN_T>(*lLegCabinHolder_ptr, ioLegCabin);
//       assert (addingSucceeded == true);
      
      SEGMENT_CABIN_HOLDER_T* lSegmentCabinHolder_ptr =
        ioLegCabin._legCabinStructure._segmentCabinHolder;
      if (lSegmentCabinHolder_ptr == NULL) {
        lSegmentCabinHolder_ptr = &FacBomStructure::
          instance().createBomHolder<SEGMENT_CABIN> ();
      }
     //  addingSucceeded = FacBomStructure::
//         addBomObjecdToBomHolder<SEGMENT_CABIN> (*lSegmentCabinHolder_ptr,
//                                                 ioSegmentCabin);
//       assert (addingSucceeded == true);
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
    /** Link the structure/holder object with its corresponding content
        object. */
    template<typename BOM_STRUCTURE, typename BOM_CONTENT>
    static void setContent (BOM_STRUCTURE& ioBomStructure,
                            BOM_CONTENT& ioBomContent) {
      ioBomStructure._content = &ioBomContent;
    }
    
  private:
    /** The unique instance.*/
    static FacBomContent* _instance;
    
  private:
    /** List of instantiated Business Objects*/
    BomContentPool_T _contentPool;
  };
}
#endif // __STDAIR_FAC_FACBOMCONTENT_HPP
