#ifndef __INTRUSIVE_BOM_RELATIONSHIPHOLDER_HPP
#define __INTRUSIVE_BOM_RELATIONSHIPHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost.Intrusive
#include <boost/intrusive/list.hpp>

/** Alias for the boost::intrusive namespace. */
namespace bi = boost::intrusive;

namespace stdair {

  /** Class holding relationship objects between either a parent Bom and its
      children or a Bom object and its siblings. */
  template <typename FIRST_BOM, typename SECOND_BOM>
  class RelationShipHolder {
  public:
    // ///////////////////////////////////////////
    /** Type definition for a list of either children or siblings. */
    typedef bi::list<SECOND_BOM> SecondBomList_T;

    /** Type definition for a relationship, holding a list of children
        or siblings for a given parent/Bom object.
        <br>The list has got only two elements. A list is used only because
        the pair does not exist (yet?) within boost::intrusive. */
    typedef bi::list<FIRST_BOM, SecondBomList_T> RelationShip_T;
    // ///////////////////////////////////////////
    
  private:
    /** Relationship, holding a list of children or siblings for a
        given parent/Bom object. */
    RelationShip_T _relationShip;
  };

}
#endif // __INTRUSIVE_BOM_RELATIONSHIPHOLDER_HPP
