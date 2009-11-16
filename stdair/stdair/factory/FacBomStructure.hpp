#ifndef __STDAIR_FAC_FACBOMSTRUCTURE_HPP
#define __STDAIR_FAC_FACBOMSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <string>
#include <vector>
#include <iostream>
// MPL
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/type_traits/is_same.hpp>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/BomStopContent.hpp>

namespace stdair {

  // Forward declarations
  class BomContent;
  class BomStructure;
  template <typename BOM_CONTENT> class InventoryStructure;
  template <typename BOM_CONTENT> class FlightDateStructure;
  template <typename BOM_CONTENT> class SegmentDateStructure;
  template <typename BOM_CONTENT> class LegDateStructure;
  template <typename BOM_CONTENT> class SegmentCabinStructure;
  template <typename BOM_CONTENT> class LegCabinStructure;
  template <typename BOM_CONTENT> class BookingClassStructure;
  
  /** Base class for Factory layer. */
  class FacBomStructure {
    friend class FacBomContent;
  public:

    /** Define the list (pool) of Bom objects. */
    typedef std::vector<BomStructure*> BomStructurePool_T;

    /** Destructor. */
    virtual ~FacBomStructure();

    /** Destroyed all the object instantiated by this factory. */
    void clean();

  protected:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is structure. */
    FacBomStructure() {}

  public:
    /** Provide the unique instance.
        <br>The singleton is instantiated when first used.
        @return FacBomStructure& */
    static FacBomStructure& instance();
    
    /** Create a structure object with the given key. */
    template <typename BOM_STRUCTURE>
    BOM_STRUCTURE& create () {
      BOM_STRUCTURE* aBomStructure_ptr = NULL;
      
      aBomStructure_ptr = new BOM_STRUCTURE ();
      assert (aBomStructure_ptr != NULL);

      // Initialise the children holder of the BOM structure.
      initChildrenHolders<BOM_STRUCTURE> (*aBomStructure_ptr);
      
      // The new object is added to the pool of structure objects
      _structurePool.push_back (aBomStructure_ptr);
      
      return *aBomStructure_ptr;
    }

    /** Link a child structure object with its parent.
        <br>For instance, link a SegmentDate structure object with its parent
        FlightDate structure object.
        <br>The child structure object is added to the dedicated holder within
        the parent structure object.       .
        @return bool Whether or not the operation succeeded. */
    template <typename BOM_STRUCTURE_CHILD>
    static bool linkBomParentWithBomChild 
    (typename BOM_STRUCTURE_CHILD::ParentBomStructure_T& ioBomParent,
     BOM_STRUCTURE_CHILD& ioBomChild) {

      // Set the parent of the child structure object
      ioBomChild._parent = &ioBomParent;
      
      // Retrive the bom children holder corresponding the the children type.
      typedef BomChildrenHolderImp<typename BOM_STRUCTURE_CHILD::Content_T> BOM_CHILDREN_HOLDER_T;
      BOM_CHILDREN_HOLDER_T* lBomChildrenHolder_ptr = NULL;
      ioBomParent.getChildrenHolder (lBomChildrenHolder_ptr);
      assert (lBomChildrenHolder_ptr != NULL);
      
      bool hasInsertBeenSuccessful =
        addBomObjecdToBomHolder <typename BOM_STRUCTURE_CHILD::Content_T>
        (*lBomChildrenHolder_ptr, ioBomChild);

      return hasInsertBeenSuccessful;
    }

