// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/SegmentDate.hpp>
// LATUS TSP
#include <latus/tsp/bom/SegmentStruct.hpp>

namespace LATUS {

  namespace TSP {

    // //////////////////////////////////////////////////////////////////////
    const std::string SegmentStruct_T::describe() const {
      std::ostringstream ostr;
      ostr << "    " << _boardPoint << " / " << _boardTime
           << " -- " << _offPoint << " / " << _offTime
           << " --> " << _elapsed
           << std::endl;
      for (SegmentCabinStructList_T::const_iterator itCabin =
             _cabinList.begin(); itCabin != _cabinList.end(); itCabin++) {
        const SegmentCabinStruct_T& lCabin = *itCabin;
        ostr << lCabin.describe();
      }
      ostr << std::endl;
    
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    void SegmentStruct_T::fill (COM::SegmentDate& ioSegmentDate) const {
      // Note that some parameters (board date, board time, off date, off time,
      // elapsed time) are set by SegmentDate::fillFromRouting() when
      // the routing (with legs) is built. So, it is useless to set those
      // parameters here.

      // At that time, there are no other parameters.
    }

  }
}
