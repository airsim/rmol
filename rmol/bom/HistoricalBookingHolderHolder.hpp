#ifndef __RMOL_BOM_HISTORICALBOOKINGVECTORHOLDER_HPP
#define __RMOL_BOM_HISTORICALBOOKINGVECTORHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
#include <vector>
// RMOL 
// #include <rmol/RMOL_Types.hpp>
#include <rmol/bom/StructAbstract.hpp>

namespace RMOL {

  /** Forward declaration. */
  struct HistoricalBookingHolder;
    
  /** Define a vector (ordered list) of N HistoricalBookings. */
  typedef std::vector<HistoricalBookingHolder> 
                                       HistoricalBookingHolderHolder_T;
    
  /** Holder of a HistoricalBookingList object (for memory allocation and
      recollection purposes). */
  struct HistoricalBookingHolderHolder : public StructAbstract {
      
  public:
    // ////// Getters //////
    /** Get number of similar flights. */
    const int getNumberOfSimilarFlights () const;

//     /** Get number of uncensored booking data. */
//     const short getNumberOfUncensoredData () const;

//     /** Get number of uncensored bookings. */
//     const double getNumberOfUncensoredBookings () const;

//     /** Get standard deviation of uncensored bookings. */
//     const double getUncensoredStandardDeviation
//                              (const double iMeanOfUncensoredBookings,
//                               const short iNumberOfUncensoredData) const;

//     /** Get mean of historical demand. */
//     const double getMeanDemand () const;

//     /** Get standard deviation of demand. */
//     const double getStandardDeviation (const double) const;

//     /** Get the list of flags of need to be unconstrained. */
//     const std::vector<bool> getListOfToBeUnconstrainedFlags() const;

    /** Get the historical booking Vector of the i-th similar flight. */
//     HistoricalBookingHolder& getHistoricalBookingVector (const int i) const;

//     /** Get the unconstraining demand of the (i+1)-th flight. */
//     const double getUnconstrainedDemand (const short i) const;

//     /** Get the unconstraining demand of the first flight. */
//     const double getUnconstrainedDemandOnFirstElement () const {
//       return getUnconstrainedDemand (0);
//     }

//     /** Calculate the expected demand. */
//     const double calculateExpectedDemand (const double,
//                                           const double,
//                                           const short,
//                                           const double) const;
      
//     /** Set the expected historical demand of the (i+1)-th flight. */
//     void setUnconstrainedDemand (const double iExpectedDemand,
//                                  const short i);

//     /** Add a HistoricalBooking object to the holder. */
//     void addHistoricalBooking (const HistoricalBooking iHistoricalBooking);
      
//     /** Dump a Business Object into an output stream.
//         @param ostream& the output stream
//         @return ostream& the output stream. */
//     void toStream (std::ostream& ioOut) const;

//     // ///////// Display Methods //////////
//     /** Give a description of the structure (for display purposes). */
//     const std::string describe() const;
      
//     /** Display on standard output. */
//     void display () const;
      
    /** Destructor. */
    virtual ~HistoricalBookingHolderHolder();
      
  public:
    /** Constructor.
        <br>Protected to force the use of the Factory. */
    HistoricalBookingHolderHolder ();

  private:
      
    /** The list of (N) similar flights. */
    HistoricalBookingHolderHolder_T _historicalBookingHolderHolder;
      
  };
}
#endif // __RMOL_BOM_HISTORICALBOOKINGVECTORHOLDER_HPP
  
