#ifndef __RMOL_COMMAND_OPTIMISER_HPP
#define __RMOL_COMMAND_OPTIMISER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/RMOL_Types.hpp>

namespace RMOL {

  /** Forward declarations. */
  //class Resource;
  class BucketHolder;
  class StudyStatManager;

  /** Class wrapping the optimisation algorithms. */
  class Optimiser {
  public:
    
    /** 
	Monte Carlo Integration algorithm.
	<br>Calculate the optimal protections for the set of buckets/classes
	given in input, and update those buckets accordingly.
	<br>The Monte Carlo Integration algorithm (see The Theory and 
	Practice of Revenue Management, by Kalyan T. Talluri and 
	Garret J. van Ryzin, Kluwer Academic Publishers, for the details) 
	is used. Hence, K is the number of random draws to perform.
	100 is a minimum for K, as statistics must be drawn from those
	random generations.
	<br>The cabin capacity is used to a double to allow for some
	overbooking.
     */
    static void optimalOptimisationByMCIntegration (const int K, 
                                                    const ResourceCapacity_T,
                                                    BucketHolder&,
                                                    BidPriceVector_T&);

    /**
       Monte Carlo Integartion algorithm with StudyStatManager.
    */
    static void optimalOptimisationByMCIntegration (const int K, 
                                                    const ResourceCapacity_T,
                                                    BucketHolder&,
                                                    BidPriceVector_T&,
                                                    StudyStatManager&);
    
    /**
       Dynamic Programming.
       <br>The cabin capacity is used to a double to allow for some
	overbooking.
     */
    static void optimalOptimisationByDP (const ResourceCapacity_T,
                                         BucketHolder&);
    
    /**
       EMRS algorithm.
       <br>The cabin capacity is used to a double to allow for some
	overbooking.
     */
    static void heuristicOptimisationByEmsr (const ResourceCapacity_T,
                                             BucketHolder&,
                                             BidPriceVector_T&);

    /**
       EMRS algorithm with StudyStatManager.
     */
    static void heuristicOptimisationByEmsr (const ResourceCapacity_T,
                                             BucketHolder&, BidPriceVector_T&,
                                             StudyStatManager&);

    /**
       EMRS-a algorithm.
       <br>The cabin capacity is used to a double to allow for some
	overbooking.
     */
    static void heuristicOptimisationByEmsrA (const ResourceCapacity_T,
                                              BucketHolder&);

    /** EMSR-a with sellup probability algorithm. 
        It is an implementation of the algorithm given by 
        Belobaba & Weatherford in the article 
        "Comparing decision rules that incorporate customer diversion in 
        perishable asset revenue management situations", Decision Sciences,
        1996.
     */
    static void heuristicOptimisationByEmsrAwithSellup (const ResourceCapacity_T,
                                                        BucketHolder&,
                                                        SellupProbabilityVector_T&);
    /**
       EMRS-b algorithm.
       <br>The cabin capacity is used to a double to allow for some
	overbooking.
     */
    static void heuristicOptimisationByEmsrB (const ResourceCapacity_T,
                                              BucketHolder&);

    /** Leg optimisation using Monte-Carlo Integration as a step in
        network optimisation. */
    static void legOptimisationByMC (const ResourceCapacity_T,
                                     BucketHolder&, BidPriceVector_T&);

  };
}
#endif // __RMOL_COMMAND_OPTIMISER_HPP