    /** Add a BOM object into a dedicated BOM holder by using the
        short key of the object. */
    template <typename BOM_CONTENT>
    static bool addBomObjecdToBomHolder (BomChildrenHolderImp<BOM_CONTENT>& ioBomHolder, typename BOM_CONTENT::BomStructure_T& ioBomStructure) {
      // Retrieve the bom structure type.
      typedef typename BOM_CONTENT::BomStructure_T BOM_STRUCTURE_T;
      // Define the bom holder type.
      typedef BomChildrenHolderImp<BOM_CONTENT> BOM_HOLDER_T;
      
      // Retrieve the short key
      const typename BOM_STRUCTURE_T::BomKey_T& lBomKey = ioBomStructure.getKey();
      const std::string& lBomKeyStr = lBomKey.toString();
      
      // Insert the structure object in the dedicated lists
      typedef typename BOM_HOLDER_T::BomChildrenMap_T BOM_MAP_T;
      const bool hasInsertBeenSuccessful =
        ioBomHolder._bomChildrenMap.
        insert (typename BOM_MAP_T::value_type (lBomKeyStr,
                                                 &ioBomStructure)).second;
      if (hasInsertBeenSuccessful == false) {
        return hasInsertBeenSuccessful;
      }
      
      ioBomHolder._bomChildrenList.push_back (&ioBomStructure);
      
      return true;
    }
    
    /** Add a BOM object into a dedicated BOM holder by using the
        full key of the object. */
    template <typename BOM_CONTENT>
    static bool addFullBomObjecdToBomHolder (BomChildrenHolderImp<BOM_CONTENT>& ioBomHolder, typename BOM_CONTENT::BomStructure_T& ioBomStructure) {
      // Retrieve the bom structure type.
      typedef typename BOM_CONTENT::BomStructure_T BOM_STRUCTURE_T;
      // Define the bom holder type.
      typedef BomChildrenHolderImp<BOM_CONTENT> BOM_HOLDER_T;
      
      // Retrieve the short key
      const typename BOM_STRUCTURE_T::BomKey_T& lBomKey = ioBomStructure.getKey();
      const std::string& lBomKeyStr = lBomKey.describe();
      
      // Insert the structure object in the dedicated lists
      typedef typename BOM_HOLDER_T::BomChildrenMap_T BOM_MAP_T;
      const bool hasInsertBeenSuccessful =
        ioBomHolder._bomChildrenMap.
        insert (typename BOM_MAP_T::value_type (lBomKeyStr,
                                                 &ioBomStructure)).second;
      if (hasInsertBeenSuccessful == false) {
        return hasInsertBeenSuccessful;
      }
      
      ioBomHolder._bomChildrenList.push_back (&ioBomStructure);
      
      return true;
    }

  private:
    /** Create a bom children holder object with the given children type. */
    template <typename BOM_CONTENT_CHILD>
    BomChildrenHolderImp<BOM_CONTENT_CHILD>& createBomHolder () {
      
      BomChildrenHolderImp<BOM_CONTENT_CHILD>* aBomChildrenHolder_ptr = NULL;
      
      aBomChildrenHolder_ptr = new BomChildrenHolderImp<BOM_CONTENT_CHILD> ();
      assert (aBomChildrenHolder_ptr != NULL);
      
      // The new object is added to the pool of structure objects
      _structurePool.push_back (aBomChildrenHolder_ptr);
      
      return *aBomChildrenHolder_ptr;
    }

    /** Initialise the holder of children for a given BOM structure.
        <br>Create the BomChildrenHolder objects corresponding to the
        list of children types of the given BOM structure. */
    template <typename BOM_STRUCTURE>
    static void initChildrenHolders (BOM_STRUCTURE& ioBomStructure) {
      // Type for the childrend type list.
      typedef typename BOM_STRUCTURE::ChildrenBomTypeList_T CHILDREN_TYPE_LIST_T;

      typedef typename boost::mpl::at_c<CHILDREN_TYPE_LIST_T,0>::type CHILDREN_TYPE_T;
      
      typedef typename CHILDREN_TYPE_T::Content_T CONTENT_CHILDREN_T;
      BomChildrenHolderImp<CONTENT_CHILDREN_T>& lBomChildrenHolder=
        instance().createBomHolder<CONTENT_CHILDREN_T>();
      
      ioBomStructure.setChildrenHolder (lBomChildrenHolder);
      
      typedef typename boost::mpl::at_c<CHILDREN_TYPE_LIST_T,1>::type SECOND_CHILDREN_TYPE_T;
      
      typedef typename SECOND_CHILDREN_TYPE_T::Content_T SECOND_CONTENT_CHILDREN_T;
      BomChildrenHolderImp<SECOND_CONTENT_CHILDREN_T>& lSecondBomChildrenHolder =
        instance().createBomHolder<SECOND_CONTENT_CHILDREN_T>();
      
      ioBomStructure.setChildrenHolder (lSecondBomChildrenHolder);
    }

