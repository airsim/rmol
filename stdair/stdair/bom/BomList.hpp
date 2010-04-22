#ifndef __STDAIR_BOM_BOMLIST_HPP
#define __STDAIR_BOM_BOMLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>

namespace stdair {
  
  // Forward declarations
  template <typename CONTENT, typename ITERATOR> struct BomIterator_T;
  template <typename CONTENT> class BomChildrenHolderImp;
  
  /** Structure which handles the iterators for a bom list. */
  template <typename BOM> struct BomList_T {

  public:
    /** Definition that allows to retrieve the corresponding Structure
        associated to the BOM. */
    typedef typename BOM::Structure_T Structure_T;
    /** Define the list of bom objects. */
    typedef std::vector<const Structure_T*> StructureList_T;
    /** Define the bom holder. */
    typedef BomChildrenHolderImp<BOM> BomHolder_T;

    // /////////////////////////////////////////////////////////////////////////
    // See the explanations, within the stdair::BomContentRoot class, for all
    // the iterator types specified below
    // /////////////////////////////////////////////////////////////////////////
    /** Define the bom list iterators. */
    typedef BomIterator_T<BOM, typename StructureList_T::const_iterator> iterator;
    typedef BomIterator_T<BOM, typename StructureList_T::const_reverse_iterator> reverse_iterator;
    // /////////////////////////////////////////////////////////////////////////
       
  public:
    // /////////// Iteration methods //////////
    /** Initialise the internal iterator on flight date:
        return the iterator at the begining of the list. */
    iterator begin () const { return _bomHolder.listBegin(); }
    
    /** Initialise the internal iterator on flight date:
        return the iterator at the end of the list. */
    iterator end () const { return _bomHolder.listEnd(); }

    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the rbegining of the list. */
    reverse_iterator rbegin () const { return _bomHolder.listRBegin(); }
    
    /** Initialise the internal reverse iterator on flight date:
        return the reverse iterator at the end of the list. */
    reverse_iterator rend () const { return _bomHolder.listREnd(); }

    // /////////// Other operators /////////////
    /** Get the size of the list. */
    const unsigned int size () const { return _bomHolder.size(); }

  public:
    /** Default constructors. */
    BomList_T ();
    BomList_T (const BomList_T& iBomList) : _bomHolder (iBomList._bomHolder) { }
    BomList_T (const BomHolder_T& iBomHolder) : _bomHolder (iBomHolder) { }

    /** Destructor. */
    ~BomList_T() { }

  private:
    // Attributes
    /** Reference structure. */
    const BomHolder_T& _bomHolder;
  };

}
#endif // __STDAIR_BOM_BOMLIST_HPP

