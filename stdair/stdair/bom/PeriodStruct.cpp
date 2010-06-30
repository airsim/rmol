// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <sstream>
#include <cassert>
// STDAIR
#include <stdair/basic/BasConst_Period_BOM.hpp>
#include <stdair/bom/PeriodStruct.hpp>

namespace stdair {
  // ////////////////////////////////////////////////////////////////////
  PeriodStruct_T::PeriodStruct_T ()
    : _dateRange (BOOST_DEFAULT_DATE_PERIOD), _dow () {
  }
  
  // ////////////////////////////////////////////////////////////////////
  PeriodStruct_T::PeriodStruct_T (const DatePeriod_T& iDateRange,
                                  const DoWStruct_T& iDoW)
    : _dateRange (iDateRange), _dow (iDoW) {
  }

  // ////////////////////////////////////////////////////////////////////
  PeriodStruct_T::PeriodStruct_T (const PeriodStruct_T& iPeriodStruct)
    : _dateRange (iPeriodStruct._dateRange), _dow (iPeriodStruct._dow) {
      
  }
    
  // ////////////////////////////////////////////////////////////////////
  const std::string PeriodStruct_T::describeShort() const {
    std::ostringstream ostr;
    ostr << _dateRange << ", " << _dow.describeShort ();
    return ostr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  const std::string PeriodStruct_T::describe() const {
    std::ostringstream ostr;
    ostr << _dateRange << ", " << _dow.describe ();
    return ostr.str();
  }

  // ////////////////////////////////////////////////////////////////////
  PeriodStruct_T PeriodStruct_T::
  addDateOffset (const DateOffset_T& iDateOffset) const {
    // Create a new date range by shifting the date range of this object with
    // iDateOffset.
    DatePeriod_T lNewDateRange = getDateRange();
    lNewDateRange.shift (iDateOffset);

    // Create a new DoWStruct by shifting the DoWStruct of this object with
    // iDateOffset.
    const long lNbOfDaysOffset = iDateOffset.days();
    const DoWStruct_T& lDoW = getDoW();
    const DoWStruct_T lNewDoW = lDoW.shift (lNbOfDaysOffset);

    return PeriodStruct_T (lNewDateRange, lNewDoW);
  }

  // ////////////////////////////////////////////////////////////////////
  PeriodStruct_T PeriodStruct_T::
  intersection (const PeriodStruct_T& iPeriodStruct) const {
    const DatePeriod_T lNewDateRange =
      _dateRange.intersection (iPeriodStruct._dateRange);
    const DoWStruct_T lNewDoW = _dow.intersection (iPeriodStruct._dow);
    
    return PeriodStruct_T (lNewDateRange, lNewDoW);
  }

  // ////////////////////////////////////////////////////////////////////
  const bool PeriodStruct_T::isValid () const {
    if (_dateRange.is_null() == false && _dow.isValid()) {
      return true;
    }
    return false;
  }
  
}