    // //////////////////////////////////////////////////////////////////
    // Section reserved for the building the direct accesses such as
    // booking class holder directly in inventory or flight-date, ect.
    // //////////////////////////////////////////////////////////////////
  private:

    // /////////////////////////////////////////////////////////////////
    template <typename BOM_ROOT_STRUCTURE>
    static void createDirectAccesses (BOM_ROOT_STRUCTURE& ioBomRootStructure) {
      // Retrieve the inventory structure type.
      typedef InventoryStructure<typename BOM_ROOT_STRUCTURE::ContentChild_T>
        INVENTORY_STRUCTURE_T;
      // Define the holder of inventories.
      typedef typename BOM_ROOT_STRUCTURE::ChildrenBomHolder_T INVENTORY_HOLDER_T;
      // Define the list of inventory structures.
      typedef typename INVENTORY_HOLDER_T::BomChildrenList_T INVENTORY_STRUCTURE_LIST_T;

      // Browse the BomRoot and build direct accesses within each inventory.
      const INVENTORY_HOLDER_T& lInventoryHolder =
        ioBomRootStructure.getChildrenHolder();
      const INVENTORY_STRUCTURE_LIST_T& lInventoryList =
        lInventoryHolder._bomChildrenList;
      for (typename INVENTORY_STRUCTURE_LIST_T::const_iterator itInv =
             lInventoryList.begin(); itInv != lInventoryList.end(); ++itInv) {
        INVENTORY_STRUCTURE_T* lInvStructure_ptr = *itInv;
        assert (lInvStructure_ptr != NULL);
        
        createDirectAccessesWithinInventory<INVENTORY_STRUCTURE_T> (*lInvStructure_ptr);
      }
    }

    // //////////////////////////////////////////////////////////////////
    /** Create a holder of all booking classes within the given inventory. */
    template <typename INVENTORY_STRUCTURE>
    static void createDirectAccessesWithinInventory (INVENTORY_STRUCTURE& ioInventoryStructure){
      // Retrieve the booking class type.
      typedef typename INVENTORY_STRUCTURE::BookingClass_T BOOKING_CLASS_T;
      // Define the bom holder of booking classes.
      typedef BomChildrenHolderImp<BOOKING_CLASS_T> BOOKING_CLASS_HOLDER_T;

      // Check if it is necessary to initialize the BookingClass holder.
      if (boost::is_same<BOOKING_CLASS_T, BomStopContent>::value == false) {
        // Initialize the booking class holder within the inventory.
        BOOKING_CLASS_HOLDER_T& lBookingClassHolder =
          FacBomStructure::instance().createBomHolder<BOOKING_CLASS_T> ();
        ioInventoryStructure.setBookingClassHolder(lBookingClassHolder);
      }
      
      // Retrieve the flight-date structure type.
      typedef FlightDateStructure<typename INVENTORY_STRUCTURE::ContentChild_T>
        FLIGHT_DATE_STRUCTURE_T;
      // Define the holder of flight-dates.
      typedef typename INVENTORY_STRUCTURE::ChildrenBomHolder_T FLIGHT_DATE_HOLDER_T;
      // Define the list of inventory structures.
      typedef typename FLIGHT_DATE_HOLDER_T::BomChildrenList_T FLIGHT_DATE_STRUCTURE_LIST_T;
      
      // Browse the inventory and build direct accesses within each
      // flight-date, then build the booking class holder within the
      // inventory.
      const FLIGHT_DATE_HOLDER_T& lFlightDateHolder =
        ioInventoryStructure.getChildrenHolder();
      const FLIGHT_DATE_STRUCTURE_LIST_T& lFlightDateList =
        lFlightDateHolder._bomChildrenList;
      for (typename FLIGHT_DATE_STRUCTURE_LIST_T::const_iterator itFlightDate =
             lFlightDateList.begin(); itFlightDate != lFlightDateList.end();
           ++itFlightDate) {
        FLIGHT_DATE_STRUCTURE_T* lCurrentFlightDate_ptr = *itFlightDate;
        assert (lCurrentFlightDate_ptr != NULL);

        createDirectAccessesWithinFlightDate<FLIGHT_DATE_STRUCTURE_T> (*lCurrentFlightDate_ptr);
      }
    }

