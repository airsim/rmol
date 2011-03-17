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
#include <stdair/basic/BasParserTypes.hpp>
// Airrac
#include <airrac/AIRRAC_Types.hpp>


namespace AIRRAC {

  /** Utility Structure for the parsing of Flight-Date structures. */
  struct YieldRuleStruct : public stdair::StructAbstract {

    /** Constructor. */
    YieldRuleStruct ();
    
    /** Set the date from the staging details. */
    stdair::Date_T getDate() const;

    /** Set the time from the staging details. */
    stdair::Duration_T getTime() const;
  
    /** Give a description of the structure (for display purposes). */
    const std::string describe() const;

    /** Get the size of the airline code list. */
    const unsigned int getAirlineListSize () const {
      return _airlineCodeList.size();
    }

    /** Get the size of the class code list. */
    const unsigned int getClassCodeListSize () const {
      return _classCodeList.size();
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

    /** Yield ID. */
    YieldID_T _yieldId;

    /** Origin. */
    stdair::AirportCode_T _origin;

    /** Destination. */
    stdair::AirportCode_T _destination;

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
