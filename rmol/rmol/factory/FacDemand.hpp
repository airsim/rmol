#ifndef __RMOL_FAC_FACDEMAND_HPP
#define __RMOL_FAC_FACDEMAND_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/factory/FacBomAbstract.hpp>

namespace RMOL {

  /** Forward declarations. */
  class FldDistributionParameters;
  class FldYieldRange;
  class Demand;

  /** Factory for Demand. */
  class FacDemand : public FacBomAbstract {
  public:

    /** Provide the unique instance.
        <br> The singleton is instantiated when first used
        @return FacDemand& */
    static FacDemand& instance();

    /** Destructor.
        <br> The Destruction put the _instance to NULL
        in order to be clean for the next FacDemand::instance() */
    virtual ~FacDemand();

    /** Create a new Demand object.
        <br>This new object is added to the list of instantiated objects.
        @return Demand& The newly created object. */
    Demand& create (const FldDistributionParameters&, const FldYieldRange&);

  protected:
    /** Default Constructor.
        <br>This constructor is protected in order to ensure the singleton
        pattern.*/
    FacDemand () {}

  private:
    /** The unique instance.*/
    static FacDemand* _instance;

  };
}
#endif // __RMOL_FAC_FACDEMAND_HPP
