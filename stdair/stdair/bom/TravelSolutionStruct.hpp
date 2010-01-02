#ifndef __STDAIR_BOM_TRAVELSOLUTIONSTRUCT_HPP
#define __STDAIR_BOM_TRAVELSOLUTIONSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>
// StdAir
#include <stdair/bom/StructAbstract.hpp>

namespace stdair {

  /** Structure holding the elements of a travel solution. */
  struct TravelSolutionStruct : public StructAbstract {
  public:
    
    // /////////// Display support method /////////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream& ioIn);

    /** Display of the structure. */
    const std::string describe() const;


  private:

  };

}
#endif // __STDAIR_BOM_TRAVELSOLUTIONSTRUCT_HPP
