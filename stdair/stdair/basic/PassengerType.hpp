#ifndef __STDAIR_BAS_PASSENGERTYPE_HPP
#define __STDAIR_BAS_PASSENGERTYPE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/bom/StructAbstract.hpp>

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

    /** Get the label as a string. */
    static const std::string& getLabel (const EN_PassengerType&);

    /** Get the label as a single char. */
    static char getTypeLabel (const EN_PassengerType&);

    /** List the labels. */
    static std::string describeLabels();

    /** Get the enumerated value. */
    EN_PassengerType getType() const;

    /** Give a description of the structure (for display purposes). */
    const std::string describe() const;

    
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
