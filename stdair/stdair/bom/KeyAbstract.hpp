/**
 * @defgroup KeyAbstract Part of the Business Object Model (BOM) handling
 *           (hash-like )keys
 * @author Anh Quan Nguyen <quannaus@users.sourceforge.net>
 * @date 20/01/2010
 */
#ifndef __STDAIR_BOM_KEYABSTRACT_HPP
#define __STDAIR_BOM_KEYABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
#include <string>

namespace stdair {

  /**
   * @brief Base class for the keys of Business Object Model (BOM) layer.
   * <br>Note that that key allows to differentiate two objects
   * at the same level only. For instance, the segment-date key allows
   * to differentiate two segment-dates under a given flight-date,
   * but does not allow to differentiate two segemnt-dates in general.
   */
  struct KeyAbstract {
  public:

    // /////////// Display support methods /////////
    /**
     * @brief Dump a Business Object Key into an output stream.
     * @param[inout] ostream& the output stream.
     */
    virtual void toStream (std::ostream& ioOut) const {}

    /**
     * @brief Read a Business Object Key from an input stream.
     * @param[inout] istream& the input stream.
     */
    virtual void fromStream (std::istream& ioIn) {}

   /**
    * @brief Get the serialised version of the Business Object Key.
    * <br>That string is unique, at the level of a given Business Object,
    * when among children of a given parent Business Object.
    * <br>For instance, "H" and "K" allow to differentiate among two
    * marketing classes for the same segment-date.
    * @param[out] const std::string The serialised version of the Business
    *             Object Key.
    */
    virtual const std::string toString() const { return std::string("Hello!"); }

    /**
     * @brief Default destructor.
     */
    virtual ~KeyAbstract() {}
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
            const stdair::KeyAbstract& iKey) {
  /**
     string stream:
      - with same format
      - without special field width
   */
  std::basic_ostringstream<charT,traits> ostr;
  ostr.copyfmt (ioOut);
  ostr.width (0);

  // Fill string stream
  iKey.toStream (ostr);

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
            stdair::KeyAbstract& ioKey) {
  // Fill Key object with input stream
  ioKey.fromStream (ioIn);
  return ioIn;
}

#endif // __STDAIR_BOM_KEYABSTRACT_HPP
