#ifndef __AIRRAC_BOM_YIELDRULESTRUCT_HPP
#define __AIRRAC_BOM_YIELDRULESTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_date_time_types.hpp>
#include <stdair/stdair_demand_types.hpp>
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/basic/BasParserHelperTypes.hpp>
// AirRAC
#include <airrac/AIRRAC_Types.hpp>

namespace AIRRAC {

  /**
   * @brief Utility Structure for the parsing of Flight-Date structures.
   */
  struct YieldRuleStruct : public stdair::StructAbstract {
  public:
    // /////////////////// Initialisation / Destruction /////////////////////
    /**
     * Constructor.
     */
    YieldRuleStruct();

    /**
     * Destructor.
     */
    ~YieldRuleStruct();
    
  public:
    // ////////////////////// Getters /////////////////////////
    /** Get the yield ID. */
    AIRRAC::YieldID_T getYieldID () const {
      return _yieldId;
    }
    
    /** Get the origin. */
    stdair::AirportCode_T getOrigin () const {
      return _origin;
    }
    
    /** Get the destination. */
    stdair::AirportCode_T getDestination () const {
      return _destination;
    }

    /** Get the trip type. */
    stdair::TripType_T getTripType () const {
      return _tripType;
    }

    /** Get the date range start. */
    stdair::Date_T getDateRangeStart () const {
      return _dateRangeStart;
    }

    /** Get the date range end. */
    stdair::Date_T getDateRangeEnd () const {
      return _dateRangeEnd;
    }

    /** Get the time range start. */
    stdair::Duration_T getTimeRangeStart () const {
      return _timeRangeStart;
    }

    /** Get the time range end. */
    stdair::Duration_T getTimeRangeEnd () const {
      return _timeRangeEnd;
    }

    /** Get the cabin code. */
    stdair::CabinCode_T getCabinCode () const {
      return _cabinCode;
    }
    
    /** Get the point-of-sale. */
    const stdair::CityCode_T getPOS () const {
      return _pos;
    }

    /** Get the channel. */
    stdair::ChannelLabel_T getChannel () const {
      return _channel;
    }

    /** Get the yield. */
    stdair::YieldValue_T getYield () const {
      return _yield;
    }

    /** Get the airline code. */
    stdair::AirlineCode_T getAirlineCode () const {
      return _airlineCode;
    }

    /** Get the class code. */
    stdair::ClassCode_T getClassCode () const {
      return _classCode;
    }

    /** Get the size of the airline code list. */
    const unsigned int getAirlineListSize () const {
      return _airlineCodeList.size();
    }

    /** Get the size of the class code list. */
    const unsigned int getClassCodeListSize () const {
      return _classCodeList.size();
    }

    /** Get the airline code list. */
    stdair::AirlineCodeList_T getAirlineList () const {
      return _airlineCodeList;
    }

    /** Get the class code list. */
    stdair::ClassList_StringList_T getClassCodeList () const {
      return _classCodeList;
    }

  public: 
    // ////////////////////// Display support methods /////////////////////////
    /** Calculate the date from the staging details. */
    stdair::Date_T calculateDate() const;

    /** Calculate the time from the staging details. */
    stdair::Duration_T calculateTime() const;
  
    /** Give a description of the structure (for display purposes). */
    const std::string describe() const;

  public:
    // ///////// Setters //////////
    /** Set the yield ID. */
    void setYieldID (const AIRRAC::YieldID_T iYieldID) {
      _yieldId = iYieldID;
    }

    /** Set the origin. */
    void setOrigin (const stdair::AirportCode_T& iOrigin) {
      _origin = iOrigin;
    }
    
    /** Set the destination. */
    void setDestination (const stdair::AirportCode_T& iDestination) {
      _destination = iDestination;
    }

    /** Set the trip type. */
    void setTripType (const stdair::TripType_T& iTripType) {
      _tripType = iTripType;
    }

