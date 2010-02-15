#ifndef __STDAIR_BOM_DOWSTRUCT_HPP
#define __STDAIR_BOM_DOWSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// STDAIR
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /** Define a Day Of the Week (DoW) sequence.
      <br>For instance, 1..11.1 means that the period is active on
      Mon., Thu., Fri. and Sun. */
  struct DoWStruct_T : public StructAbstract {
  public:
    /** Define the bit set representing the DoW. */
    typedef std::vector<bool> BooleanList_T;
      
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

  public:
    /** Constructor from a given bit set (e.g., "0000011" for the
        week-ends). */
    DoWStruct_T (const std::string& iDowString);

    /** Default constructor. */
    DoWStruct_T ();

    /** Default constructor. */
    DoWStruct_T (const DoWStruct_T&);
  };

}
#endif // __STDAIR_BOM_DOWSTRUCT_HPP
