// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
// LATUS Common
#include <latus/com/basic/BasConst_Period_BOM.hpp>
#include <latus/com/bom/LegDate.hpp>
// LATUS TSP
#include <latus/tsp/bom/LegStruct.hpp>

namespace LATUS {

  namespace TSP {

    // //////////////////////////////////////////////////////////////////////
    LegStruct_T::LegStruct_T () : _dateOffSet (COM::DEFAULT_DATE_OFFSET) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string LegStruct_T::describe() const {
      std::ostringstream ostr;
      ostr << "    " << _boardPoint << " / " << _boardTime
           << " -- " << _offPoint << " / " << _offTime
           << " --> " << _elapsed
           << std::endl;
      for (LegCabinStructList_T::const_iterator itCabin = _cabinList.begin();
           itCabin != _cabinList.end(); itCabin++) {
        const LegCabinStruct_T& lCabin = *itCabin;
        ostr << lCabin.describe();
      }
      ostr << std::endl;
    
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    void LegStruct_T::fill (const COM::DateTime_T& iRefDate,
                            COM::LegDate& ioLegDate) const {
      // Set the Off Point
      ioLegDate.setOffPoint (_offPoint);

      // Set the Board Date
      ioLegDate.setBoardDate (iRefDate);

      // Set the Board Time
      ioLegDate.setBoardTime (_boardTime);
      
      // Set the Off Date
      const boost::gregorian::date_duration lDateOffSet (_dateOffSet);
      ioLegDate.setOffDate (iRefDate + lDateOffSet);

      // Set the Off Time
      ioLegDate.setOffTime (_offTime);

      // Set the Elapsed Time
      ioLegDate.setElapsedTime (_elapsed);
    }

  }
}
