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
  public:
    
    // ///////////// Getters ///////////
    /** Get the mean number of requests. */
    const NbOfRequests_T& getMeanNumberOfRequests() const {
      return _meanNumberOfRequests;
    }
    
    /** Get the standard deviation of number of requests. */
    const StandardDeviationValue_T& getStandardDeviationNumberOfRequests() const {
      return _standardDeviationNumberOfRequests;
    }

  public:
    // ///////////// Setters ///////////
    /** Set the mean number of requests. */
    void setMeanNumberOfRequests (const NbOfRequests_T& iMean) {
      _meanNumberOfRequests = iMean;
    }
    
    /** Set the standard deviation of number of requests. */
    void setStandardDeviationNumberOfRequests (const StandardDeviationValue_T& iStandardDeviation) {
      _standardDeviationNumberOfRequests = iStandardDeviation;
    }
    
  public:
    // ////////////// Display Support Methods //////////
    /** Display demand distribution */
    std::string display() const;

    
  public:
    // ////////// Constructors and destructors /////////
    /** Constructor. */
    DemandDistribution (const NbOfRequests_T& iMean,
                        const StandardDeviationValue_T& iStandardDeviation);
    
    /** Default constructor. */
    // TODO: That constructor should be private
    DemandDistribution ();
    
    /** Copy constructor. */
    // TODO: That constructor should be private
    DemandDistribution (const DemandDistribution&);

    /** Destructor. */
    virtual ~DemandDistribution ();

    
  private:
    // ////////// Attributes //////////
    /** Mean number of requests */
    NbOfRequests_T _meanNumberOfRequests;
    
    /** Standard deviation of number of requests */
    StandardDeviationValue_T _standardDeviationNumberOfRequests;
  };

}
#endif // __STDAIR_BAS_DEMAND_DISTRIBUTION_HPP
