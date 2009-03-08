#ifndef __RMOL_FLD_FLDABSTRACT_HPP
#define __RMOL_FLD_FLDABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

namespace RMOL {

  /** Base class for the Business Object Model (BOM) layer. */
  class FldAbstract {
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const = 0;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) = 0;
    
  protected:
    /** Protected Default Constructor to ensure this class is abtract. */
    FldAbstract() {}
    FldAbstract(const FldAbstract&) {}

    /** Destructor. */
    virtual ~FldAbstract() {}
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
            const RMOL::FldAbstract& iBom) {
  /**
     string stream:
      - with same format
      - without special field width
   */
  std::basic_ostringstream<charT,traits> ostr;
  ostr.copyfmt (ioOut);
  ostr.width (0);

  // Fill string stream
  iBom.toStream (ostr);

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
            RMOL::FldAbstract& ioBom) {
  // Fill Bom object with input stream
  ioBom.fromStream (ioIn);
  return ioIn;
}

#endif // __RMOL_FLD_FLDABSTRACT_HPP
