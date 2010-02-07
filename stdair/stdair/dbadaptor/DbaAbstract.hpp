#ifndef __STDAIR_DBA_DBAABSTRACT_HPP
#define __STDAIR_DBA_DBAABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>

namespace stdair {

  /** Base class for the Database Adaptor (DBA) layer. */
  class DbaAbstract {
  public:

    /** Destructor. */
    virtual ~DbaAbstract() {}
    
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const {}
    
    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) {}
    
  protected:
    /** Protected Default Constructor to ensure this class is abtract. */
    DbaAbstract() {}
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
            const stdair::DbaAbstract& iDba) {
  /**
     string stream:
     - with same format
     - without special field width
  */
  std::basic_ostringstream<charT,traits> ostr;
  ostr.copyfmt (ioOut);
  ostr.width (0);

  // Fill string stream
  iDba.toStream (ostr);

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
            stdair::DbaAbstract& ioDba) {
  // Fill Dba object with input stream
  ioDba.fromStream (ioIn);
  return ioIn;
}

#endif // __STDAIR_DBA_DBAABSTRACT_HPP
