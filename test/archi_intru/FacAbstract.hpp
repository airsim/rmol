#ifndef __INTRUSIVE_FAC_FACABSTRACT_HPP
#define __INTRUSIVE_FAC_FACABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////

namespace stdair {

  /** Base class for Factory layer. */
  class FacAbstract {
  public:      
    /** Destructor. */
    virtual ~FacAbstract() {}
      
  protected:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is abstract. */
    FacAbstract() {}
  };
}
#endif // __INTRUSIVE_FAC_FACABSTRACT_HPP
