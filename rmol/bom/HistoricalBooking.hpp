#ifndef __RMOL_BOM_HISTORICALBOOKING_HPP
#define __RMOL_BOM_HISTORICALBOOKING_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/bom/StructAbstract.hpp>

namespace RMOL {
    
  /** HistoricalBooking for a given class and the flag of censorship.
   */
  struct HistoricalBooking : public StructAbstract {
      
  public:
    // Getters
    /** Getter for the booking. */
    const double& getNumberOfBookings() const {
      return _numberOfBookings;
    }
    /** Getter for the unconstrained bookings. */
    const double& getUnconstrainedDemand() const {
      return _unconstrainedDemand;
    }
    /** Getter for the flag of censorship: "false" means that the bookings
        are not censored. */
    const bool& getFlag() const {
      return _flag;
    }

    /** Setter for the unconstraining demand. */
    void setUnconstrainedDemand (const double iDemand) {
      _unconstrainedDemand = iDemand;
    }

    /** Setter for all parameters (no of bkgs, flag). */
    void setParameters (const double, const bool);
      
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream
        @return ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    // ///////// Display Methods //////////
    /** Give a description of the structure (for display purposes). */
    const std::string describe() const;
      
    /** Display on standard output. */
    void display () const;
      
    /** Destructors. */
    virtual ~HistoricalBooking();
      
  public:
    /** Constructors.
        <br>Protected to force the use of the Factory. */
    HistoricalBooking ();

    HistoricalBooking (const HistoricalBooking&);
      
  private:
    /** Number of historical bookings. */
    double _numberOfBookings;

    /** Unconstrained historical bookings. */
    double _unconstrainedDemand;

    /** Flag of censorship. */
    bool _flag;
  };
}
#endif // __RMOL_BOM_HISTORICALBOOKING_HPP
