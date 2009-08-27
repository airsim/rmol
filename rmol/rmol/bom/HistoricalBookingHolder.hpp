#ifndef __RMOL_BOM_HISTORICALBOOKINGHOLDER_HPP
#define __RMOL_BOM_HISTORICALBOOKINGHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
#include <vector>
// RMOL 
#include <rmol/RMOL_Types.hpp>
#include <rmol/bom/StructAbstract.hpp>

namespace RMOL {

  /** Forward declaration. */
  struct HistoricalBooking;
    
  /** Define a vector (ordered list) of N HistoricalBookings. */
  typedef std::vector<HistoricalBooking> HistoricalBookingVector_T;
    
  /** Holder of a HistoricalBookingList object (for memory allocation and
      recollection purposes). */
  struct HistoricalBookingHolder : public StructAbstract {
      
  public:
    // ////// Getters //////
    /** Get number of flights. */
    const short getNumberOfFlights () const;

    /** Get number of uncensored booking data. */
    const short getNumberOfUncensoredData () const;

    /** Get number of uncensored bookings. */
    const double getNumberOfUncensoredBookings () const;

    /** Get standard deviation of uncensored bookings. */
    const double getUncensoredStandardDeviation
                             (const double iMeanOfUncensoredBookings,
                              const short iNumberOfUncensoredData) const;

    /** Get mean of historical demand. */
    const double getMeanDemand () const;

    /** Get standard deviation of demand. */
    const double getStandardDeviation (const double) const;

    /** Get the list of flags of need to be unconstrained. */
    const std::vector<bool> getListOfToBeUnconstrainedFlags() const;

    /** Get the historical booking of the (i+1)-th flight. */
    const double getHistoricalBooking (const short i) const;

    /** Get the unconstraining demand of the (i+1)-th flight. */
    const double getUnconstrainedDemand (const short i) const;

    /** Get the unconstraining demand of the first flight. */
    const double getUnconstrainedDemandOnFirstElement () const {
      return getUnconstrainedDemand (0);
    }

    /** Calculate the expected demand. */
    const double calculateExpectedDemand (const double,
                                          const double,
                                          const short,
                                          const double) const;
      
    /** Set the expected historical demand of the (i+1)-th flight. */
    void setUnconstrainedDemand (const double iExpectedDemand,
                                 const short i);

    /** Add a HistoricalBooking object to the holder. */
    void addHistoricalBooking (const HistoricalBooking iHistoricalBooking);
      
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream
        @return ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    // ///////// Display Methods //////////
    /** Give a description of the structure (for display purposes). */
    const std::string describe() const;
      
    /** Display on standard output. */
    void display () const;
      
    /** Destructor. */
    virtual ~HistoricalBookingHolder();
      
  public:
    /** Constructor.
        <br>Protected to force the use of the Factory. */
    HistoricalBookingHolder ();

  private:
      
    /** The list of (N) buckets/classes. */
    HistoricalBookingVector_T _historicalBookingVector;
      
  };
}
#endif // __RMOL_BOM_HISTORICALBOOKINGHOLDER_HPP
  