    // //////////////////////////////////////////////////////////////////
    /** Create the direct acceeses within the given flight-date, and, at the
        same time, build the class holder for the parent inventory. */
    template <typename FLIGHT_DATE_STRUCTURE>
    static void createDirectAccessesWithinFlightDate (FLIGHT_DATE_STRUCTURE& ioFlightDateStructure) {
      // Retrieve the booking class type.
      typedef typename FLIGHT_DATE_STRUCTURE::BookingClass_T BOOKING_CLASS_T;
      // Define the bom holder of booking classes.
      typedef BomChildrenHolderImp<BOOKING_CLASS_T> BOOKING_CLASS_HOLDER_T;
      
      // Check if it is necessary to initialize the BookingClass holder.
      if (boost::is_same<BOOKING_CLASS_T, BomStopContent>::value == false) {
        // Initialize the booking class holder within the flight-date.
        BOOKING_CLASS_HOLDER_T& lBookingClassHolder =
          FacBomStructure::instance().createBomHolder<BOOKING_CLASS_T> ();
        ioFlightDateStructure.setBookingClassHolder(lBookingClassHolder);
      }
      
      // Retrieve the segment-date type.
      typedef SegmentDateStructure <typename FLIGHT_DATE_STRUCTURE::ContentChild_T> SEGMENT_DATE_STRUCTURE_T;
      // Define the holder of segment-dates.
      typedef typename FLIGHT_DATE_STRUCTURE::ChildrenBomHolder_T SEGMENT_DATE_HOLDER_T;
      // Define the list of segment-date structures.
      typedef typename SEGMENT_DATE_HOLDER_T::BomChildrenList_T SEGMENT_DATE_STRUCTURE_LIST_T;
      // Retrieve the segment-date key type.
      typedef typename SEGMENT_DATE_STRUCTURE_T::BomKey_T SEGMENT_DATE_KEY_T;
      // Retrieve the leg-date type.
      typedef typename FLIGHT_DATE_STRUCTURE::SecondContentChild_T LEG_DATE_T;
      // Retrieve the leg-date structure type.
      typedef typename LEG_DATE_T::BomStructure_T LEG_DATE_STRUCTURE_T;
      // Define the holder of leg-dates.
      typedef BomChildrenHolderImp<LEG_DATE_T> LEG_DATE_HOLDER_T;
      // Retrieve the map of leg-dates.
      typedef typename LEG_DATE_HOLDER_T::BomChildrenMap_T LEG_DATE_STRUCTURE_MAP_T;
      // Retrieve the leg-date key type.
      typedef typename LEG_DATE_STRUCTURE_T::BomKey_T LEG_DATE_KEY_T;
      
      const SEGMENT_DATE_HOLDER_T& lSegmentDateHolder =
        ioFlightDateStructure.getChildrenHolder();
      const SEGMENT_DATE_STRUCTURE_LIST_T& lSegmentDateList =
        lSegmentDateHolder._bomChildrenList;
      for (typename SEGMENT_DATE_STRUCTURE_LIST_T::const_iterator itSegmentDate =
             lSegmentDateList.begin();
           itSegmentDate != lSegmentDateList.end(); ++itSegmentDate) {
        SEGMENT_DATE_STRUCTURE_T* lCurrentSegmentDate_ptr = *itSegmentDate;
        assert (lCurrentSegmentDate_ptr != NULL);
        
        // Check if it is necessary to initialize the leg-date holder.
        if (boost::is_same<LEG_DATE_T, BomStopContent>::value == false) {
          // Initialize the leg-date holder within the segment-date.
          LEG_DATE_HOLDER_T& lLegDateHolder =
            instance().createBomHolder<LEG_DATE_T> ();
          lCurrentSegmentDate_ptr->setLegDateHolder(lLegDateHolder);

          const SEGMENT_DATE_KEY_T& lSegmentDateKey =
            lCurrentSegmentDate_ptr->getKey();
          const AirportCode_T& lBoardPoint = lSegmentDateKey.getBoardPoint();
          AirportCode_T currentBoardPoint = lBoardPoint;
          const AirportCode_T& lOffPoint = lSegmentDateKey.getOffPoint();
          
          // Add a sanity check so as to ensure that the loop stops. If
          // there are more than MAXIMUM_NUMBER_OF_LEGS legs, there is
          // an issue somewhere in the code (not in the parser, as the
          // segments are derived from the legs thanks to the
          // FlightPeriodStruct::buildSegments() method).
          unsigned short i = 1;
          while (currentBoardPoint != lOffPoint
                 && i <= MAXIMUM_NUMBER_OF_LEGS_IN_FLIGHT) {
            // Retrieve the (unique) LegDate getting that Board Point

            const LEG_DATE_HOLDER_T& lLegDateHolder = ioFlightDateStructure.getSecondChildrenHolder();
            const LEG_DATE_STRUCTURE_MAP_T& lLegDateMap = lLegDateHolder._bomChildrenMap;
            typename LEG_DATE_STRUCTURE_MAP_T::const_iterator itLegDate =
              lLegDateMap.find (currentBoardPoint);
            assert (itLegDate != lLegDateMap.end());
            LEG_DATE_STRUCTURE_T* lLegDateStructure_ptr = itLegDate->second;
            assert (lLegDateStructure_ptr != NULL);
            
            // Link the SegmentDate and LegDate together
            initLinkSegmentDateWithLegDate<SEGMENT_DATE_STRUCTURE_T> (*lCurrentSegmentDate_ptr, *lLegDateStructure_ptr);
            
            // Prepare the next iteration
            const typename LEG_DATE_STRUCTURE_T::Content_T* lLegDateContent_ptr =
              lLegDateStructure_ptr->_content;
            assert (lLegDateContent_ptr != NULL);
            currentBoardPoint = lLegDateContent_ptr->getOffPoint();
            ++i;
          }
          assert (i <= MAXIMUM_NUMBER_OF_LEGS_IN_FLIGHT);

        }
        // Create the routing for the leg- and segment-cabins.
        // At the same time, set the SegmentDate attributes derived from
        // its routing legs (e.g., board and off dates).
        createDirectAccessesWithinSegmentDate<SEGMENT_DATE_STRUCTURE_T> (*lCurrentSegmentDate_ptr);
      }             
    }

