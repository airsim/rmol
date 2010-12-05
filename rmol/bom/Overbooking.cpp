// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
// Boost Math
#include <boost/math/special_functions/pow.hpp>
#include <boost/math/special_functions/powm1.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/math/distributions/binomial.hpp>
#include <boost/math/distributions/normal.hpp>
// RMOL
#include <rmol/basic/BasConst_Overbooking.hpp>
#include <rmol/bom/Overbooking.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  Overbooking::Overbooking () :
    _overbookingPercentage (DEFAULT_OVERBOOKING_OVERBOOKING_PERCENTAGE),
    _capacity (DEFAULT_OVERBOOKING_CAPACITY), 
    _netBookings (DEFAULT_OVERBOOKING_NET_BOOKINGS),
    _loadFactor (DEFAULT_OVERBOOKING_LOAD_FACTOR),
    _noShowDistributionParameters (FldDistributionParameters (DEFAULT_OVERBOOKING_MEAN, 
                                                              DEFAULT_OVERBOOKING_STANDARD_DEVIATION)),
    _cancellationDistributionParameters (FldDistributionParameters (DEFAULT_OVERBOOKING_MEAN, 
                                                                    DEFAULT_OVERBOOKING_STANDARD_DEVIATION)),
    _remainingCancellationDistributionParameters (FldDistributionParameters (DEFAULT_OVERBOOKING_MEAN, 
                                                                             DEFAULT_OVERBOOKING_STANDARD_DEVIATION)),
    _demandDistributionParameters (FldDistributionParameters (DEFAULT_OVERBOOKING_MEAN, 
                                                              DEFAULT_OVERBOOKING_STANDARD_DEVIATION)) {
  }

  // //////////////////////////////////////////////////////////////////////
  Overbooking::Overbooking (const Overbooking& iOverbooking) :
    _overbookingPercentage (DEFAULT_OVERBOOKING_OVERBOOKING_PERCENTAGE),
    _capacity (DEFAULT_OVERBOOKING_CAPACITY), 
    _netBookings (DEFAULT_OVERBOOKING_NET_BOOKINGS),
    _loadFactor (DEFAULT_OVERBOOKING_LOAD_FACTOR),
    _noShowDistributionParameters (FldDistributionParameters (DEFAULT_OVERBOOKING_MEAN, 
                                                              DEFAULT_OVERBOOKING_STANDARD_DEVIATION)),
    _cancellationDistributionParameters (FldDistributionParameters (DEFAULT_OVERBOOKING_MEAN, 
                                                                    DEFAULT_OVERBOOKING_STANDARD_DEVIATION)),
    _remainingCancellationDistributionParameters (FldDistributionParameters (DEFAULT_OVERBOOKING_MEAN, 
                                                                             DEFAULT_OVERBOOKING_STANDARD_DEVIATION)),
    _demandDistributionParameters (FldDistributionParameters (DEFAULT_OVERBOOKING_MEAN, 
                                                              DEFAULT_OVERBOOKING_STANDARD_DEVIATION)) {
  }

  // //////////////////////////////////////////////////////////////////////
  Overbooking::Overbooking (const FldOverbookingPolicy& iPolicy) :
    _policy (iPolicy),
    _overbookingPercentage (DEFAULT_OVERBOOKING_OVERBOOKING_PERCENTAGE),
    _capacity (DEFAULT_OVERBOOKING_CAPACITY), 
    _netBookings (DEFAULT_OVERBOOKING_NET_BOOKINGS),
    _loadFactor (DEFAULT_OVERBOOKING_LOAD_FACTOR),
    _noShowDistributionParameters (FldDistributionParameters (DEFAULT_OVERBOOKING_MEAN, 
                                                              DEFAULT_OVERBOOKING_STANDARD_DEVIATION)),
    _cancellationDistributionParameters (FldDistributionParameters (DEFAULT_OVERBOOKING_MEAN, 
                                                                    DEFAULT_OVERBOOKING_STANDARD_DEVIATION)),
    _remainingCancellationDistributionParameters (FldDistributionParameters (DEFAULT_OVERBOOKING_MEAN, 
                                                                             DEFAULT_OVERBOOKING_STANDARD_DEVIATION)),
    _demandDistributionParameters (FldDistributionParameters (DEFAULT_OVERBOOKING_MEAN, 
                                                              DEFAULT_OVERBOOKING_STANDARD_DEVIATION)) {
  }

  // //////////////////////////////////////////////////////////////////////
  Overbooking::~Overbooking() {
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string Overbooking::describeShortKey() const {
    std::ostringstream oStr;
    oStr << _policy;
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string Overbooking::describeKey() const {
    return describeShortKey();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string Overbooking::toString() const {
    std::ostringstream oStr;
    oStr << describeShortKey()
         << ", " << _policy << ", " << _overbookingPercentage
         << ", " << _capacity  << ", " << _netBookings
         << ", " << _loadFactor
         << ", " << _noShowDistributionParameters
         << ", " << _cancellationDistributionParameters
         << ", " << _remainingCancellationDistributionParameters
         << ", " << _demandDistributionParameters
         << std::endl;
    
    return oStr.str();
  }   

  // //////////////////////////////////////////////////////////////////////
  void Overbooking::toStream (std::ostream& ioOut) const {
    ioOut << toString();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void Overbooking::fromStream (std::istream& ioIn) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string Overbooking::shortDisplay() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string Overbooking::display() const {
    std::ostringstream oStr;
    oStr << shortDisplay();
    oStr << "Policy = " << _policy
         << "; OB% = " << _overbookingPercentage
         << "; Capacity = " << _capacity
         << "; Net Bookings = " << _netBookings
         << "; Load Factor (LF) = " << _loadFactor
         << "; No-Show Distrib. Params = " << _noShowDistributionParameters
         << "; Cx Distrib. Params = " << _cancellationDistributionParameters
         << "; Rem. Cx Distrib. Params = " << _remainingCancellationDistributionParameters
         << "; Demand Distrib. Params = " << _demandDistributionParameters
         << std::endl;
    return oStr.str();
  }


  // ////////////// TODO: REMOVE THOSE CONSTANTS //////////
  //Parameters given by RMS User , for the prototype we set at
  //predefined values

  // = 0.5; to check the influence of this parameter , actually has 1 problem
  const double PRICE_OVER_DENIED_COST = 0.5;

  // = 150; 
  // const unsigned int CAPACITY = 150;

  // = CAPACITY*1.2;
  const double MAX_BOOKING_LIMIT = 180;

  // 0.8; // il faut calculer ro dans la requete
  // const double SHOW_RATE = 0.9 ;

  // 120;
  // const unsigned int NET_BOOKINGS = 120;
  // const int OVERBOOKING_METHOD_TYPE = 0;
	
	
  // service level parameters
  //pSHOW_RATEbability that we have to deny one or more passengers = 1/10.000
  const double SERVICE_LEVEL1 = 0.0001; 

  //the fraction of passengers who will be denied to board = 1 over 10.000
  const double SERVICE_LEVEL2 = 0.0001; 
  const int SERVICE_LEVEL_TYPE = 2;
	
  //parameters fSHOW_RATEm Forecaster 
  //demand average and deviation for a flight date
  // const double DEMAND_AVERAGE = 135;

  //100,10
  // const double DEMAND_DEVIATION = 10; 
  // const double NS_PERCENTAGE = 0.1;
  //10,2
  // const double NS_DEVIATION = 0.02;	
  // const double REMAINING_CANCELLATIONS_PERCENTAGE = 0.2;
  //20,5
  const double CANCELLATIONS_DEVIATION = 0.05;
  // ////////////// END OF TODO: REMOVE THOSE CONSTANTS //////////

  // //////////////////////////////////////////////////////////////////////
  FldDistributionParameters Overbooking::getOverbookingCalculation () const {
    FldDistributionParameters resultOBPercentage;
    
    const FldOverbookingPolicy::EN_Policy lPolicy = _policy.getPolicy();

    switch (lPolicy) {
    case FldOverbookingPolicy::HEUR: 
      resultOBPercentage = calculateHeuristic(); 
      break;
    case FldOverbookingPolicy::RISK:  
      resultOBPercentage = calculateRiskBased();
      break;
    case FldOverbookingPolicy::SL1: 
      resultOBPercentage = calculateServiceLevel();
      break;
    case FldOverbookingPolicy::HYBRID: 
      resultOBPercentage = calculateHybridPolicy();
      break;
    default: 
      resultOBPercentage = calculateHeuristic(); 
      break;
    }
    return resultOBPercentage;	
  }

  // 0 :  Method Heuristic take No show and cancellations infor 
  //to calculate the Overbooking percentage and deviation
  // //////////////////////////////////////////////////////////////////////
  FldDistributionParameters Overbooking::calculateHeuristic() const {
    FldDistributionParameters resultOBPercentage;

    const double lCancellationsPercentage = 
      _remainingCancellationDistributionParameters.getMean()
      * _netBookings / _capacity;

    // Overbooking average percentage
    const double lNoShow = _noShowDistributionParameters.getMean();
    const double lOBMean = (lNoShow + lCancellationsPercentage)
      / (1 - (lNoShow + lCancellationsPercentage));
    resultOBPercentage.setMean (lOBMean);

    // Overbooking deviation (heuristic)
    const double lNSStdDev = 
      _noShowDistributionParameters.getStandardDeviation();
    const double lNSVariance = lNSStdDev * lNSStdDev;

    const double lCxStdDev = 
      _cancellationDistributionParameters.getStandardDeviation();
    const double lCxVariance = lCxStdDev * lCxStdDev;

    const double lOBStdDev = sqrt (lNSVariance + lCxVariance);
    resultOBPercentage.setStandardDeviation (lOBStdDev);

    return resultOBPercentage ;
  }
	
  // 1 : Method Risk based  take No show and cancellations infor 
  //to calculate the Overbooking percentage and deviation
  // //////////////////////////////////////////////////////////////////////
  FldDistributionParameters Overbooking::calculateRiskBased() const {
    FldDistributionParameters resultOBPercentage;
			
    // take the Overbooking average and deviation by Heuristic method
    // in order to calculate some parameters ? show rate par exemple
    resultOBPercentage = calculateHeuristic();

    //Calculation SHOW_RATE : Shows rate = shows/net booking;
    //Calculation booking limit
    const double lBookingLimit = calculateBookingLimit ();

    const double lOBMean = lBookingLimit / _capacity - 1.0;
    resultOBPercentage.setMean (lOBMean);
	
    return resultOBPercentage;
  }

  //  2 : Service level policy	
  // //////////////////////////////////////////////////////////////////////
  FldDistributionParameters Overbooking::calculateServiceLevel() const {
    FldDistributionParameters resultOBPercentage;

    // No-Show Rate
    const double lNoShowMean = _noShowDistributionParameters.getMean();
    
    // 	service level 1
    unsigned int b = _capacity;
    switch (SERVICE_LEVEL_TYPE){
    case 1: default: {
      double test = serviceLevel1 (lNoShowMean, b, _capacity);
      while (test < SERVICE_LEVEL1) {
        b++; 
        test = serviceLevel1 (lNoShowMean, b, _capacity);
      }
      break;
    }
    case 2: {
      // service level 2
      double test = fractionServiceLevel2 (lNoShowMean, b, _capacity);
      while (test < SERVICE_LEVEL2){
        b++;
        test = fractionServiceLevel2 (lNoShowMean, b, _capacity);
      }
      break;		
    }	
    }
    resultOBPercentage.setMean (static_cast<double>(b) / _capacity - 1.0);
    // TODO: To be altered
    resultOBPercentage.setStandardDeviation (0);

    return resultOBPercentage;
  }
	
  //	3 : Hybrid policy
  // //////////////////////////////////////////////////////////////////////
  FldDistributionParameters Overbooking::calculateHybridPolicy() const {
    FldDistributionParameters resultOBPercentage;
    
    FldDistributionParameters resultOBPercentage_1 = calculateRiskBased();
    FldDistributionParameters resultOBPercentage_2 = calculateServiceLevel();
    
    //intermediate step to calculate the OB%
    const double lMean1 = resultOBPercentage_1.getMean();
    const double lMean2 = resultOBPercentage_2.getMean();
    const double lSDeviation1 = resultOBPercentage_1.getStandardDeviation();
    const double lSDeviation2 = resultOBPercentage_2.getStandardDeviation();
    
    //The hybrid method gets the minimum value
    if (lMean1 > lMean2)      {
      resultOBPercentage.setMean (lMean2);
      resultOBPercentage.setStandardDeviation (lSDeviation2);
      return resultOBPercentage;
    }
    assert (lMean1 <= lMean2);

    resultOBPercentage.setMean (lMean1);
    resultOBPercentage.setStandardDeviation (lSDeviation1);

    return resultOBPercentage;
  }
	
  //Distribution
  //binomial distribution, normal distribution
	
  // Service level 
  // in the Service Level policy method we can switch between service
  // level 1 and 2 in the Hybrid policy, because they are constraints
  // so we can choose one or the other or the two

	
  // useful functions
  // //////////////////////////////////////////////////////////////////////
  double Overbooking::calculateBookingLimit () const {
    double resultBookingLimit = _capacity;

    // Demand Distribution Parameters
    const double lDemandMean = _demandDistributionParameters.getMean();
    const double lDemandStdDev =
      _demandDistributionParameters.getStandardDeviation();
    
    boost::math::normal lNormalDistribution (lDemandMean,
                                             lDemandStdDev);
    
    // Algorithm
    double pNormal = 
      boost::math::cdf (boost::math::complement (lNormalDistribution,
                                                 _capacity));

    //  double pNormal = probabilityNormal (CAPACITY, DEMAND_AVERAGE, 
    //                                  DEMAND_DEVIATION);

    if  (PRICE_OVER_DENIED_COST >= 1 - pNormal) {
      resultBookingLimit = MAX_BOOKING_LIMIT;
      return resultBookingLimit; 
    }
    assert (PRICE_OVER_DENIED_COST < 1 - pNormal);

    pNormal =
      boost::math::cdf (boost::math::complement (lNormalDistribution,
                                                 _capacity - 1));

    //    pNormal = probabilityNormal (CAPACITY-1, DEMAND_AVERAGE, 
    //                           DEMAND_DEVIATION);

    const double lNoShowMean = _noShowDistributionParameters.getMean();

    double lProbability =
      (1 - pNormal) * (boost::math::powm1 (lNoShowMean, _capacity) + 1);

    int counter = 1;
    while (lProbability < PRICE_OVER_DENIED_COST && counter < 100) {
      ++counter;
      
      if (resultBookingLimit >= MAX_BOOKING_LIMIT) {
        return resultBookingLimit;

      } else {
        resultBookingLimit += 1.0; 
      }

      const unsigned int b = static_cast<unsigned int> (resultBookingLimit);

      pNormal =
        boost::math::cdf (boost::math::complement (lNormalDistribution,
                                                   b + 1));

      //  pNormal = probabilityNormal (b+1, DEMAND_AVERAGE, DEMAND_DEVIATION);

      assert (_capacity > 1);
      assert (b - _capacity + 1 > 0);
      // assert (b >= 0); (derived from the other two)


      /**
         The probability that the number of shows exceeds the leg/cabin
         physical capacity follows a binomial distribution, with the following
         parameters:<br>
         <ul>
          <li>"Probability of success (== no-show)": p == lNoShowMean</li>
          <li>"Number of trials (== bookings)": n == b</li>
          <li>"Number of successes (no-shows)": k == _capacity - 1</li>
         </ul> */
      boost::math::binomial lBinomialDistribution (lNoShowMean, b);
      lProbability += (1 + pNormal) * lNoShowMean
        * boost::math::pdf (lBinomialDistribution, _capacity-1);
    }
    return resultBookingLimit;
  }
	

  // Private useful functions

  // //////////////////////////////////////////////////////////////////////

  // pSHOW_RATEbability to deny one or more services
  // //////////////////////////////////////////////////////////////////////

  ////////////// Private functions for Servive level policies/////////////

  // service level 1 : cumulated probability of having no-shows
  //the constant SHOW_RATE can be changed in local variable in this function

  // //////////////////////////////////////////////////////////////////////
  double Overbooking::serviceLevel1 (const double iShowRate, 
                                     const int b, const int iCapacity) const {

    /**
       The probability that the number of shows exceeds the leg/cabin
       physical capacity follows a binomial distribution, with the following
       parameters:<br>
       <ul>
        <li>"Probability of success (== no-show)": p == iShowRate</li>
        <li>"Number of trials (== bookings)": n == b</li>
        <li>"Number of successes (no-shows)": k == iCapacity</li>
       </ul> */
    boost::math::binomial lBinomialDistribution (iShowRate, b);
    const double resultProbability =
      boost::math::cdf (lBinomialDistribution, iCapacity);
    
    return resultProbability;
  }

  //////////////fraction of customers who will be denied service///////////////
  double Overbooking::fractionServiceLevel2 (const double iShowRate, 
                                             const int b, const int C) const {
    double resultFraction = serviceLevel1 (iShowRate, b-1, _capacity-1) 
      - C / b / iShowRate * serviceLevel1 (iShowRate, b, _capacity);

    return resultFraction;
  } 
}
 
  
  /* where can I move this main function ?*/
  // int main(){
    //tester = a supprimer
  // double []test; 
  // overBookingCalculation tester = new overBookingCalculation("AY", "831");
  // test = tester.getOverbookingCalculation(2);

  // System.out.println("OB % = " + test[0]);
  // System.out.println("OB deviation = " + test[1]);
	       
  
 
