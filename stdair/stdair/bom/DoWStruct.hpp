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
  struct DoWStruct : public StructAbstract {
  public:
    /** Define the bit set representing the DoW. */
    typedef std::vector<bool> BooleanList_T;

  public:
    // //////////////// Getters ///////////////
    /** Get the i-th day of the week (Monday being the first one). */
    bool getDayOfWeek (const unsigned short i) const;
      
    /** Get the i-th day of the week (Sunday being the first one). */
    bool getStandardDayOfWeek (const unsigned short i) const;

  public:
    // //////////////// Setters ///////////////
    /** Set the new value for the i-th day-of-week. */
    void setDayOfWeek (const unsigned short, const bool);
    
  public:
    // //////////////// Display methods ///////////////
    /** Display explicitly (e.g., "Mon.Tue.Wed.Thu.Fri."). */
    const std::string describe() const;

    /** Display as a bit set (e.g., "1111100"). */
    const std::string describeShort() const;

  public:
    // ///////////////// Business Methods ////////////////
    /** Build a new DoW struct by shifting the current DoW by a given number. */
    DoWStruct shift (const long&) const;

    /** Build a new DoW struct by intersecting two DoW structs. */
    DoWStruct intersection (const DoWStruct&) const;

    /** Return if the DoW struct is valid (i.e., has at least one "true"). */
    const bool isValid () const;
    
  public:
    /** Constructor from a given bit set (e.g., "0000011" for the
        week-ends). */
    DoWStruct (const std::string& iDowString);
    /** Default constructors. */
    DoWStruct ();
    DoWStruct (const DoWStruct&);
    /** Default destructor. */
    ~DoWStruct () { }
    
  private:
    /** Attributes. */
    BooleanList_T _dowList;
  };

}
#endif // __STDAIR_BOM_DOWSTRUCT_HPP
