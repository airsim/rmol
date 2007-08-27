#ifndef __LATUS_TSP_BOM_DOWSTRUCT_HPP
#define __LATUS_TSP_BOM_DOWSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// LATUS Common
#include <latus/com/bom/StructAbstract.hpp>

namespace LATUS {

  namespace TSP {

    /** Define a Day Of the Week (DOW) sequence.
        <br>For instance, 1..11.1 means that the period is active on
        Mon., Thu., Fri. and Sun. */
    struct DOWStruct_T : public COM::StructAbstract {
      /** Define the bit set representing the DOW. */
      typedef std::vector<bool> BooleanList_T;
      
      /** Constructor from a given bit set (e.g., "0000011" for the
          week-ends). */
      DOWStruct_T (const std::string& iDowString);
      
      /** Attributes. */
      BooleanList_T _dowList;

      /** Get the i-th day of the week (Monday being the first one). */
      bool getDayOfWeek (const unsigned short i) const;
      
      /** Get the i-th day of the week (Sunday being the first one). */
      bool getStandardDayOfWeek (const unsigned short i) const;
      
      /** Display explicitly (e.g., "Mon.Tue.Wed.Thu.Fri."). */
      const std::string describe() const;

      /** Display as a bit set (e.g., "1111100"). */
      const std::string describeShort() const;
    };

  }
}
#endif // __LATUS_TSP_BOM_DOWSTRUCT_HPP
