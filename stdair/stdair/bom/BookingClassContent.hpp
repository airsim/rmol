#ifndef __STDAIR_BOM_BOOKINGCLASSCONTENT_HPP
#define __STDAIR_BOM_BOOKINGCLASSCONTENT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STDAIR 
#include <stdair/bom/BomContent.hpp>
#include <stdair/bom/BookingClassKey.hpp>

namespace stdair {

  /** Class representing the actual attributes for an airline booking class. */
  class BookingClassContent : public BomContent {
  public:
    // Type definitions.
    /** Definition allowing to retrieve the associated BOM key type. */
    typedef BookingClassKey_T Key_T;

  public:
    // /////////// Getters ////////////
    /** Get the booking class key. */
    const Key_T& getKey() const {
      return _key;
    }
    
    /** Get the booking code (part of the primary key). */
    const ClassCode_T& getClassCode() const {
      return _key.getClassCode();
    }

    /** Get the number of bookings of the bookingClass. */
    const NbOfBookings_T& getNbOfBookings() const {
      return _nbOfBookings;
    }

    /** Get the number of bookings (without cancellation counted)
        of the bookingClass. */
    const NbOfBookings_T& getTotalNbOfBookings() const {
      return _totalNbOfBookings;
    }

    /** Get the number of bookings at the last DCP(without
        cancellation counted) of the bookingClass. */
    const NbOfBookings_T& getLastDCPTotalNbOfBookings() const {
      return _lastDCPTotalNbOfBookings;
    }

    /** Get the unconstrained demand (last DCP) of the bookingClass. */
    const NbOfBookings_T& getUnconstrainedDemand () const {
      return _unconstrainedDemand;
    }

    /** Get the number of cancellations of the bookingClass. */
    const NbOfCancellations_T& getNbOfCancellations() const {
      return _nbOfCancellations;
    }

    /** Get the number of no-shows of the bookingClass. */
    const NbOfNoShows_T& getNbOfNoShows() const {
      return _nbOfNoShows;
    }

    /** Get the overbooking rate dedicated to the booking. */
    const OverbookingRate_T& getOverbookingRate() const {
      return _overbookingRate;
    }

    /** Get the list of censorship flags. */
    const CensorshipFlagList_T& getCensorshipFlagList() const {
      return _censorshipFlagList;
    }

    /** Get the current censorship flag. */
    const CensorshipFlag_T& getCurrentCensorshipFlag() const {
      return _currentCensorshipFlag;
    }

    /** Get the protection value. */
    const BookingLimit_T& getBookingLimit() const {
      return _bookingLimit;
    }

    /** Get the authorisation level value. */
    const AuthorizationLevel_T& getAuthorizationLevel () const {
      return _authorizationLevel;
    }

    /** Get the MAX value of AU. */
    const AuthorizationLevel_T& getMAX () const {
      return _MAX;
    }

    /** Get the MIN value of AU. */
    const AuthorizationLevel_T& getMIN () const {
      return _MIN;
    }
      
    /** Get the availability number. */
    const Availability_T& getAvailability() const {
      return _availability;
    }

    /** Get the revenue amount. */
    const Revenue_T& getRevenue() const {
      return _classRevenue;
    }

    /** Get the fare current value. */
    const Fare_T& getFare() const {
      return _fare;
    }

    /** Get the adjusted yield current value. */
    const Yield_T& getAdjustedYield() const {
      return _adjustedYield;
    }

    /** Get the yield current value. */
    const Yield_T& getYield() const {
      return _yield;
    }

    /** Get the remaining demand mean. */
    const NbOfBookings_T& getRemainingDemandMean() const {
      return _remainingDemandMean;
    }

    /** Get the remaining demand mean for the net booking product. */
    const NbOfBookings_T& getRemainingProductDemandMean() const {
      return _remainingProductDemandMean;
    }

    /** Get the remaining demand standard deviation. */
    const NbOfBookings_T& getRemainingDemandSD() const {
      return _remainingDemandSD;
    }

    /** Get the remaining demand standard deviation
        for the net booking product. */
    const NbOfBookings_T& getRemainingProductDemandSD() const {
      return _remainingProductDemandSD;
    }

  public:
    // /////////// Setters ////////////
    /** Set the booking limit. */
    void setBookingLimit (BookingLimit_T& iBookingLimit) {
      _bookingLimit = iBookingLimit;
    }

    /** Set the authorization level. */
    void setAuthorizationLevel (AuthorizationLevel_T& iAuthorizationLevel) {
      _authorizationLevel = iAuthorizationLevel;
    }

    /** Set the MAX value of AU. */
    void setMAX (const AuthorizationLevel_T& iMAX) {
      _MAX = iMAX;
    }

    /** Set the MIN value of AU. */
    void setMIN (const AuthorizationLevel_T& iMIN) {
      _MIN = iMIN;
    }

    /** Set the Availability number. */
    void setAvailability (Availability_T& iAvailability) {
      _availability = iAvailability;
    }

    /** Set the censorship flag status. */
    void setCensorshipFlagStatus (bool iFlagStatus) {
      _currentCensorshipFlag = iFlagStatus;
    }

