#ifndef __STDAIR_BOM_PERIODSTRUCT_HPP
#define __STDAIR_BOM_PERIODSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// STDAIR
#include <stdair/basic/StructAbstract.hpp>
#include <stdair/bom/DoWStruct.hpp>

namespace stdair {

  /** Define a departure period
      <br> A period is defined by a date range and a day-of-week struct. */
  struct PeriodStruct_T : public StructAbstract {
  public:
    // ////////// Getters /////////////
    /** Retrieve the attributes. */
    const DatePeriod_T& getDateRange () const {
      return _dateRange;
    }
    const DoWStruct_T& getDoW () const {
      return _dow;
    }

  public:
    // /////////// Setters ////////////
    /** Set the new value for the attributes. */
    void setDateRange (const DatePeriod_T& iDateRange) {
      _dateRange = iDateRange;
    }
    void setDoW (const DoWStruct_T& iDoW) { _dow = iDoW; }

  public:
    /** Display explicitly (e.g., "Mon.Tue.Wed.Thu.Fri."). */
    const std::string describe() const;

    /** Display as a bit set (e.g., "1111100"). */
    const std::string describeShort() const;

  public:
    // /////////// Business Methods /////////////
    /** Build a period struct from this period struct by adding a date offset. */
    PeriodStruct_T addDateOffset (const DateOffset_T&) const;

    /** Build a new period struct which is the intersection of two
        period structs. */
    PeriodStruct_T intersection (const PeriodStruct_T&) const;

    /** Return if the period is  valid (i.e., valid date range and valid DoW). */
    const bool isValid () const;
    
  public:
    /** Constructor. */
    PeriodStruct_T (const DatePeriod_T&, const DoWStruct_T&);
    /** Default constructors. */
    PeriodStruct_T ();
    PeriodStruct_T (const PeriodStruct_T&);
    /** Default destructor. */
    ~PeriodStruct_T () { }

  private:
    // Attributes
    DatePeriod_T _dateRange;
    DoWStruct_T _dow;
  };

}
#endif // __STDAIR_BOM_PERIODSTRUCT_HPP
