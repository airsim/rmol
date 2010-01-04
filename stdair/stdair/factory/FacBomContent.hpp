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
    BOM_CONTENT_CHILD& create (typename BOM_CONTENT_CHILD::BomKey_T& ioKey) {
      
      // Create the child structure object for the given key
      BOM_CONTENT_CHILD& lBomContentChild =
        createInternal<BOM_CONTENT_CHILD> (ioKey);

      return lBomContentChild;
    }

    /** Link a child content objet with his parent. */
    template <typename BOM_CONTENT_CHILD>
    static void linkWithParent (BOM_CONTENT_CHILD& ioContentChild, typename BOM_CONTENT_CHILD::Parent_T& ioContentParent) {

      // Define the key types.
      typedef typename BOM_CONTENT_CHILD::Parent_T::BomKey_T ParentKey_T;
      
      // Finish the construction of the child key by setting its parent.
      const ParentKey_T& lParentKey = ioContentParent.getKey();
      ioContentChild._key.setParentKey (lParentKey);
      
      // Retrieve the child structure object
      typename BOM_CONTENT_CHILD::BomStructure_T& lBomStructureChild =
        ioContentChild.getBomStructure ();

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

  public:
    /** Build the direct accesses such as booking class holder
        directly in inventory or flight-date, ect. */
    template <typename BOM_ROOT>
    static void createDirectAccesses (const BOM_ROOT& iBomRoot) {
      // Forward the job to FacBomStructure.
      FacBomStructure::createDirectAccesses<typename BOM_ROOT::BomStructure_T>
        (iBomRoot._bomRootStructure);
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
