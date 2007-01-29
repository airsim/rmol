#ifndef __RMOL_DEMANDGENERATORLIST_HPP
#define __RMOL_DEMANDGENERATORLIST_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <list>
// RMOL
#include <rmol/bom/VariateList.hpp>
#include <rmol/bom/DistributionParameterList.hpp>
#include <rmol/bom/Gaussian.hpp>

namespace RMOL {

  /** Wrapper around a set of Gaussian Random Generators. */
  class DemandGeneratorList {
  protected:
    /** Define a (ordered) set of Gaussian Random Generators. */
    typedef std::list<Gaussian> DemandGeneratorList_T;
    
  public:
    /** Constructors. */
    DemandGeneratorList ();
    DemandGeneratorList (const DemandGeneratorList&);
    /** List of distribution parameters (mean, standard deviation). */
    DemandGeneratorList (const DistributionParameterList_T&);
    
    /** Destructors. */
    virtual ~DemandGeneratorList();

    /** */
    void generateVariateList (VariateList_T&) const;
    
  private:
    DemandGeneratorList_T _demandGeneratorList;

    /** Initialise the Random Genrators. */
    void init (const DistributionParameterList_T&);
    
  };
}
#endif // __RMOL_DEMANDGENERATORLIST_HPP