    /** Set the date range start. */
    void setDateRangeStart (const stdair::Date_T& iDateRangeStart) {
      _dateRangeStart = iDateRangeStart;
    }

    /** Set the date range end. */
    void setDateRangeEnd (const stdair::Date_T& iDateRangeEnd) {
      _dateRangeEnd = iDateRangeEnd;
    }

    /** Set the time range start. */
    void setTimeRangeStart (const stdair::Duration_T& iTimeRangeStart) {
      _timeRangeStart = iTimeRangeStart;
    }

    /** Set the time range end. */
    void setTimeRangeEnd (const stdair::Duration_T& iTimeRangeEnd) {
      _timeRangeEnd = iTimeRangeEnd;
    }

    /** Set the cabin code. */
    void setCabinCode (const stdair::CabinCode_T& iCabinCode) {
      _cabinCode = iCabinCode;
    }

    /** Set the point-of-sale. */
    void setPOS (const stdair::CityCode_T& iPOS) {
      _pos = iPOS;
    }

    /** Set the channel. */
    void setChannel (const stdair::ChannelLabel_T& iChannel) {
      _channel = iChannel;
    }

    /** Set the yield. */
    void setYield(const stdair::YieldValue_T& iYield) {
      _yield = iYield;
    }

    /** Set the airline code. */
    void setAirlineCode (const stdair::AirlineCode_T&  iAirlineCode) {
      _airlineCode = iAirlineCode;
    }

    /** Set the class code. */
    void setClassCode (const stdair::ClassCode_T& iClassCode) {
      _classCode = iClassCode;
    }

    /** Empty the airline code list.*/
    void clearAirlineCodeList () {
      _airlineCodeList.clear();
    }

    /** Empty the class code list.*/
    void clearClassCodeList () {
      _classCodeList.clear();
    }

    /** Add an airline code to the list.*/
    void addAirlineCode (const stdair::AirlineCode_T& iAirlineCode)  {
      _airlineCodeList.push_back (iAirlineCode);
    }

    /** Add a class code to the list.*/
    void addClassCode (const stdair::ClassCode_T& iClassCode) {
      _classCodeList.push_back (iClassCode);
    }

  public:
    // ////////////////// Attributes /////////////////
    /** Staging Date. */
    stdair::year_t _itYear;
    stdair::month_t _itMonth;
    stdair::day_t _itDay;
      
    /** Staging Time. */
    //long _itHours;
    stdair::hour_t _itHours;
    stdair::minute_t _itMinutes;
    stdair::second_t _itSeconds;

  private:
    // ////////////////// Attributes /////////////////   

    /** Yield ID. */
    YieldID_T _yieldId;

    /** Origin. */
    stdair::AirportCode_T _origin;

    /** Destination. */
    stdair::AirportCode_T _destination; 

    /** Type of trip (RT=round-trip, OW=one way). */
    stdair::TripType_T _tripType;

    /** Start Range date available for this yield rule.*/
    stdair::Date_T _dateRangeStart;

    /** Start Range date available for this yield rule.*/
    stdair::Date_T _dateRangeEnd;
    
    /** Start time from the time range available for this yield rule.*/
    stdair::Duration_T _timeRangeStart;
     
    /** End time from the time range available for this yield rule.*/
    stdair::Duration_T _timeRangeEnd;
    
    /** Yield.*/
    stdair::YieldValue_T _yield;

    /** Cabin code. */
    stdair::CabinCode_T _cabinCode;

    /** Point-of-sale. */
    stdair::CityCode_T _pos;
    
    /** Channel distribution. */
    stdair::ChannelLabel_T _channel;

    /** Airline code */
    stdair::AirlineCode_T _airlineCode;

    /** Code */
    stdair::ClassCode_T _classCode;

    /** Airline Code List*/
    stdair::AirlineCodeList_T _airlineCodeList;

    /** Class Code List*/
    stdair::ClassList_StringList_T _classCodeList;
  };

}
#endif // __AIRRAC_BOM_YIELDRULESTRUCT_HPP
