#ifndef __STDAIR_BAS_PASSENGERTYPE_HPP
#define __STDAIR_BAS_PASSENGERTYPE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/StructAbstract.hpp>

namespace stdair {

  /** Enumeration of Frequent Flyer types. */
  struct PassengerType : public StructAbstract {
  public:
    typedef enum { 
      LEISURE = 0,
      BUSINESS,
      FIRST,
      LAST_VALUE
    } EN_PassengerType;

    /** Get the label as a string (e.g., "Leisure" or "Business"). */
    static const std::string& getLabel (const EN_PassengerType&);

    /** Get the label as a single char (e.g., 'L' or 'B'). */
    static char getTypeLabel (const EN_PassengerType&);

    /** Get the label as a single char (e.g., 'L' or 'B'). */
    static std::string getTypeLabelAsString (const EN_PassengerType&);

    /** List the labels. */
    static std::string describeLabels();

    /** Get the enumerated value. */
    EN_PassengerType getType() const;

    /** Get the enumerated value as a short string (e.g., 'L' or 'B'). */
    std::string getTypeAsString() const;
    
    /** Give a description of the structure (e.g., "Leisure" or "Business"). */
    const std::string describe() const;

  public:
    /** Comparison operator. */
    bool operator== (const EN_PassengerType&) const;
    
  public:
    /** Constructor. */
    PassengerType (const EN_PassengerType&);
    /** Constructor. */
    PassengerType (const char iType);

    
  private:
    /** String version of the enumeration. */    
    static const std::string _labels[LAST_VALUE];
    /** Type version of the enumeration. */    
    static const char _typeLabels[LAST_VALUE];


  private:
    // //////// Attributes /////////
    /** Frequent flyer type. */
    EN_PassengerType _type;
  };

}
#endif // __STDAIR_BAS_PASSENGERTYPE_HPP
