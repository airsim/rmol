#ifndef __MYPROVIDER_BOMROOT_HPP
#define __MYPROVIDER_BOMROOT_HPP
/*!
 * \page test_archi_root_hpp Specific Implementation of a BOM Root
 * \code
 */

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir 
#include <stdair/bom/BomRoot.hpp>

namespace myprovider {
  
  /** Class representing the actual functional/business content
      for the Bom root. */
  class BomRoot : public stdair::BomRoot {
  public:
    // /////////// Display support methods /////////
    /** Get the serialised version of the Business Object. */
    std::string toString() const { return describeKey(); }
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const { return std::string (""); }
  
  public:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Constructors. */
    BomRoot (const Key_T&);
    /** Destructor. */
    ~BomRoot();
    /** Default constructors. */
    BomRoot ();
    BomRoot (const BomRoot&);
  };
  
}  
/*!
 * \endcode
 */
#endif // __MYPROVIDER_BOMROOT_HPP
