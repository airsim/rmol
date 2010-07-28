// //////////////////////////////////////////////////////////////////////
#ifndef __STRUCTURETYPES_HPP
#define __STRUCTURETYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// /////////////////////////////////////////////
// BOOST
#include <boost/fusion/include/map.hpp>
#include <boost/mpl/map.hpp>

// Forward declarations.
namespace stdair {
  template <typename CONTENT> class BomChildrenHolderImp;
  template <typename BOM> struct BomList_T;
  template <typename BOM> struct BomMap_T;
}
template <typename CONTENT> class Structure;
class BomRoot;
class Inventory;

// /////////////////////////////////////////////////
typedef Structure<BomRoot> BomRootStructure_T;
typedef Structure<Inventory> InventoryStructure_T;
typedef stdair::BomChildrenHolderImp<Inventory> InventoryHolder_T;
typedef stdair::BomList_T<Inventory> InventoryList_T;
typedef stdair::BomMap_T<Inventory> InventoryMap_T;

// /////////////////////////////////////////////////
typedef boost::mpl::map <
  boost::mpl::pair<Inventory, BomRoot>,
  boost::mpl::pair<BomRoot, BomRoot> > ParentMap_T;

typedef boost::fusion::map<
  boost::fusion::pair<Inventory, InventoryHolder_T*>
  >BomRootChildrenHolderMap_T;
typedef boost::fusion::map< > InventoryChildrenHolderMap_T;

typedef boost::mpl::map <
  boost::mpl::pair<BomRoot, BomRootChildrenHolderMap_T>,
  boost::mpl::pair<Inventory, InventoryChildrenHolderMap_T>
  > ChildrenHolderMapMap_T;


#endif // __STRUCTURETYPES_HPP

