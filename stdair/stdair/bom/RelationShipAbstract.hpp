/**
 * @defgroup RelationShipAbstract Abstract part of the Business Object Model
 * @author Anh Quan Nguyen <quannaus@users.sourceforge.net>
 * @date 20/01/2010
 */
#ifndef __STDAIR_BOM_RELATIONSHIPABSTRACT_HPP
#define __STDAIR_BOM_RELATIONSHIPABSTRACT_HPP

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
  class RelationShipAbstract {
  protected:
    /** Protected Default Constructor to ensure this class is abtract. */
    RelationShipAbstract () {}
    RelationShipAbstract (const RelationShipAbstract&) {}
  public:
    /** Destructor. */
    virtual ~RelationShipAbstract() {}
 };
}

#endif // __STDAIR_BOM_RELATIONSHIPABSTRACT_HPP
