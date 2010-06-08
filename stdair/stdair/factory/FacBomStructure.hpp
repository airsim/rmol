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
// BOOST Fusion
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/BomStructure.hpp>
#include <stdair/bom/Structure.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  // Forward declarations
  class BomContent;
  
  /** Base class for Factory layer. */
  class FacBomStructure {
    friend class FacBomContent;
  public:
    /** Define the list (pool) of Bom objects. */
    typedef std::vector<BomStructure*> BomStructurePool_T;

    
    // //////////////////////////////////////////////////////////////////
    /** Create a structure object with the given type. */
    template <typename STRUCTURE>
    STRUCTURE& create () {
      STRUCTURE* aBomStructure_ptr = NULL;
      aBomStructure_ptr = new STRUCTURE ();
      assert (aBomStructure_ptr != NULL);
      
      // The new object is added to the pool of structure objects
      _structurePool.push_back (aBomStructure_ptr);
      
      return *aBomStructure_ptr;
    }

    // //////////////////////////////////////////////////////////////////
    /** Link two child structure objects, the second one into the first one,
        using the short key. */
    template <typename PARENT, typename CHILD>
    static bool addObjectToTheDedicatedList (PARENT& ioParent,
                                             const CHILD& iChild) {
      // Retrive the bom children holder corresponding the the children type.
      typedef typename CHILD::Content_T CHILD_CONTENT_T;
      typedef BomChildrenHolderImp<CHILD_CONTENT_T> CHILDREN_HOLDER_T;
      
      CHILDREN_HOLDER_T*& lChildrenHolder_ptr =
        boost::fusion::at_key<CHILD_CONTENT_T> (ioParent._holderMap);

      // If the holder does not existe, then create it.
      if (lChildrenHolder_ptr == NULL) {
        lChildrenHolder_ptr = &instance().create<CHILDREN_HOLDER_T> ();
      }

      return addObjectToHolder<CHILD_CONTENT_T> (*lChildrenHolder_ptr, iChild);
    }

    // //////////////////////////////////////////////////////////////////
    /** Link two child structure objects, the second one into the first one,
        using the full key. */
    template <typename PARENT, typename CHILD>
    static bool addFullObjectToTheDedicatedList (PARENT& ioParent,
                                             const CHILD& iChild) {
      // Retrive the bom children holder corresponding the the children type.
      typedef typename CHILD::Content_T CHILD_CONTENT_T;
      typedef BomChildrenHolderImp<CHILD_CONTENT_T> CHILDREN_HOLDER_T;
      
      CHILDREN_HOLDER_T*& lChildrenHolder_ptr =
        boost::fusion::at_key<CHILD_CONTENT_T> (ioParent._holderMap);

      // If the holder does not existe, then create it.
      if (lChildrenHolder_ptr == NULL) {
        lChildrenHolder_ptr = &instance().create<CHILDREN_HOLDER_T> ();
      }

      return addFullObjectToHolder<CHILD_CONTENT_T> (*lChildrenHolder_ptr,
                                                     iChild);
    }

    // //////////////////////////////////////////////////////////////////
    /** Link a child structure object with its parent.
        <br>For instance, link a SegmentDate structure object with its parent
        FlightDate structure object.
        <br>The child structure object is added to the dedicated holder within
        the parent structure object.       .
        @return bool Whether or not the operation succeeded. */
    template <typename PARENT, typename CHILD>
    static bool linkParentWithChild (PARENT& ioParent, CHILD& ioChild) {
      // Set the parent of the child structure object
      ioChild._parent = &ioParent;
      return addObjectToTheDedicatedList (ioParent, ioChild);
    }

    // //////////////////////////////////////////////////////////////////
    /** Add a BOM object into a dedicated BOM holder by using the
        short key of the object. */
    template <typename CONTENT>
    static bool addObjectToHolder (BomChildrenHolderImp<CONTENT>& ioHolder,
                                   const typename CONTENT::Structure_T& iStructure) {
      // Retrieve the bom structure type.
      typedef typename CONTENT::Structure_T STRUCTURE_T;
      // Define the bom holder type.
      typedef BomChildrenHolderImp<CONTENT> HOLDER_T;
      
      // Retrieve the short key
      const typename STRUCTURE_T::Key_T& lKey = iStructure.getKey();
      const std::string& lKeyStr = lKey.toString();
      
      // Insert the structure object in the dedicated lists
      typedef typename HOLDER_T::BomChildrenMap_T BOM_MAP_T;
      const bool hasInsertBeenSuccessful = ioHolder.insert (lKeyStr, iStructure);
            
      return hasInsertBeenSuccessful;
    }

    // //////////////////////////////////////////////////////////////////
    /** Add a BOM object into a dedicated BOM holder by using the
        full key of the object. */
    template <typename CONTENT>
    static bool addFullObjectToHolder (BomChildrenHolderImp<CONTENT>& ioHolder,
                                       const typename CONTENT::Structure_T& iStructure) {
      // Retrieve the bom structure type.
      typedef typename CONTENT::Structure_T STRUCTURE_T;
      // Define the bom holder type.
      typedef BomChildrenHolderImp<CONTENT> HOLDER_T;
      
      // Retrieve the short key
      const std::string& lKeyStr = iStructure.getContent().describeKey();
      
      // Insert the structure object in the dedicated lists
      typedef typename HOLDER_T::BomChildrenMap_T BOM_MAP_T;
      const bool hasInsertBeenSuccessful = ioHolder.insert (lKeyStr, iStructure);
            
      return hasInsertBeenSuccessful;
    }
    
    // //////////////////////////////////////////////////////////////////
    /** Clone the children holder.*/
    template <typename HOLDER>
    static void cloneChildrenHolder (HOLDER*& ioHolder_ptr,
                                     const HOLDER& iReferenceHolder) {
      if (ioHolder_ptr == NULL) {
        ioHolder_ptr = &instance().create<HOLDER> ();
      }
      ioHolder_ptr->_bomChildrenMap = iReferenceHolder._bomChildrenMap;
      ioHolder_ptr->_bomChildrenList = iReferenceHolder._bomChildrenList;
    }
    
  protected:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is structure. */
    FacBomStructure() {}
  public:
    /** Destructor. */
    ~FacBomStructure();
    /** Destroyed all the object instantiated by this factory. */
    void clean();
    
    /** Provide the unique instance.
        <br>The singleton is instantiated when first used.
        @return FacBomStructure& */
    static FacBomStructure& instance();
    
  private:
    /** The unique instance.*/
    static FacBomStructure* _instance;

    /** List of instantiated Business Objects*/
    BomStructurePool_T _structurePool;

  };
}
#endif // __STDAIR_FAC_FACBOMSTRUCTURE_HPP
