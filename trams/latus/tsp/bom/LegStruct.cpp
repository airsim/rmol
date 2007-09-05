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
    LegStruct_T::LegStruct_T ()
      : _boardDateOffSet (COM::DEFAULT_DATE_OFFSET),
        _offDateOffSet (COM::DEFAULT_DATE_OFFSET) {
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string LegStruct_T::describe() const {
      std::ostringstream ostr;
      ostr << "    " << _boardPoint << " / " << _boardTime;
      if (_boardDateOffSet.days() != 0) {
        ostr << " [" << _boardDateOffSet.days() << "]";
      }
      ostr << " -- " << _offPoint << " / " << _offTime;
      if (_offDateOffSet.days() != 0) {
        ostr << " [" << _offDateOffSet.days() << "]";
      }
      ostr << " --> " << _elapsed
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
      const boost::gregorian::date_duration lBoardDateOffSet (_boardDateOffSet);
      ioLegDate.setBoardDate (iRefDate+ lBoardDateOffSet);

      // Set the Board Time
      ioLegDate.setBoardTime (_boardTime);
      
      // Set the Off Date
      const boost::gregorian::date_duration lOffDateOffSet (_offDateOffSet);
      ioLegDate.setOffDate (iRefDate + lOffDateOffSet);

      // Set the Off Time
      ioLegDate.setOffTime (_offTime);

      // Set the Elapsed Time
      ioLegDate.setElapsedTime (_elapsed);
    }

  }
}
