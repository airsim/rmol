#ifndef __AIRRAC_BOM_BOMABSTRACT_HPP
#define __AIRRAC_BOM_BOMABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>

namespace AIRRAC {

  /** Base class for the Business Object Model (BOM) layer. */
  class BomAbstract {
    friend class FacBomAbstract;
  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const = 0;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) = 0;

    /** Get the serialised version of the Business Object. */
    virtual std::string toString() const = 0;
    
    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    virtual std::string describeKey() const = 0;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    virtual std::string describeShortKey() const = 0;

    
  protected:
    /** Protected Default Constructor to ensure this class is abtract. */
    BomAbstract() {}
    BomAbstract(const BomAbstract&) {}

    /** Destructor. */
    virtual ~BomAbstract() {}
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
            const AIRRAC::BomAbstract& iBom) {
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
            AIRRAC::BomAbstract& ioBom) {
  // Fill Bom object with input stream
  ioBom.fromStream (ioIn);
  return ioIn;
}

#endif // __AIRRAC_BOM_BOMABSTRACT_HPP
