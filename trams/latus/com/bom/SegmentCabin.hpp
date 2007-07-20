#ifndef __LATUS_COM_BOM_SEGMENTCABIN_HPP
#define __LATUS_COM_BOM_SEGMENTCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/BomAbstract.hpp>

namespace LATUS {

  namespace COM {

    /** Class wrapping the Segment-Cabin specific attributes and methods. */
    class SegmentCabin : public BomAbstract {
    public:
      // /////////// Getters //////////////
      /** Get the primary key. */
      const SegmentCabinKey_T& getPrimaryKey() const {
        return getSegmentCabinKey();
      }

      /** Get the flight-cabin key. */
      const SegmentCabinKey_T& getSegmentCabinKey() const {
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
      SegmentCabin (const SegmentCabinKey_T&); 

      /** Destructor. */
      virtual ~SegmentCabin();


    private:
      // Primary Key
      /** Segment-Cabin Key is composed of the cabin code. */
      SegmentCabinKey_T _key;

      // Attributes
      /** Capacity of the cabin. */
      CabinCapacity_T _capacity;
    };

  }
}
#endif // __LATUS_COM_BOM_SEGMENTCABIN_HPP
