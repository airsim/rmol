#ifndef __INTRUSIVE_BOM_RELATIONSHIPHOLDERABSTRACT_HPP
#define __INTRUSIVE_BOM_RELATIONSHIPHOLDERABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <iosfwd>
#include <sstream>
#include <string>
// Boost.Intrusive
#include <boost/functional/hash.hpp>

namespace stdair {

  /** RelationShipHolderAbstract. */
  class RelationShipHolderAbstract {
  public:
    /** Constructors. */
    RelationShipHolderAbstract (const std::string& iKey) : _key (iKey)  {}
    RelationShipHolderAbstract (const int idx) {
      std::ostringstream oStr;
      oStr << idx;
      _key = oStr.str();
    }
    /** Destructor. */
    virtual ~RelationShipHolderAbstract() {}
    
  protected:
    /** Default constructors.
        <br>They are kept private, so as to forbid their use (only the
        public constructors should be used). */
    RelationShipHolderAbstract () {}
    RelationShipHolderAbstract (const RelationShipHolderAbstract&) {}

  public:
    /** Get the key. */
    const std::string& getKey() const {
      return _key;
    }
    
  public:
    // Comparison operators
    friend bool operator< (const RelationShipHolderAbstract& a,
                           const RelationShipHolderAbstract& b) {
      return a._key < b._key;
    }

    friend bool operator> (const RelationShipHolderAbstract& a,
                           const RelationShipHolderAbstract& b) {
      return a._key > b._key;
    }

    friend bool operator== (const RelationShipHolderAbstract& a,
                            const RelationShipHolderAbstract& b) {
      return a._key == b._key;
    }

    friend bool operator!= (const RelationShipHolderAbstract& a,
                            const RelationShipHolderAbstract& b) {
      return a._key != b._key;
    }

    // The hash function
    friend std::size_t hash_value (const RelationShipHolderAbstract& iRelationShipHolder) {
      return boost::hash<std::string>() (iRelationShipHolder._key);
    }

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
    
  protected:
    std::string _key;
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
            const stdair::RelationShipHolderAbstract& iRelationShipHolder) {
  /**
     string stream:
      - with same format
      - without special field width
   */
  std::basic_ostringstream<charT,traits> ostr;
  ostr.copyfmt (ioOut);
  ostr.width (0);

  // Fill string stream
  iRelationShipHolder.toStream (ostr);

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
            stdair::RelationShipHolderAbstract& ioRelationShipHolder) {
  // Fill RelationShipHolder object with input stream
  ioRelationShipHolder.fromStream (ioIn);
  return ioIn;
}

#endif // __INTRUSIVE_BOM_RELATIONSHIPHOLDERABSTRACT_HPP
