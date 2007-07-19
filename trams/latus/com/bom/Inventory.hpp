#ifndef __LATUS_COM_BOM_INVENTORY_HPP
#define __LATUS_COM_BOM_INVENTORY_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>


namespace LATUS {

  namespace COM {

    // Forward declarations
    class WorldSchedule;
    
    /** Class wrapping the Inventory for a specific airline/provider. */
    class Inventory : public BomAbstract {
      friend class FacWorldSchedule;
    public:
      // /////////// Getters //////////////
      /** Get the parent class. */
      WorldSchedule* getParent() const {
        return getWorldSchedule();
      }

      /** Get the WorldSchedule (parent class). */
      WorldSchedule* getWorldSchedule() const {
        return _worldSchedule;
      }

      /** Get the primary key. */
      const std::string& getPrimaryKey() const {
        return getDescription();
      }

      /** Get the description, e.g., "BA". */
      const std::string& getDescription() const {
        return _description;
      }


      // ///////// Setters //////////
      /** Set the WorldSchedule (parent class). */
      void setWorldSchedule (WorldSchedule* ioWorldSchedulePtr) {
        _worldSchedule = ioWorldSchedulePtr;
      }


      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Display the full BookingDay context. */
      void display() const;


    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      Inventory (const std::string& iDescription); 

      /** Destructor. */
      virtual ~Inventory();

    private:
      // Parent
      /** Parent class: WorldSchedule. */
      WorldSchedule* _worldSchedule;
      
      // Attributes
      /** Inventory Description, e.g., "BA". */
      const std::string _description;
    };

  }
}
#endif // __LATUS_COM_BOM_INVENTORY_HPP