    // //////////////////////////////////////////////////////////////////
    /** Create the direct acceeses within the given segment-date, and, at the
        same time, build the class holder for the corresponding flight-date
        and inventory. */
    template <typename SEGMENT_DATE_STRUCTURE>
    static void createDirectAccessesWithinSegmentDate (SEGMENT_DATE_STRUCTURE& ioSegmentDateStructure) {
      // Retrieve the type of the holder of segment-cabins.
      typedef typename SEGMENT_DATE_STRUCTURE::ChildrenBomHolder_T SEGMENT_CABIN_HOLDER_T;
      // Retrieve the segment-cabin type.
      typedef typename SEGMENT_DATE_STRUCTURE::ContentChild_T SEGMENT_CABIN_T;
      // Retrieve the segment-cabin key type.
      typedef typename SEGMENT_CABIN_T::BomKey_T SEGMENT_CABIN_KEY_T;
      // Define the segment-cabin structure.
      typedef SegmentCabinStructure<SEGMENT_CABIN_T> SEGMENT_CABIN_STRUCTURE_T;
      // Retrieve the segment-cabin structure list type.
      typedef typename SEGMENT_CABIN_HOLDER_T::BomChildrenList_T SEGMENT_CABIN_LIST_T;
      // Retrieve the leg-date type.
      typedef typename SEGMENT_DATE_STRUCTURE::LegDate_T LEG_DATE_T;
      // Define the leg-date structure type.
      typedef LegDateStructure <LEG_DATE_T> LEG_DATE_STRUCTURE_T;
      // Define the leg-date holder type.
      typedef BomChildrenHolderImp<LEG_DATE_T> LEG_DATE_HOLDER_T;
      // Retrieve the leg-date structure list type.
      typedef typename LEG_DATE_HOLDER_T::BomChildrenList_T LEG_DATE_LIST_T;
      // Retrieve the leg-cabin type.
      typedef typename LEG_DATE_T::ContentChild_T LEG_CABIN_T;
      // Define the leg-cabin structure type.
      typedef LegCabinStructure <LEG_CABIN_T> LEG_CABIN_STRUCTURE_T;
      // Define the leg-cabin holder type.
      typedef BomChildrenHolderImp<LEG_CABIN_T> LEG_CABIN_HOLDER_T;
      // Retrieve the leg-cabin structure map type.
      typedef typename LEG_CABIN_HOLDER_T::BomChildrenMap_T LEG_CABIN_MAP_T;
      // Retrieve the leg-cabin key type.
      typedef typename LEG_CABIN_T::BomKey_T LEG_CABIN_KEY_T;
      
      
      // Browse the segment-cabin structure list.
      const SEGMENT_CABIN_HOLDER_T& lSegmentCabinHolder =
        ioSegmentDateStructure.getChildrenHolder();
      const SEGMENT_CABIN_LIST_T lSegmentCabinList =
        lSegmentCabinHolder._bomChildrenList;
      for (typename SEGMENT_CABIN_LIST_T::const_iterator itSegmentCabin =
             lSegmentCabinList.begin();
           itSegmentCabin != lSegmentCabinList.end(); ++itSegmentCabin) {
        SEGMENT_CABIN_STRUCTURE_T* lSegmentCabinStructure_ptr = *itSegmentCabin;
        assert (lSegmentCabinStructure_ptr != NULL);
        
        // Initialize the leg-cabin holder for the current segment-cabin.
        LEG_CABIN_HOLDER_T& lLegCabinHolder =
          instance().createBomHolder<LEG_CABIN_T> ();
        lSegmentCabinStructure_ptr->setLegCabinHolder (lLegCabinHolder);
        
        // Iterate on the routing legs
        const LEG_DATE_HOLDER_T& lLegDateHolder =
          ioSegmentDateStructure.getLegDateHolder();
        const LEG_DATE_LIST_T& lLegDateList = lLegDateHolder._bomChildrenList;
        for (typename LEG_DATE_LIST_T::const_iterator itLegDate =
               lLegDateList.begin();
             itLegDate != lLegDateList.end(); ++itLegDate) {
          const LEG_DATE_STRUCTURE_T* lLegDateStructure_ptr = *itLegDate;
          assert (lLegDateStructure_ptr != NULL);
          
          // Retrieve the LegCabin getting the same class of service
          // (cabin code) as the SegmentCabin.
          const SEGMENT_CABIN_KEY_T& lSegmentCabinKey =
            lSegmentCabinStructure_ptr->getKey();
          const CabinCode_T& lCabinCode = lSegmentCabinKey.getCabinCode();

          const LEG_CABIN_HOLDER_T& lCurrentLetCabinHolder =
            lLegDateStructure_ptr->getChildrenHolder();
          const LEG_CABIN_MAP_T& lCurrentLegCabinMap =
            lCurrentLetCabinHolder._bomChildrenMap;
          typename LEG_CABIN_MAP_T::const_iterator itLegCabin =
            lCurrentLegCabinMap.find (lCabinCode);
          assert (itLegCabin != lCurrentLegCabinMap.end());
          LEG_CABIN_STRUCTURE_T& lLegCabinStructure = *itLegCabin->second;
          
          // Link the SegmentCabin and LegCabin together
          initLinkSegmentCabinWithLegCabin<SEGMENT_CABIN_STRUCTURE_T> (*lSegmentCabinStructure_ptr, lLegCabinStructure);
          
          // Build the class holders for the corresponding flight-date and
          // inventory.
          buildBookingClassHolders<SEGMENT_CABIN_STRUCTURE_T> (*lSegmentCabinStructure_ptr);
        }
      }
    }