    /** Set the fare value. */
    void setFare(Fare_T& iFare) {
      _fare = iFare;
    }

    /** Set the adjusted fare value. */
    void setAdjustedYield(Yield_T& iYield) {
      _adjustedYield = iYield;
    }

    /** Set the yield value. */
    void setYield(Yield_T& iYield) {
      _yield = iYield;
    }

    /** Set the unconstrained demand. */
    void setUnconstrainedDemand (NbOfBookings_T& iDemand) {
      _unconstrainedDemand = iDemand;
    }

    /** Set the total bookings for the DCP. */
    void setDCPTotalNbOfBookings (NbOfBookings_T& iBookings) {
      _lastDCPTotalNbOfBookings = iBookings;
    }

    /** Set the remaining demand mean. */
    void setRemainingDemandMean (NbOfBookings_T&);

    /** Set the remaining demand mean for the net booking product. */
    void setRemainingProductDemandMean (NbOfBookings_T& iMean) {
      _remainingProductDemandMean = iMean;
    }

    /** Set the remaining demand standard deviation. */
    void setRemainingDemandSD (NbOfBookings_T&);

    /** Set the remaining demand standard deviation. */
    void setRemainingProductDemandSD (NbOfBookings_T& iSD) {
      _remainingProductDemandSD = iSD;
    }

  public:
    // /////////// Display support methods /////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    virtual void toStream (std::ostream& ioOut) const = 0;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    virtual void fromStream (std::istream& ioIn) = 0;

   /** Get the serialised version of the Business Object. */
    virtual std::string toString() const = 0;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const { return _key.toString(); }

    
  protected:
    /** Default constructors. */
    BookingClassContent (const Key_T&);
    BookingClassContent (const BookingClassContent&);
    /** Destructor. */
    ~BookingClassContent();

  public:
    // for AIRINV Test
    stdair::SubclassCode_T _subclassCode;
    stdair::AuthorizationLevel_T _cumulatedProtection;
    stdair::AuthorizationLevel_T _protection;
    stdair::OverbookingRate_T _noShowPercentage;
    stdair::OverbookingRate_T _overbookingPercentage;
    stdair::NbOfBookings_T _groupNbOfBookings;
    stdair::NbOfBookings_T _groupPendingNbOfBookings;
    stdair::NbOfBookings_T _staffNbOfBookings;
    stdair::NbOfBookings_T _wlNbOfBookings;
    stdair::NbOfBookings_T _etb;
    stdair::Availability_T _netClassAvailability;
    stdair::Availability_T _segmentAvailability;
    stdair::Availability_T _netRevenueAvailability;
    
  protected:
    // Attributes
    /** The key of both structure and content objects. */
    Key_T _key;
          
    /** Number of current bookings in the booking. */
    NbOfBookings_T _nbOfBookings;

    /** Total number of bookings (without substraction of cancellation). */
    NbOfBookings_T _totalNbOfBookings;

    /** Total number of bookings at the last DCP (without
        substraction of cancellation). */
    NbOfBookings_T _lastDCPTotalNbOfBookings;
      
    /** Unconstraining demnd value (last RMS Computation).*/
    NbOfBookings_T _unconstrainedDemand;

    /** Number of cancelled demands. */
    NbOfCancellations_T _nbOfCancellations;

    /** Number of no-shows. */
    NbOfNoShows_T _nbOfNoShows;

    /** Number of available seats. */
    Availability_T _availability;

    /** Total Revenue of the booking. */
    Revenue_T _classRevenue;

    /** Current Censorship flag which indicates whether the demand
        is censored. */
    CensorshipFlag_T _currentCensorshipFlag;

    /** List of censorship flags which indicates whether the demand
        is censored (one flag per DCP). */
    CensorshipFlagList_T _censorshipFlagList;

    /** Value of the booking limit of the booking. */
    BookingLimit_T _bookingLimit;

    /** Value of the authorization level of the booking. */
    AuthorizationLevel_T _authorizationLevel;

    /** MAX of Authorization Level (AU). */
    AuthorizationLevel_T _MAX;

    /** MIN of Authorization Level (AU). */
    AuthorizationLevel_T _MIN;

    /** Rate of allowed overbooking. */
    OverbookingRate_T _overbookingRate;

    /** Current Fare value of the booking. */
    Fare_T _fare;

    /** Current Adjusted Fare value of the booking. */
    Yield_T _adjustedYield;

    /** Current Yield value of the booking. */
    Yield_T _yield;

    /** Temporary attributes just for the forecaster prototype. */
    /** Remaining demand mean for the whole booking. */
    NbOfBookings_T _remainingDemandMean;
      
    /** Remaining demand mean for the product corresponding to this booking
        (excluding (OnDs)). */
    NbOfBookings_T _remainingProductDemandMean;
      
    /** Remaining demand standrad deviation for the whole booking. */
    NbOfBookings_T _remainingDemandSD;

    /** Remaining demand standard deviation for the product
        corresponding to this booking (excluding (OnDs)). */
    NbOfBookings_T _remainingProductDemandSD;

  };

}
#endif // __STDAIR_BOM_BOOKINGCLASSCONTENT_HPP

