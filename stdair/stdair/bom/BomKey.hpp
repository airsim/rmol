#ifndef __STDAIR_BOM_BOMKEY_HPP
#define __STDAIR_BOM_BOMKEY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

namespace stdair {

  /** Base class for the keys of Business Object Model (BOM) layer.
      <br>Note that that key allows to differentiate two objects
      at the same level only. For instance, the segment-date key allows
      to differentiate two segment-dates under a given flight-date,
      but does not allow to differentiate two segemnt-dates in general. */
  class BomKey {
  public:

    // /////////// Display support methods /////////
    /** Dump a Business Object Key into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const {}

    /** Read a Business Object Key from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) {}

   /** Get the serialised version of the Business Object Key.
       <br>That string is unique, at the level of a given Business Object,
       when among children of a given parent Business Object.
       <br>For instance, "H" and "K" allow to differentiate among two
       marketing classes for the same segment-date. */
    virtual std::string toString() const { return std::string("Hello!"); }
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
            const stdair::BomKey& iBom) {
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
            stdair::BomKey& ioBom) {
  // Fill Bom object with input stream
  ioBom.fromStream (ioIn);
  return ioIn;
}

#endif // __STDAIR_BOM_BOMKEY_HPP
