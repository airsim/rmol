#ifndef __BOMROOT_HPP
#define __BOMROOT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
#include <string>
#include "StructureTypes.hpp"
// StdAir 
#include <stdair/bom/BomRootContent.hpp>

/** Class representing the actual functional/business content
    for the Bom root. */
class BomRoot : public stdair::BomRootContent {
public:
  /** Definition allowing to retrieve the associated BOM structure type. */
  typedef BomRootStructure_T Structure_T;
  /** Definition allowing to retrieve the map/multimap type using by
      BomChildrenHolder. */
  typedef std::map<const std::string, const Structure_T*> Map_T;

public:
// /////////// Display support methods /////////
/** Dump a Business Object into an output stream.
    @param ostream& the output stream. */
void toStream (std::ostream& ioOut) const { ioOut << toString(); }

/** Read a Business Object from an input stream.
    @param istream& the input stream. */
void fromStream (std::istream& ioIn) { }

/** Get the serialised version of the Business Object. */
std::string toString() const { return describeKey(); }
    
/** Get a string describing the whole key (differentiating two objects
    at any level). */
const std::string describeKey() const { return std::string (""); }
    
public:
/** Constructors are private so as to force the usage of the Factory
    layer. */
/** Constructors. */
BomRoot (const Key_T&, Structure_T&);
/** Destructor. */
~BomRoot();
/** Default constructors. */
BomRoot ();
BomRoot (const BomRoot&);

// Attributes
/** Reference structure. */
Structure_T& _structure;
};
#endif // __BOMROOT_HPP
