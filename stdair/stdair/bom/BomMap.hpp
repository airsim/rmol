#ifndef __STDAIR_BOM_BOMMAP_HPP
#define __STDAIR_BOM_BOMMAP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>

namespace stdair {
  
  // Forward declarations
  template <typename BOM_CONTENT, typename ITERATOR> struct BomIterator_T;
  template <typename BOM_CONTENT> class BomChildrenHolderImp;
  
  /** Structure which handles the iterators for a bom map. */
  template <typename BOM> struct BomMap_T {

  public:
    /** Definition that allows to retrieve the corresponding BomStructure
        associated to the BOM. */
    typedef typename BOM::BomStructure_T BomStructure_T;
    /** Define the map of bom objects. */
    typedef std::map<const MapKey_T, BomStructure_T*> BomStructureMap_T;
    /** Define the bom holder. */
    typedef BomChildrenHolderImp<BOM> BomHolder_T;

    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the bom map iterators. */
    typedef BomIterator_T<BOM, typename BomStructureMap_T::const_iterator> iterator;
    typedef BomIterator_T<BOM, typename BomStructureMap_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
       
  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on flight date:
        return the iterator at the begining of the map. */
    iterator begin () const { return _bomHolder.mapBegin(); }
    
    /** Initialise the internal iterator on flight date:
        return the iterator at the end of the map. */
    iterator end () const { return _bomHolder.mapEnd(); }

    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the rbegining of the map. */
    reverse_iterator rbegin () const { return _bomHolder.mapRBegin(); }
    
    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the end of the map. */
    reverse_iterator rend () const { return _bomHolder.mapREnd(); }
    
    /** Retrieve, if existing, the Inventory corresponding to the
        given key. */
    iterator find (const MapKey_T& iKey) const { return _bomHolder.find (iKey); }
    
  public:
    /** Default constructors. */
    BomMap_T ();
    BomMap_T (const BomMap_T& iBomMap) : _bomHolder (iBomMap._bomHolder) { }
    BomMap_T (const BomHolder_T& iBomHolder) : _bomHolder (iBomHolder) { }

    /** Destructor. */
    ~BomMap_T() { }

  private:
    // Attributes
    /** Reference structure. */
    const BomHolder_T& _bomHolder;
  };

}
#endif // __STDAIR_BOM_BOMMAP_HPP

