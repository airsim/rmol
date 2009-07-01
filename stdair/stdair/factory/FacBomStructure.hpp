#ifndef __STDAIR_FAC_FACBOMSTRUCTURE_HPP
#define __STDAIR_FAC_FACBOMSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>

namespace stdair {

  // Forward declarations
  class BomStructure;
  class BomContent;

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
    template <typename BOM_KEY>
    typename BOM_KEY::BomStructure_T& create (const BOM_KEY& iKey) {
      typename BOM_KEY::BomStructure_T* aBomStructure_ptr = NULL;

      aBomStructure_ptr = new typename BOM_KEY::BomStructure_T (iKey);
      assert (aBomStructure_ptr != NULL);
      
      // The new object is added to the pool of structure objects
      _structurePool.push_back (aBomStructure_ptr);
      
      return *aBomStructure_ptr;
    }

    /** Link a child structure object with its parent.
        <br>For instance, link a SegmentDate structure object with its parent
        FlightDate structure object.
        <br>The child structure object is added to the dedicated list within
        the parent structure object.       .
        @return bool Whether or not the operation succeeded. */
    template <typename BOM_STRUCTURE_CHILD,
              typename BOM_CHILDREN_LIST>
    static bool linkBomParentWithBomChild (typename BOM_STRUCTURE_CHILD::ParentBomStructure_T& ioBomParent,
                                           BOM_STRUCTURE_CHILD& ioBomChild) {

      
      // Set the parent of the child structure object
      ioBomChild._parent = &ioBomParent;

      // Retrieve the short key
      const typename BOM_STRUCTURE_CHILD::BomKey_T& lBomChildKey =
        ioBomChild.getKey();
      const std::string& lBomChildKeyStr = lBomChildKey.toString();
      
      // Insert the child structure object in the dedicated list
      const bool hasInsertBeenSuccessful = ioBomParent._childrenList.
        insert (typename BOM_CHILDREN_LIST::value_type (lBomChildKeyStr,
                                                        &ioBomChild)).second;
      if (hasInsertBeenSuccessful == false) {
        return hasInsertBeenSuccessful;
      }
      return true;
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
