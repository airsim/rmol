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
    static void createDirectAccessesWithinInventory (INVENTORY& ioInventory){
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
      ioInventory._inventoryStructure.setBookingClassHolder(lBookingClassHolder);
      
      // Browse the inventory and build direct accesses within each
      // flight-date, then build the booking class holder within the
      // inventory.
      const FLIGHT_DATE_LIST_T lFlightDateList = ioInventory.getFlightDateList();
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
    static void createDirectAccessesWithinFlightDate (const FLIGHT_DATE& ioFlightDate) {
      // Retrieve the booking class type.
      typedef typename FLIGHT_DATE::BookingClassContent_T BOOKING_CLASS_T;
      // Define the bom holder of booking classes.
      typedef BomChildrenHolderImp<BOOKING_CLASS_T> BOOKING_CLASS_HOLDER_T;
      
      typename FLIGHT_DATE::BomStructure_T::ParentBomStructure_T& lInvStructure =
        ioFlightDate._flightDateStructure.getInventoryStructure();

      BOOKING_CLASS_HOLDER_T* lInvBookingClassHolder_ptr =
        lInvStructure._bookingClassHolder;
      assert (lInvBookingClassHolder_ptr != NULL);

      // Retrieve the segment-date type.
      typedef typename FLIGHT_DATE::ContentChild_T SEGMENT_DATE_T;
      // Define the list of segment-dates.
      typedef BomList_T<SEGMENT_DATE_T> SEGMENT_DATE_LIST_T;

             
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
