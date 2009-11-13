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
#include <stdair/bom/BomChildrenHolderImp.hpp>
#include <stdair/bom/BomStructure.hpp>

namespace stdair {

  // Forward declarations
  class BomContent;
  class BomStructure;

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

      // Initialise the children list of the BOM structure.
      initChildrenLists<BOM_STRUCTURE> (*aBomStructure_ptr);
      
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
    template <typename BOM_STRUCTURE_CHILD>
    static bool linkBomParentWithBomChild 
    (typename BOM_STRUCTURE_CHILD::ParentBomStructure_T& ioBomParent,
     BOM_STRUCTURE_CHILD& ioBomChild) {

      // Set the parent of the child structure object
      ioBomChild._parent = &ioBomParent;
      
      // Retrive the bom children holder corresponding the the children type.
      typedef BomChildrenHolderImp<typename BOM_STRUCTURE_CHILD::Content_T> BOM_CHILDREN_HOLDER_T;
      BOM_CHILDREN_HOLDER_T* lBomChildrenHolder_ptr = NULL;
      ioBomParent.getChildrenList (lBomChildrenHolder_ptr);
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
      typedef typename BOM_HOLDER_T::BomChildrenList_T BOM_LIST_T;
      const bool hasInsertBeenSuccessful =
        ioBomHolder._bomChildrenList.
        insert (typename BOM_LIST_T::value_type (lBomKeyStr,
                                                 &ioBomStructure)).second;
      if (hasInsertBeenSuccessful == false) {
        return hasInsertBeenSuccessful;
      }
      
      ioBomHolder._bomChildrenOrderedList.push_back (&ioBomStructure);
      
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
      typedef typename BOM_HOLDER_T::BomChildrenList_T BOM_LIST_T;
      const bool hasInsertBeenSuccessful =
        ioBomHolder._bomChildrenList.
        insert (typename BOM_LIST_T::value_type (lBomKeyStr,
                                                 &ioBomStructure)).second;
      if (hasInsertBeenSuccessful == false) {
        return hasInsertBeenSuccessful;
      }
      
      ioBomHolder._bomChildrenOrderedList.push_back (&ioBomStructure);
      
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

    /** Initialise the list of children for a given BOM structure.
        <br>Create the BomChildrenHolder objects corresponding to the
        list of children types of the given BOM structure. */
    template <typename BOM_STRUCTURE>
    static void initChildrenLists (BOM_STRUCTURE& ioBomStructure) {
      // Type for the childrend type list.
      typedef typename BOM_STRUCTURE::ChildrenBomTypeList_T CHILDREN_TYPE_LIST_T;

      typedef typename boost::mpl::at_c<CHILDREN_TYPE_LIST_T,0>::type CHILDREN_TYPE_T;
      
      typedef typename CHILDREN_TYPE_T::Content_T CONTENT_CHILDREN_T;
      BomChildrenHolderImp<CONTENT_CHILDREN_T>& lBomChildrenHolder=
        instance().createBomHolder<CONTENT_CHILDREN_T>();
      
      ioBomStructure.setChildrenList (lBomChildrenHolder);
      
      typedef typename boost::mpl::at_c<CHILDREN_TYPE_LIST_T,1>::type SECOND_CHILDREN_TYPE_T;
      
      typedef typename SECOND_CHILDREN_TYPE_T::Content_T SECOND_CONTENT_CHILDREN_T;
      BomChildrenHolderImp<SECOND_CONTENT_CHILDREN_T>& lSecondBomChildrenHolder =
        instance().createBomHolder<SECOND_CONTENT_CHILDREN_T>();
      
      ioBomStructure.setChildrenList (lSecondBomChildrenHolder);
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
