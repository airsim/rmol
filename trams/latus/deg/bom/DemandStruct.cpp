// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/service/Logger.hpp>
// LATUS Discrete-Event Generation (DEG)
#include <latus/deg/bom/DemandStruct.hpp>

namespace LATUS {

  namespace DEG {

    // //////////////////////////////////////////////////////////////////////
    DemandStruct_T::DemandStruct_T () {
    }

    // //////////////////////////////////////////////////////////////////////
    COM::DateTime_T DemandStruct_T::getDate() const {
      return COM::DateTime_T (_itYear, _itMonth, _itDay);
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string DemandStruct_T::describe() const {
      std::ostringstream ostr;
      ostr << _origin << "-" << _destination << " " << _departureDate
           << ", " << _wtp << " " << _currency
           << ", " << _demandMean << " " << _demandStdDev << std::endl;

      return ostr.str();
    }

  }

}
