#ifndef __LATUS_COM_BOM_WORLDSCHEDULE_HPP
#define __LATUS_COM_BOM_WORLDSCHEDULE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
// LATUS Common
#include <latus/com/bom/BomAbstract.hpp>
#include <latus/com/bom/InventoryList.hpp>

namespace LATUS {

  namespace COM {

    /** Class wrapping the inventories of all the available airlines. */
    class WorldSchedule : public BomAbstract {
      friend class FacWorldSchedule;
    public:
      // /////////// Getters //////////////
      /** Get the primary key. */
      const boost::gregorian::date& getPrimaryKey() const {
        return getUpdateDate();
      }

      /** Get the update/creation date for the world schedule data. */
      const boost::gregorian::date& getUpdateDate() const {
        return _updateDate;
      }


      // ///////// Setters //////////
      /** Set the update/creation date for the world schdule data. */
      void setUpdateDate (const boost::gregorian::date& iUpdateDate) {
        _updateDate = iUpdateDate;
      }


      // ///////// Display Methods //////////
      /** Get a string describing the key. */
      const std::string describeKey() const;

      /** Display the full BookingDay context. */
      void display() const;

    private:
      /** Constructors are private so as to force the usage of the Factory
          layer. */
      WorldSchedule (const boost::gregorian::date& iUpdateDate); 

      /** Destructor. */
      virtual ~WorldSchedule();

      /** Get the list of (children) WorldSchedule objects. */
      const InventoryList_T& getInventoryList () const {
        return _inventoryList;
      }

      /** Retrieve, if existing, the WorldSchedule corresponding to the
          given departure date.
          <br>If not existing, return the NULL pointer. */
      Inventory* getInventory (const std::string& iDescription) const;
      

    private:
      // Attributes
      /** Children: list of Inventory objects. */
      InventoryList_T _inventoryList;

      /** Update/creation date for the World Schedule data. */
      boost::gregorian::date _updateDate;

    };

  }

}

#endif // __LATUS_COM_BOM_WORLDSCHEDULE_HPP
