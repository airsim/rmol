// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <sstream>
// LATUS Common
#include <latus/com/basic/BasConst_Period_BOM.hpp>
// LATUS TSP
#include <latus/tsp/bom/DOWStruct.hpp>

namespace LATUS {

  namespace TSP {

    // //////////////////////////////////////////////////////////////////////
    DOWStruct_T::DOWStruct_T (const std::string& iDowString) {
      const unsigned short lDowStringSize = iDowString.size();
      assert (lDowStringSize == 7);
      
      _dowList.reserve (lDowStringSize);
      for (std::string::const_iterator itChar = iDowString.begin();
           itChar != iDowString.end(); ++itChar) {
        const bool isDOWSet = (*itChar == '1')?true:false;
        _dowList.push_back (isDOWSet);
      }
    }
    
    // //////////////////////////////////////////////////////////////////////
    const std::string DOWStruct_T::describeShort() const {
      std::ostringstream ostr;
      short i = 0;
      for (BooleanList_T::const_iterator itDOW = _dowList.begin();
           itDOW != _dowList.end(); ++itDOW, ++i) {
        const char lDOW = (*itDOW == true)?'1':'0';
        ostr << lDOW;
      }
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    const std::string DOWStruct_T::describe() const {
      std::ostringstream ostr;
      short i = 0;
      for (BooleanList_T::const_iterator itDOW = _dowList.begin();
           itDOW != _dowList.end(); ++itDOW, ++i) {
        const bool lDOW = *itDOW;
        if (lDOW == true) {
          ostr << COM::DOW_STR[i] << ".";
        }
      }
      return ostr.str();
    }

    // //////////////////////////////////////////////////////////////////////
    bool DOWStruct_T::getDayOfWeek (const unsigned short i) const {
      return _dowList.at (i);
    }
      
    // //////////////////////////////////////////////////////////////////////
    bool DOWStruct_T::getStandardDayOfWeek (const unsigned short i) const {
      unsigned short iStd = i;
      if (iStd == 0) {
        iStd = 6;
      } else {
        --iStd;
      }
      return _dowList.at (iStd);
    }
    
  }
}
