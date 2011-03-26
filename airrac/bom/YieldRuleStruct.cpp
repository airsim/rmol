// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/service/Logger.hpp>
// AIRRAC
#include <airrac/AIRRAC_Types.hpp>
#include <airrac/bom/YieldRuleStruct.hpp>

namespace AIRRAC {

  // //////////////////////////////////////////////////////////////////////
  YieldRuleStruct::YieldRuleStruct()
    : _yieldId(0), 
      _origin(""), 
      _destination(""),
      _dateRangeStart (stdair::DEFAULT_DATE),
      _dateRangeEnd (stdair::DEFAULT_DATE),
      _timeRangeStart (stdair::DEFAULT_EPSILON_DURATION),
      _timeRangeEnd (stdair::DEFAULT_EPSILON_DURATION),
      _yield(0),
      _cabinCode(""),
      _pos(""), 
      _channel(""),
      _airlineCode(""), 
      _classCode("") { 
  }

  // //////////////////////////////////////////////////////////////////////
  YieldRuleStruct::~YieldRuleStruct() {
  }

  // //////////////////////////////////////////////////////////////////////
  stdair::Date_T YieldRuleStruct::getDate() const {
    _itYear.check(); _itMonth.check(); _itDay.check();
    return stdair::Date_T (_itYear._value, _itMonth._value, _itDay._value);
  }

  // //////////////////////////////////////////////////////////////////////
  stdair::Duration_T YieldRuleStruct::getTime() const {
    _itHours.check(); _itMinutes.check(); _itSeconds.check();
    return boost::posix_time::hours (_itHours._value)
      + boost::posix_time::minutes (_itMinutes._value)
      + boost::posix_time::seconds (_itSeconds._value);
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string YieldRuleStruct::describe() const {
    std::ostringstream oStr;
    oStr << "YieldRule: " << _yieldId << ", ";

    oStr << _origin << "-" << _destination << " ("
         << _pos << "), " << _channel << ", [";
    oStr << _dateRangeStart << "/" << _dateRangeEnd << "] - ["
         << boost::posix_time::to_simple_string (_timeRangeStart) << "/"
         << boost::posix_time::to_simple_string (_timeRangeEnd) << "], ";

    oStr << _cabinCode << ", " << _yield << " EUR, ";

    // Sanity check
    assert (_airlineCodeList.size() == _classCodeList.size());

    // Browse the class-pathes
    unsigned short idx = 0;
    stdair::ClassList_StringList_T::const_iterator itClass =
      _classCodeList.begin();
    for (stdair::AirlineCodeList_T::const_iterator itAirline =
           _airlineCodeList.begin();
         itAirline != _airlineCodeList.end(); ++itAirline, ++itClass, ++idx) {
      if (idx != 0) {
        oStr << " - ";
      }
      const stdair::AirlineCode_T lAirlineCode = *itAirline;
      const stdair::ClassCode_T lClassCode = *itClass;
      oStr << lAirlineCode << " / " << lClassCode;
    }

    return oStr.str();
  }
}
