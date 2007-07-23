// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <sstream>
// LATUS COM
#include <latus/com/bom/PeriodKey.hpp>


namespace LATUS {

  namespace COM {

    // //////////////////////////////////////////////////////////////////////
    PeriodKey_T::PeriodKey_T (const DateTime_T& iStartDate,
                              const DateTime_T& iEndDate, const DOW_T& iDow)
      : startDate (iStartDate), endDate (iEndDate), dow (iDow) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string PeriodKey_T::describe() const {
      std::ostringstream ostr;
      ostr << startDate << "; " << endDate << "; ";
      for (DOW_T::const_iterator itDay = dow.begin(); itDay != dow.end();
           itDay++) { ostr << *itDay; }
      ostr << "; ";
      return ostr.str();
    }

  }

}
