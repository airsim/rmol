#ifndef __RMOL_FAC_FACABSTRACT_HPP
#define __RMOL_FAC_FACABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>

namespace RMOL {

  // Forward declarations
  class BomAbstract;

  /** Base class for Factory layer. */
  class FacAbstract {
  public:

    /** Define the list (pool) of Bom objects. */
    typedef std::vector<BomAbstract*> BomPool_T;

    /** Destructor. */
    virtual ~FacAbstract();

    /** Destroyed all the object instantiated by this factory. */
    void clean();

  protected:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is abstract. */
    FacAbstract() {}

    /** List of instantiated Business Objects*/
    BomPool_T _pool;
  };
}
#endif // __RMOL_FAC_FACABSTRACT_HPP
