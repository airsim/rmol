#ifndef __INTRUSIVE_BOM_RELATIONSHIPABSTRACT_HPP
#define __INTRUSIVE_BOM_RELATIONSHIPABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/STDAIR_Types.hpp>

namespace stdair {

  /**
   * @brief Base class for the relation ship objects
   */
  class FacRelationShipRootAbstract {
  protected:
    /** Protected Default Constructor to ensure this class is abtract. */
    FacRelationShipRootAbstract () {}
    FacRelationShipRootAbstract (const FacRelationShipRootAbstract&) {}
  public:
    /** Destructor. */
    virtual ~FacRelationShipRootAbstract() {}
 };

}
#endif // __INTRUSIVE_BOM_RELATIONSHIPABSTRACT_HPP
