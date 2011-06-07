#ifndef __RMOL_BOM_HISTORICALBOOKING_HPP
#define __RMOL_BOM_HISTORICALBOOKING_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/basic/StructAbstract.hpp>

namespace RMOL {    

  /**
   * @brief Structure keeping track, for a given class, of the number
   *        of historical bookings and of the censorship flag.
   */
  struct HistoricalBooking : public stdair::StructAbstract {
      
  public:
    // /////////////////// Getters ////////////////////////
    /** Getter for the booking. */
    const stdair::NbOfBookings_T& getNbOfBookings() const {
      return _numberOfBookings;
    }
    /** Getter for the unconstrained bookings. */
    const stdair::NbOfBookings_T& getUnconstrainedDemand() const {
      return _unconstrainedDemand;
    }
    /** Getter for the flag of censorship: "false" means that the bookings
        are not censored. */
    const stdair::Flag_T& getFlag() const {
      return _flag;
    }
    
  public:
    // ///////////////////// Setters /////////////////////
    /** Setter for the unconstraining demand. */
    void setUnconstrainedDemand (const stdair::NbOfBookings_T& iDemand) {
      _unconstrainedDemand = iDemand;
    }

    /** Setter for all parameters. */
    void setParameters (const stdair::NbOfBookings_T, const stdair::Flag_T);

  public:
    // ///////// Display Methods //////////
    /**
     * Dump a Business Object into an output stream.
     * @param ostream& the output stream
     * @return ostream& the output stream.
     */
    void toStream (std::ostream& ioOut) const;
    
    /**
     * Give a description of the structure (for display purposes).
     */
    const std::string describe() const;
      
    /**
     * Display on standard output.
     */
    void display () const;
      
  public:
    // /////////// Constructors and destructor. ////////////
    /**
     * Main constructor.
     */
    HistoricalBooking (const stdair::NbOfBookings_T, const stdair::Flag_T);
    /**
     * Default constructor.
     */
    HistoricalBooking();
    /**
     * Copy constructor.
     */
    HistoricalBooking (const HistoricalBooking&);
      
    /**
     * Destructor.
     */
    virtual ~HistoricalBooking();
      
  private:
    // //////////// Attributes ////////////
    /**
     * Number of historical bookings.
     */
    stdair::NbOfBookings_T _numberOfBookings;

    /**
     * Unconstrained historical bookings.
     */
    stdair::NbOfBookings_T _unconstrainedDemand;

    /**
     * Flag of censorship.
     */
    stdair::Flag_T _flag;
  };
}
#endif // __RMOL_BOM_HISTORICALBOOKING_HPP
