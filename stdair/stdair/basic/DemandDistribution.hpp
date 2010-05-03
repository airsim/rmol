#ifndef __STDAIR_BAS_DEMAND_DISTRIBUTION_HPP
#define __STDAIR_BAS_DEMAND_DISTRIBUTION_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/ContinuousAttribute.hpp>

namespace stdair {
  
  /** Class modeling the distribution of a demand type. */
  struct DemandDistribution {
    
    // ////////////// Display Support Methods //////////
    /** Display demand distribution */
    std::string display() const;

    
    // ////////// Constructors and destructors /////////
    /** Constructor. */
    DemandDistribution (const NbOfRequests_T& iMean,
                        const StandardDeviationValue_T& iStandardDeviation);
    /** Default constructor. */
    DemandDistribution ();
    /** Copy constructor. */
    DemandDistribution (const DemandDistribution&);
    /** Destructor. */
     ~DemandDistribution ();

    
    // ////////// Attributes //////////
    /** Mean number of requests */
    NbOfRequests_T _meanNumberOfRequests;
    
    /** Standard deviation of number of requests */
    StandardDeviationValue_T _standardDeviationNumberOfRequests;
  };

}
#endif // __STDAIR_BAS_DEMAND_DISTRIBUTION_HPP
