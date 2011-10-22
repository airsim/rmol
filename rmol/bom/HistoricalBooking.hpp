#ifndef __RMOL_BOM_HISTORICALBOOKING_HPP
#define __RMOL_BOM_HISTORICALBOOKING_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
<<<<<<< HEAD
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
=======
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
>>>>>>> 0.24
      return _unconstrainedDemand;
    }
    /** Getter for the flag of censorship: "false" means that the bookings
        are not censored. */
<<<<<<< HEAD
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
=======
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
>>>>>>> 0.24
  };
}
#endif // __RMOL_BOM_HISTORICALBOOKING_HPP
