#ifndef __INVENTORY_HPP
#define __INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include <string>
#include "StructureTypes.hpp"
#include <stdair/bom/InventoryContent.hpp>

class Inventory : public stdair::InventoryContent {
  friend class FacBomContent;
public:
  /** Definition allowing to retrieve the associated BOM structure type. */
  typedef InventoryStructure_T Structure_T;
  /** Definition allowing to retrieve the map/multimap type using by
      BomChildrenHolder. */
  typedef std::map<const std::string, const Structure_T*> Map_T;

public:
// /////////// Display support methods /////////
/** Dump a Business Object into an output stream.
    @param ostream& the output stream. */
void toStream (std::ostream& ioOut) const;

/** Read a Business Object from an input stream.
    @param istream& the input stream. */
void fromStream (std::istream& ioIn);

/** Get the serialised version of the Business Object. */
std::string toString() const;
    
/** Get a string describing the whole key (differentiating two objects
    at any level). */
const std::string describeKey() const;


public:
/** Constructors are private so as to force the usage of the Factory
    layer. */
/** Constructors. */
Inventory (const Key_T&, Structure_T&);
/** Destructor. */
~Inventory();
/** Default constructors. */
Inventory ();
Inventory (const Inventory&);

// Attributes
/** Reference structure. */
Structure_T& _structure;
};

#endif // __INVENTORY_HPP

