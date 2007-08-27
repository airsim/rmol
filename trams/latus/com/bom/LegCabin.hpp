#ifndef __LATUS_COM_BOM_LEGCABIN_HPP
#define __LATUS_COM_BOM_LEGCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/LegCabinKey.hpp>
#include <latus/com/bom/SegmentCabinList.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class LegDate;
    
    /** Class wrapping the Leg-Cabin specific attributes and methods. */
    class LegCabin : public BomAbstract {
      friend class FacLegCabin;
    public:
      // /////////// Getters //////////////
      /** Get the parent class. */
      LegDate* getParent() const {
        return getLegDate();
      }

      /** Get the LegDate (parent class). */
      LegDate* getLegDate() const {
        return _legDate;
      }

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

      /** Get the board point (from the LegDate parent). */
      const AirportCode_T& getBoardPoint () const;

      /** Get the off point (from the LegDate parent). */
      const AirportCode_T& getOffPoint () const;


      // ///////// Setters //////////
      /** Set the LegDate (parent class). */
      void setLegDate (LegDate* ioLegDatePtr) {
        _legDate = ioLegDatePtr;
      }

      /** Set the off cabin. */
      void setCapacity (const CabinCapacity_T& iCapacity) {
        _capacity = iCapacity;
      }


      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Get a string describing the short key. */
      const std::string describeShortKey() const;

      /** Display the full BookingDay context. */
      void display() const;

      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      LegCabin (const LegCabinKey_T&); 

      /** Destructor. */
      virtual ~LegCabin();

    private:
      /** Get the list of (children) SegmentCabin objects. */
      const SegmentCabinList_T& getSegmentCabinList () const {
        return _segmentCabinList;
      }

      /** Retrieve, if existing, the SegmentCabin corresponding to the
          given board point.
          <br>If not existing, return the NULL pointer. */
      SegmentCabin* getSegmentCabin(const std::string& iSegmentCabinKey) const;
      

    private:
      // Parent
      /** Parent class: LegDate. */
      LegDate* _legDate;
      
      // Primary Key
      /** Leg-Cabin Key is composed of the cabin code. */
      LegCabinKey_T _key;

      /** List of crossing SegmentCabin objects. */
      SegmentCabinList_T _segmentCabinList;

      // Attributes
      /** Capacity of the cabin. */
      CabinCapacity_T _capacity;
    };

  }
}
#endif // __LATUS_COM_BOM_LEGCABIN_HPP
