#ifndef __STDAIR_BOM_BOMSTRUCTURE_HPP
#define __STDAIR_BOM_BOMSTRUCTURE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

namespace stdair {

  // Forward declarations
  class BomContent;

  /** Base class for the Business Object Model (BOM) tree structure.
      <br>That class is just a holder of, on one hand, a key and, on the
      other hand, a pointer on the functional (Business) object, which is
      the actual content. */
  class BomStructure {
    friend class FacBomStructure;
    friend class FacBomContent;
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
    virtual const std::string describeKey() const = 0;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    virtual const std::string describeShortKey() const = 0;

    /** Retrieve the actual functional (Business Object) content. */
    template<typename T>
    T& getContent() const {
      T* oBom_ptr = NULL;
      oBom_ptr = dynamic_cast<T*> (_content);
      assert (oBom_ptr != NULL);
      return *oBom_ptr;
    }

    
  protected:
    /** Protected Default Constructor to ensure this class is abtract. */
    BomStructure() : _content (NULL) {}
    BomStructure(const BomStructure&) : _content (NULL) {}

    /** Destructor. */
    virtual ~BomStructure() {}

  protected:
    // Attributes
    /** The actual functional (Business Object) content. */
    BomContent* _content;
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
            const stdair::BomStructure& iBom) {
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
            stdair::BomStructure& ioBom) {
  // Fill Bom object with input stream
  ioBom.fromStream (ioIn);
  return ioIn;
}

#endif // __STDAIR_BOM_BOMSTRUCTURE_HPP
