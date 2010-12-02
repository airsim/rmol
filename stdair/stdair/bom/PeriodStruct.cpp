// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <cassert>
// StdAir
#include <stdair/basic/BasConst_Period_BOM.hpp>
#include <stdair/bom/PeriodStruct.hpp>

namespace stdair {
  
  // ////////////////////////////////////////////////////////////////////
  PeriodStruct::PeriodStruct ()
    : _dateRange (BOOST_DEFAULT_DATE_PERIOD), _dow () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  PeriodStruct::PeriodStruct (const DatePeriod_T& iDateRange,
                              const DoWStruct& iDoW)
    : _dateRange (iDateRange), _dow (iDoW) {
  }

  // ////////////////////////////////////////////////////////////////////
  PeriodStruct::PeriodStruct (const PeriodStruct& iPeriodStruct)
    : _dateRange (iPeriodStruct._dateRange), _dow (iPeriodStruct._dow) {
      
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string PeriodStruct::describeShort() const {
    std::ostringstream ostr;
    ostr << _dateRange << ", " << _dow.describeShort ();
    return ostr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string PeriodStruct::describe() const {
    std::ostringstream ostr;
    ostr << _dateRange << ", " << _dow.describe ();
    return ostr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  PeriodStruct PeriodStruct::
  addDateOffset (const DateOffset_T& iDateOffset) const {
    // Create a new date range by shifting the date range of this object with
    // iDateOffset.
    DatePeriod_T lNewDateRange = getDateRange();
    lNewDateRange.shift (iDateOffset);

    // Create a new DoWStruct by shifting the DoWStruct of this object with
    // iDateOffset.
    const long lNbOfDaysOffset = iDateOffset.days();
    const DoWStruct& lDoW = getDoW();
    const DoWStruct lNewDoW = lDoW.shift (lNbOfDaysOffset);

    return PeriodStruct (lNewDateRange, lNewDoW);
  }

  // ////////////////////////////////////////////////////////////////////
  PeriodStruct PeriodStruct::
  intersection (const PeriodStruct& iPeriodStruct) const {
    const DatePeriod_T lNewDateRange =
      _dateRange.intersection (iPeriodStruct._dateRange);
    const DoWStruct lNewDoW = _dow.intersection (iPeriodStruct._dow);
    
    return PeriodStruct (lNewDateRange, lNewDoW);
  }

  // ////////////////////////////////////////////////////////////////////
  const bool PeriodStruct::isValid () const {
    if (_dateRange.is_null() == false && _dow.isValid()) {
      return true;
    }
    return false;
  }
  
}
