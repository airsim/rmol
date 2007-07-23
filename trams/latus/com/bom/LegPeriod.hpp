#ifndef __LATUS_COM_BOM_LEGPERIOD_HPP
#define __LATUS_COM_BOM_LEGPERIOD_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/LegPeriodKey.hpp>
#include <latus/com/bom/BomAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Class wrapping the Leg-Period specific attributes and methods. */
    class LegPeriod : public BomAbstract {
    public:
      // /////////// Getters //////////////
      /** Get the primary key. */
      const LegPeriodKey_T& getPrimaryKey() const {
        return getLegPeriodKey();
      }

      /** Get the leg-period key. */
      const LegPeriodKey_T& getLegPeriodKey() const {
        return _key;
      }


      // ///////// Setters //////////

      
      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Display the full BookingDay context. */
      void display() const;

      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      LegPeriod (const LegPeriodKey_T&); 

      /** Destructor. */
      virtual ~LegPeriod();


    private:
      // Primary Key
      /** Leg-Period Key is composed of the airline code, flight number, 
          departure period, board point and off point. */
      LegPeriodKey_T _key;

      // Attributes
    };

  }
}
#endif // __LATUS_COM_BOM_LEGPERIOD_HPP
