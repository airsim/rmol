#ifndef __RMOL_OVERBOOKING_HPP
#define __RMOL_OVERBOOKING_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
#include <vector>
// RMOL
#include <rmol/field/FldDistributionParameters.hpp>
#include <rmol/field/FldOverbookingPolicy.hpp>
#include <rmol/bom/DistributionParameterList.hpp>
#include <rmol/bom/BomAbstract.hpp>

namespace RMOL {

  /** Class holding the algorithms for the optimisation of the
      overbooking controls. */
  class Overbooking : public BomAbstract {
    /** Friend Classes
        <br>Those classes need to access the internal attributes of this object
        in order to construct and initialise it.*/
    friend class FacOverbooking;

  public:
    // ///////// Getters /////////
    /** Get the overbooking calculation policy. */
    const FldOverbookingPolicy& getPolicy () const {
      return _policy;
    }

    /** Get the overbooking percentage. */
    double getOverbookingPercentage () const {
      return _overbookingPercentage;
    }

    /** Get the load factor. */
    double getLoadFactor () const {
      return _loadFactor;
    }

    /** Get the capacity. */
    unsigned int getCapacity () const {
      return _capacity;
    }

    /** Get the net bookings. */
    unsigned int getNetBookings () const {
      return _netBookings;
    }


    /** Get the No-Show Distribution Parameters. */
    FldDistributionParameters getNoShowDistributionParameters () const {
      return _noShowDistributionParameters;
    }

    /** Get the Cancellation Distribution Parameters. */
    FldDistributionParameters getCancellationDistributionParameters () const {
      return _cancellationDistributionParameters;
    }

    /** Get the Remaining Cancellation Distribution Parameters. */
    FldDistributionParameters getRemainingCancellationDistributionParameters () const {
      return _remainingCancellationDistributionParameters;
    }

    /** Get the Demand Distribution Parameters. */
    FldDistributionParameters getDemandDistributionParameters () const {
      return _demandDistributionParameters;
    }

    // ///////// Setters /////////
    /** Set the overbooking calculation policy. */
    void setOverbookingPercentage (const FldOverbookingPolicy& iPolicy) {
      _policy = iPolicy;
    }

    /** Set the overbooking percentage. */
    void setOverbookingPercentage (const double iOverbookingPercentage) {
      _overbookingPercentage = iOverbookingPercentage;
    }

    /** Set the load factor. */
    void setLoadFactor (const double iLoadFactor) {
      _loadFactor = iLoadFactor;
    }

    /** Set the No-Show Distribution Parameters. */
    void setNoShowDistributionParameters (const FldDistributionParameters iNoShowDistributionParameters) {
      _noShowDistributionParameters = iNoShowDistributionParameters;
    }

    /** Set the Cancellation Distribution Parameters. */
    void setCancellationDistributionParameters (const FldDistributionParameters iCancellationDistributionParameters) {
      _cancellationDistributionParameters = iCancellationDistributionParameters;
    }

    /** Set the Remaining Cancellation Distribution Parameters. */
    void setRemainingCancellationDistributionParameters (const FldDistributionParameters iRemainingCancellationDistributionParameters) {
      _remainingCancellationDistributionParameters = 
        iRemainingCancellationDistributionParameters;
    }

    /** Set the Demand Distribution Parameters. */
    void setDemandDistributionParameters (const FldDistributionParameters iDemandDistributionParameters) {
      _demandDistributionParameters = iDemandDistributionParameters;
    }

    /** Set the capacity. */
    void setCapacity (const unsigned int iCapacity) {
      _capacity = iCapacity;
    }

    /** Set the net bookings. */
    void setNetBookings (const unsigned int iNetBookings) {
      _netBookings = iNetBookings;
    }

    
    // ///////////
    /** This function return the OB% with its standard deviation
        following the given choice of method*/
    FldDistributionParameters getOverbookingCalculation () const;
    
    /** This function calculates the OB% by the heuristic method */
    FldDistributionParameters calculateHeuristic() const;
    
    /** This function calculates the OB% by the cost-based method */
    FldDistributionParameters calculateRiskBased() const;
    
    /** This function calculates the OB% by the service level policies */
    FldDistributionParameters calculateServiceLevel() const;
    
    /** This function calculates the OB% by the Hybrid policy*/
    FldDistributionParameters calculateHybridPolicy() const;


  public:
    // ///////// Display methods ////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream&) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream&);

    /** Get the serialised version of the Place object. */
    std::string toString() const;

    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const;
    
    /** Display the full Place context. */
    const std::string display() const;

    /** Display a short Place context. */
    const std::string shortDisplay() const;


  private:
    /** Constructors. 
	<br>Protected to force the use of the Factory. */
    Overbooking ();
    Overbooking (const Overbooking&);
    Overbooking (const FldOverbookingPolicy&);

    /** Destructor. */
    virtual ~Overbooking();

    
  private:
    /** Calculate the booking limit. */
    double calculateBookingLimit () const;
    
    /** Calculate the normal probability. */
    double probabilityNormal (const int, const double, const double) const;
    
    /** Calculate the binomial probability. */
    double binomialProbability_F_b_s (const double, 
                                      const int, const int) const;
    /** Calculate the first service level. */
    double serviceLevel1 (const double, const int, const int) const;
    
    /** Calculate the fraction of service level 2. */
    double fractionServiceLevel2 (const double ,  const int , const int) const;

    
  private:
    // /////// Attributes //////////
    /** Overbooking Calculation Policy. */
    FldOverbookingPolicy _policy;

    /** Overbooking percentage. */
    double _overbookingPercentage;

    /** Capacity. */
    unsigned int _capacity;

    /** Net Bookings. */
    unsigned int _netBookings;

    /** Load Factor. */
    double _loadFactor;

    /** No-Show Distribution Parameters. */
    FldDistributionParameters _noShowDistributionParameters;

    /** Cancellation Distribution Parameters. */
    FldDistributionParameters _cancellationDistributionParameters;

    /** Remaining Cancellation Distribution Parameters. */
    FldDistributionParameters _remainingCancellationDistributionParameters;

    /** Demand Distribution Parameters. */
    FldDistributionParameters _demandDistributionParameters;
  };
}

#endif // __RMOL_OVERBOOKING_HPP