    // //////////////////////////////////////////////////////////////////
    /** Build the booking class holders of the corresponding inventory
        and flight-date of the given segment-cabin. */
    template <typename SEGMENT_CABIN_STRUCTURE>
    static void buildBookingClassHolders (SEGMENT_CABIN_STRUCTURE& ioSegmentCabinStructure) {
      // Retrieve the flight-date structure type.
      typedef typename SEGMENT_CABIN_STRUCTURE::ParentBomStructure_T::ParentBomStructure_T FLIGHT_DATE_STRUCTURE_T;
      // Retrieve the booking class type.
      typedef typename SEGMENT_CABIN_STRUCTURE::ContentChild_T BOOKING_CLASS_T;
      // Retrieve the booking class structure type.
      typedef typename BOOKING_CLASS_T::BomStructure_T BOOKING_CLASS_STRUCTURE_T;

      FLIGHT_DATE_STRUCTURE_T& lFDStructure = ioSegmentCabinStructure.
        getSegmentDateStructure().getFlightDateStructure();

      // Define the holder of booking classes.
      typedef BomChildrenHolderImp<BOOKING_CLASS_T> BOOKING_CLASS_HOLDER_T;

      // Retrieve the booking class holders of the flight-date and the
      // inventory.
      BOOKING_CLASS_HOLDER_T& lFDBookingClassHolder =
        lFDStructure.getBookingClassHolder();
      BOOKING_CLASS_HOLDER_T& lInvBookingClassHolder =
        lFDStructure.getInventoryStructure().getBookingClassHolder();

      // Retrieve the list of booking classes.
      typedef typename BOOKING_CLASS_HOLDER_T::BomChildrenList_T BOOKING_CLASS_LIST_T;
      const BOOKING_CLASS_HOLDER_T& lBookingClassHolder =
        ioSegmentCabinStructure.getChildrenHolder();
      BOOKING_CLASS_LIST_T lBookingClassList =
        lBookingClassHolder._bomChildrenList;
      for (typename BOOKING_CLASS_LIST_T::const_iterator itBookingClass =
             lBookingClassList.begin();
           itBookingClass != lBookingClassList.end(); ++itBookingClass) {
        BOOKING_CLASS_STRUCTURE_T* lBookingClassStructure_ptr = *itBookingClass;
        assert (lBookingClassStructure_ptr != NULL);
        
        bool addingSucceeded =
          addFullBomObjecdToBomHolder<BOOKING_CLASS_T> (lFDBookingClassHolder,
                                                        *lBookingClassStructure_ptr);
        assert (addingSucceeded == true);
        addingSucceeded =
          addFullBomObjecdToBomHolder<BOOKING_CLASS_T> (lInvBookingClassHolder,
                                                        *lBookingClassStructure_ptr);
        assert (addingSucceeded == true);
      }
    }
    
