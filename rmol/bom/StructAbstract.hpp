#ifndef __RMOL_BOM_STRUCTABSTRACT_HPP
#define __RMOL_BOM_STRUCTABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
#include <sstream>

namespace RMOL {

  /** Base class for the Structures of the Business Object Model (BOM)
      layer. */
  struct StructAbstract {
  public:
    
    /** Destructor. */
    virtual ~StructAbstract() {}
    
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream& ioOut) const {
      ioOut << describe();
    }
    
    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) {}
    
    /** Display of the structure. */
    virtual const std::string describe() const = 0;
    
  protected:
    /** Protected Default Constructor to ensure this class is abtract. */
    StructAbstract() {}
  };
}

/**
   Piece of code given by Nicolai M. Josuttis, Section 13.12.1 "Implementing
   Output Operators" (p653) of his book "The C++ Standard Library: A Tutorial
   and Reference", published by Addison-Wesley.
*/
template <class charT, class traits>
inline
std::basic_ostream<charT, traits>&
operator<< (std::basic_ostream<charT, traits>& ioOut,
            const RMOL::StructAbstract& iStruct) {
  /**
     string stream:
     - with same format
     - without special field width
  */
  std::basic_ostringstream<charT,traits> ostr;
  ostr.copyfmt (ioOut);
  ostr.width (0);

  // Fill string stream
  iStruct.toStream (ostr);

  // Print string stream
  ioOut << ostr.str();

  return ioOut;
}

/**
   Piece of code given by Nicolai M. Josuttis, Section 13.12.1 "Implementing
   Output Operators" (pp655-657) of his book "The C++ Standard Library:
   A Tutorial and Reference", published by Addison-Wesley.
*/
template <class charT, class traits>
inline
std::basic_istream<charT, traits>&
operator>> (std::basic_istream<charT, traits>& ioIn,
            RMOL::StructAbstract& ioStruct) {
  // Fill the Structure object with the input stream.
  ioStruct.fromStream (ioIn);
  return ioIn;

}

#endif // __RMOL_BOM_STRUCTABSTRACT_HPP
