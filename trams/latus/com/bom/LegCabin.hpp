#ifndef __LATUS_COM_BOM_LEGCABIN_HPP
#define __LATUS_COM_BOM_LEGCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/LegCabinKey.hpp>

namespace LATUS {

  namespace COM {

    /** Class wrapping the Leg-Cabin specific attributes and methods. */
    class LegCabin : public BomAbstract {
    public:
      // /////////// Getters //////////////
      /** Get the primary key. */
      const LegCabinKey_T& getPrimaryKey() const {
        return getLegCabinKey();
      }

      /** Get the flight-cabin key. */
      const LegCabinKey_T& getLegCabinKey() const {
        return _key;
      }

      /** Get the off cabin. */
      const CabinCapacity_T& getCapacity () const {
        return _capacity;
      }


      // ///////// Setters //////////
      /** Set the off cabin. */
      void setCapacity (const CabinCapacity_T& iCapacity) {
        _capacity = iCapacity;
      }


      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Display the full BookingDay context. */
      void display() const;

      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      LegCabin (const LegCabinKey_T&); 

      /** Destructor. */
      virtual ~LegCabin();


    private:
      // Primary Key
      /** Leg-Cabin Key is composed of the cabin code. */
      LegCabinKey_T _key;

      // Attributes
      /** Capacity of the cabin. */
      CabinCapacity_T _capacity;
    };

  }
}
#endif // __LATUS_COM_BOM_LEGCABIN_HPP