    // //////////////////////////////////////////////////////////////////
    /** Build the link between the given segment-date and the given leg-date. */
    template <typename SEGMENT_DATE_STRUCTURE>
    static void initLinkSegmentDateWithLegDate (SEGMENT_DATE_STRUCTURE& ioSegmentDateStructure, typename SEGMENT_DATE_STRUCTURE::LegDate_T::BomStructure_T& ioLegDateStructure) {
      // Retrieve the leg-date type (can be STOP type).
      typedef typename SEGMENT_DATE_STRUCTURE::LegDate_T LEG_DATE_T;
      // Retrieve the segment-date type.
      typedef typename SEGMENT_DATE_STRUCTURE::Content_T SEGMENT_DATE_T;
      // Define the segment-date holder type.
      typedef BomChildrenHolderImp<SEGMENT_DATE_T> SEGMENT_DATE_HOLDER_T;
      // Define the leg-date holder type.
      typedef BomChildrenHolderImp<LEG_DATE_T> LEG_DATE_HOLDER_T;

      LEG_DATE_HOLDER_T* lLegDateHolder_ptr =
        ioSegmentDateStructure._legDateHolder;
      assert (lLegDateHolder_ptr != NULL);

      bool addingSucceeded =
        addBomObjecdToBomHolder<LEG_DATE_T> (*lLegDateHolder_ptr,
                                             ioLegDateStructure);
      assert (addingSucceeded == true);
      
      SEGMENT_DATE_HOLDER_T* lSegmentDateHolder_ptr =
        ioLegDateStructure._segmentDateHolder;
      if (lSegmentDateHolder_ptr == NULL) {
        lSegmentDateHolder_ptr = &instance().createBomHolder<SEGMENT_DATE_T>();
      }

      addingSucceeded = 
        addBomObjecdToBomHolder<SEGMENT_DATE_T> (*lSegmentDateHolder_ptr,
                                               ioSegmentDateStructure);
      assert (addingSucceeded == true);
    }

