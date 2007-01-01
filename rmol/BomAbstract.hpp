#ifndef __RMOL_BOMABSTRACT_HPP
#define __RMOL_BOMABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>

namespace RMOL {

  /** Base class for the Business Object Model (BOM) layer. */
  class BomAbstract {
  public:

    /** Destructor. */
    virtual ~BomAbstract() {}

    /** Dump a Business Object into an output stream.
        @param ostream& the output stream
        @return ostream& the output stream. */
    virtual std::ostream& toStream (std::ostream& ioOut) const {}

  protected:
    /** Protected Default Constructor to ensure this class is abtract. */
    BomAbstract() {}
  };
}

std::ostream& operator<<(std::ostream& ioOut, const RMOL::BomAbstract& iBom);

#endif // __RMOL_BOMABSTRACT_HPP
