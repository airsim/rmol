#ifndef __LATUS_COM_BOM_CLASSSTRUCT_HPP
#define __LATUS_COM_BOM_CLASSSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
// LATUS Common
#include <latus/com/basic/BasComTypes.hpp>
#include <latus/com/bom/StructAbstract.hpp>
#include <latus/com/bom/ClassKey.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class SegmentCabin;

    /** Utility Structure for the parsing of Class details. */
    struct ClassStruct_T : public StructAbstract {
      /** Constructor. */
      ClassStruct_T (const ClassKey_T&);
      
      // /////////// Getters //////////////
      /** Get the parent class. */
      SegmentCabin* getParent() const {
        return getSegmentCabin();
      }

      /** Get the SegmentCabin (parent class). */
      SegmentCabin* getSegmentCabin() const {
        return _segmentCabin;
      }

      /** Get the primary key. */
      const ClassKey_T& getPrimaryKey() const {
        return getClassKey();
      }

      /** Get the segment-class key. */
      const ClassKey_T& getClassKey() const {
        return _key;
      }

      // ///////// Setters //////////
      /** Set the SegmentCabin (parent class). */
      void setSegmentCabin (SegmentCabin* ioSegmentCabinPtr) {
        _segmentCabin = ioSegmentCabinPtr;
      }

      // ///////// Display Methods //////////
      /** Give a description of the structure (for display purposes). */
      const std::string describe() const;

      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Get a string describing the short key. */
      const std::string describeShortKey() const;

      /** Display the full SegmentCabin context. */
      void display() const;


      // /////////////// Attributes //////////
      // Parent
      /** Parent class: SegmentCabin. */
      SegmentCabin* _segmentCabin;
      
      // Primary Key
      /** Class Key is composed of the class code. */
      ClassKey_T _key;
      
      // Attributes
      BookingNumber_T _bookingNumber;
      Availability_T _availability;
      
    };

    /** Lists of Class-Detail strucutres. */
    typedef std::vector<ClassStruct_T> ClassStructOrderedList_T;
    typedef std::map<std::string, ClassStruct_T*> ClassStructList_T;
  }
}
#endif // __LATUS_COM_BOM_CLASSSTRUCT_HPP