    // //////////////////////////////////////////////////////////////////
    /** Build the link between the given segment-cabin and the given leg-cabin.*/
    template <typename SEGMENT_CABIN_STRUCTURE>
    static void initLinkSegmentCabinWithLegCabin (SEGMENT_CABIN_STRUCTURE& ioSegmentCabinStructure, typename SEGMENT_CABIN_STRUCTURE::LegCabin_T::BomStructure_T& ioLegCabinStructure) {
      // Retrieve the leg-cabin type (can be STOP type).
      typedef typename SEGMENT_CABIN_STRUCTURE::LegCabin_T LEG_CABIN_T;
      // Retrieve the segment-cabin type.
      typedef typename SEGMENT_CABIN_STRUCTURE::Content_T SEGMENT_CABIN_T;
      // Define the segment-cabin holder type.
      typedef BomChildrenHolderImp<SEGMENT_CABIN_T> SEGMENT_CABIN_HOLDER_T;
      // Define the leg-cabin holder type.
      typedef BomChildrenHolderImp<LEG_CABIN_T> LEG_CABIN_HOLDER_T;

      LEG_CABIN_HOLDER_T* lLegCabinHolder_ptr =
        ioSegmentCabinStructure._legCabinHolder;
      assert (lLegCabinHolder_ptr != NULL);

      bool addingSucceeded =
        addBomObjecdToBomHolder<LEG_CABIN_T> (*lLegCabinHolder_ptr,
                                             ioLegCabinStructure);
      assert (addingSucceeded == true);
      
      SEGMENT_CABIN_HOLDER_T* lSegmentCabinHolder_ptr =
        ioLegCabinStructure._segmentCabinHolder;
      if (lSegmentCabinHolder_ptr == NULL) {
        lSegmentCabinHolder_ptr = &instance().createBomHolder<SEGMENT_CABIN_T>();
      }

      addingSucceeded = 
        addBomObjecdToBomHolder<SEGMENT_CABIN_T> (*lSegmentCabinHolder_ptr,
                                               ioSegmentCabinStructure);
      assert (addingSucceeded == true);
    }

  private:
    /** The unique instance.*/
    static FacBomStructure* _instance;
    
  private:
    /** List of instantiated Business Objects*/
    BomStructurePool_T _structurePool;
  };
}
#endif // __STDAIR_FAC_FACBOMSTRUCTURE_HPP
