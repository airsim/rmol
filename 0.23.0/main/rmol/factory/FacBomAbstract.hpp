#ifndef __RMOL_FAC_FACBOMABSTRACT_HPP
#define __RMOL_FAC_FACBOMABSTRACT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>

namespace RMOL {

  // Forward declarations
  class BomAbstract;

  /** Base class for Factory layer. */
  class FacBomAbstract {
  public:

    /** Define the list (pool) of Bom objects. */
    typedef std::vector<BomAbstract*> BomPool_T;

    /** Destructor. */
    virtual ~FacBomAbstract();

    /** Destroyed all the object instantiated by this factory. */
    void clean();

  protected:
    /** Default Constructor.
        <br>This constructor is protected to ensure the class is abstract. */
    FacBomAbstract() {}

    /** List of instantiated Business Objects*/
    BomPool_T _pool;
  };
}
#endif // __RMOL_FAC_FACBOMABSTRACT_HPP
