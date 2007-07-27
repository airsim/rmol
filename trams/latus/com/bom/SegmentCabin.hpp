#ifndef __LATUS_COM_BOM_SEGMENTCABIN_HPP
#define __LATUS_COM_BOM_SEGMENTCABIN_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/SegmentCabinKey.hpp>
#include <latus/com/bom/LegCabinList.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class SegmentDate;
    
    /** Class wrapping the Segment-Cabin specific attributes and methods. */
    class SegmentCabin : public BomAbstract {
      friend class FacSegmentCabin;
    public:
      // /////////// Getters //////////////
      /** Get the parent class. */
      SegmentDate* getParent() const {
        return getSegmentDate();
      }

      /** Get the SegmentDate (parent class). */
      SegmentDate* getSegmentDate() const {
        return _segmentDate;
      }

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
      /** Set the SegmentDate (parent class). */
      void setSegmentDate (SegmentDate* ioSegmentDatePtr) {
        _segmentDate = ioSegmentDatePtr;
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

      /** Display the full SegmentCabin context. */
      void display() const;

      
    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      SegmentCabin (const SegmentCabinKey_T&); 

      /** Destructor. */
      virtual ~SegmentCabin();

    private:
      /** Get the list of (children) LegCabin objects. */
      const LegCabinList_T& getLegCabinList () const {
        return _legCabinList;
      }

      /** Retrieve, if existing, the LegCabin corresponding to the
          given board point.
          <br>If not existing, return the NULL pointer. */
      LegCabin* getLegCabin (const std::string& iLegCabinKey) const;
      

    private:
      // Parent
      /** Parent class: SegmentDate. */
      SegmentDate* _segmentDate;
      
      // Primary Key
      /** Segment-Cabin Key is composed of the cabin code. */
      SegmentCabinKey_T _key;

      /** List of routing LegCabin objects. */
      LegCabinList_T _legCabinList;

      // Attributes
      /** Capacity of the cabin. */
      CabinCapacity_T _capacity;
    };

  }
}
#endif // __LATUS_COM_BOM_SEGMENTCABIN_HPP
