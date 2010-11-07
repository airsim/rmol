/*!
 * \page tut_completeex_cpp Tutorial Full Basic Example
 * \code
 */
// STL
#include <cassert>
// StdAir
#include <stdair/bom/BomRoot.hpp>
#include <stdair/bom/Inventory.hpp>
#include <stdair/bom/InventoryTypes.hpp>
#include <stdair/bom/FlightDate.hpp>
#include <stdair/bom/FlightDateTypes.hpp>
#include <stdair/bom/LegDate.hpp>
#include <stdair/bom/LegDateTypes.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/bom/LegCabinTypes.hpp>
#include <stdair/bom/SegmentDate.hpp>
#include <stdair/bom/SegmentDateTypes.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/SegmentCabinTypes.hpp>
#include <stdair/bom/FareFamily.hpp>
#include <stdair/bom/FareFamilyTypes.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/bom/BookingClassTypes.hpp>
#include <stdair/bom/BomManager.hpp> // Utility class to display BOM objects
#include <stdair/factory/FacBomManager.hpp>

// /////////////////////// M A I N ///////////////////////////
int main() {

  // ///////////// Step 0.0: Initialisation ////////////
  // Create the root of the Bom tree (i.e., a BomRoot object)
  stdair::BomRoot& lBomRoot =
    stdair::FacBom<stdair::BomRoot>::instance().create();

  // Step 0.1: Inventory level
  // Create an Inventory for BA
  const stdair::InventoryKey lBAKey ("BA");
  stdair::Inventory& lBAInv =
    stdair::FacBom<stdair::Inventory>::instance().create (lBAKey);
  stdair::FacBomManager::instance().addToList (lBomRoot, lBAInv);

  // Create an Inventory for AF
  const stdair::InventoryKey lAFKey ("AF");
  stdair::Inventory& lAFInv =
    stdair::FacBom<stdair::Inventory>::instance().create (lAFKey);
  stdair::FacBomManager::instance().addToList (lBomRoot, lAFInv);

  // ////// BA ///////    
  // Step 0.2: Flight-date level
  // Create a FlightDate (BA15/10-JUN-2010) for BA's Inventory
  stdair::FlightNumber_T lFlightNumber = 15;
  stdair::Date_T lDate (2010, 6, 10);
  stdair::FlightDateKey lFlightDateKey (lFlightNumber, lDate);

  stdair::FlightDate& lBA15_20100610_FD =
    stdair::FacBom<stdair::FlightDate>::instance().create (lFlightDateKey);
  stdair::FacBomManager::instance().addToList (lBAInv, lBA15_20100610_FD);
    
  // Step 0.3: Segment-date level
  // Create a first SegmentDate (LHR-SYD) for BA's Inventory
  const stdair::AirportCode_T lLHR ("LHR");
  const stdair::AirportCode_T lSYD ("SYD");
  stdair::SegmentDateKey lSegmentDateKey (lLHR, lSYD);

  stdair::SegmentDate& lLHRSYDSegment =
    stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
  stdair::FacBomManager::instance().addToList (lBA15_20100610_FD,
                                               lLHRSYDSegment);
    
  // Create a second SegmentDate (LHR-BKK) for BA's Inventory
  const stdair::AirportCode_T lBKK ("BKK");
  lSegmentDateKey = stdair::SegmentDateKey (lLHR, lBKK);

  stdair::SegmentDate& lLHRBKKSegment =
    stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
  stdair::FacBomManager::instance().addToList (lBA15_20100610_FD,
                                               lLHRBKKSegment);

  // Create a third SegmentDate (BKK-SYD) for BA's Inventory
  lSegmentDateKey = stdair::SegmentDateKey (lBKK, lSYD);

  stdair::SegmentDate& lBKKSYDSegment =
    stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
  stdair::FacBomManager::instance().addToList (lBA15_20100610_FD,
                                               lBKKSYDSegment);

  // Step 0.4: Leg-date level
  // Create a first LegDate (LHR) for BA's Inventory
  stdair::LegDateKey lLegDateKey (lLHR);

  stdair::LegDate& lLHRLeg =
    stdair::FacBom<stdair::LegDate>::instance().create (lLegDateKey);
  stdair::FacBomManager::instance().addToList (lBA15_20100610_FD, lLHRLeg);
    
  // Create a second LegDate (BKK)
  lLegDateKey = stdair::LegDateKey (lBKK);

  stdair::LegDate& lBKKLeg =
    stdair::FacBom<stdair::LegDate>::instance().create (lLegDateKey);
  stdair::FacBomManager::instance().addToList (lBA15_20100610_FD, lBKKLeg);

  // Step 0.5: segment-cabin level
  // Create a SegmentCabin (Y) for the Segment LHR-BKK of BA's Inventory
  const stdair::CabinCode_T lY ("Y");
  stdair::SegmentCabinKey lYSegmentCabinKey (lY);

  stdair::SegmentCabin& lLHRBKKSegmentYCabin =
    stdair::FacBom<stdair::SegmentCabin>::instance().create(lYSegmentCabinKey);
  stdair::FacBomManager::instance().addToList (lLHRBKKSegment,
                                               lLHRBKKSegmentYCabin);

  // Create a SegmentCabin (Y) of the Segment BKK-SYD;
  stdair::SegmentCabin& lBKKSYDSegmentYCabin =
    stdair::FacBom<stdair::SegmentCabin>::instance().create(lYSegmentCabinKey);
  stdair::FacBomManager::instance().addToList (lBKKSYDSegment,
                                               lBKKSYDSegmentYCabin);

  // Create a SegmentCabin (Y) of the Segment LHR-SYD;
  stdair::SegmentCabin& lLHRSYDSegmentYCabin =
    stdair::FacBom<stdair::SegmentCabin>::instance().create(lYSegmentCabinKey);
  stdair::FacBomManager::instance().addToList (lLHRSYDSegment,
                                               lLHRSYDSegmentYCabin);

  // Step 0.6: leg-cabin level
  // Create a LegCabin (Y) for the Leg LHR-BKK on BA's Inventory
  stdair::LegCabinKey lYLegCabinKey (lY);

  stdair::LegCabin& lLHRLegYCabin =
    stdair::FacBom<stdair::LegCabin>::instance().create (lYLegCabinKey);
  stdair::FacBomManager::instance().addToList (lLHRLeg, lLHRLegYCabin);

  // Create a LegCabin (Y) for the Leg BKK-SYD
  stdair::LegCabin& lBKKLegYCabin =
    stdair::FacBom<stdair::LegCabin>::instance().create (lYLegCabinKey);
  stdair::FacBomManager::instance().addToList (lBKKLeg, lBKKLegYCabin);

  // Step 0.7: fare family level
  // Create a FareFamily (1) for the Segment LHR-BKK, cabin Y on BA's Inv
  const stdair::FamilyCode_T l1 ("1");
  stdair::FareFamilyKey l1FareFamilyKey (l1);

  stdair::FareFamily& lLHRBKKSegmentYCabin1Family =
    stdair::FacBom<stdair::FareFamily>::instance().create(l1FareFamilyKey);
  stdair::FacBomManager::instance().addToList (lLHRBKKSegmentYCabin,
                                               lLHRBKKSegmentYCabin1Family);

  // Create a FareFamily (1)  for the Segment BKK-SYD, cabin Y on BA's Inv
  stdair::FareFamily& lBKKSYDSegmentYCabin1Family =
    stdair::FacBom<stdair::FareFamily>::instance().create(l1FareFamilyKey);
  stdair::FacBomManager::instance().addToList (lBKKSYDSegmentYCabin,
                                               lBKKSYDSegmentYCabin1Family);

  // Create a FareFamily (1)  for the Segment LHR-SYD, cabin Y on BA's Inv
  stdair::FareFamily& lLHRSYDSegmentYCabin1Family =
    stdair::FacBom<stdair::FareFamily>::instance().create(l1FareFamilyKey);
  stdair::FacBomManager::instance().addToList (lLHRSYDSegmentYCabin,
                                               lLHRSYDSegmentYCabin1Family);

  // Step 0.8: booking class level
  // Create a BookingClass (Q) for the Segment LHR-BKK, cabin Y, fare
  // family 1 on BA's Inv
  const stdair::ClassCode_T lQ ("Q");
  stdair::BookingClassKey lQBookingClassKey (lQ);

  stdair::BookingClass& lLHRBKKSegmentYCabin1FamilyQClass =
    stdair::FacBom<stdair::BookingClass>::instance().create(lQBookingClassKey);
  stdair::FacBomManager::instance().addToList (lLHRBKKSegmentYCabin1Family,
                                               lLHRBKKSegmentYCabin1FamilyQClass);

  // Create a BookingClass (Q) for the Segment BKK-SYD, cabin Y, fare
  // family 1 on BA's Inv
  stdair::BookingClass& lBKKSYDSegmentYCabin1FamilyQClass =
    stdair::FacBom<stdair::BookingClass>::instance().create(lQBookingClassKey);
  stdair::FacBomManager::instance().addToList (lBKKSYDSegmentYCabin1Family,
                                               lBKKSYDSegmentYCabin1FamilyQClass);
    
  // Create a BookingClass (Q) for the Segment LHR-SYD, cabin Y, fare
  // family 1 on BA's Inv
  stdair::BookingClass& lLHRSYDSegmentYCabin1FamilyQClass =
    stdair::FacBom<stdair::BookingClass>::instance().create(lQBookingClassKey);
  stdair::FacBomManager::instance().addToList (lLHRSYDSegmentYCabin1Family,
                                               lLHRSYDSegmentYCabin1FamilyQClass);
    
  // ////// AF ///////    
  // Step 0.2: Flight-date level
  // Create a FlightDate (AF102/20-MAR-2010) for AF's Inventory
  lFlightNumber = 102;
  lDate = stdair::Date_T (2010, 3, 20);
  lFlightDateKey = stdair::FlightDateKey (lFlightNumber, lDate);

  stdair::FlightDate& lAF102_20100320_FD =
    stdair::FacBom<stdair::FlightDate>::instance().create (lFlightDateKey);
  stdair::FacBomManager::instance().addToList (lAFInv, lAF102_20100320_FD);

  // Step 0.3: Segment-date level
  // Create a SegmentDate (CDG-SFO) for AF's Inventory
  const stdair::AirportCode_T lCDG ("CDG");
  const stdair::AirportCode_T lSFO ("SFO");
  lSegmentDateKey = stdair::SegmentDateKey (lCDG, lSFO);

  stdair::SegmentDate& lCDGSFOSegment =
    stdair::FacBom<stdair::SegmentDate>::instance().create (lSegmentDateKey);
  stdair::FacBomManager::instance().addToList (lAF102_20100320_FD,
                                               lCDGSFOSegment);

  // Step 0.4: Leg-date level
  // Create a LegDate (CDG) for AF's Inventory
  lLegDateKey = stdair::LegDateKey (lCDG);

  stdair::LegDate& lCDGLeg =
    stdair::FacBom<stdair::LegDate>::instance().create (lLegDateKey);
  stdair::FacBomManager::instance().addToList (lAF102_20100320_FD, lCDGLeg);

  // Step 0.5: segment-cabin level
  // Create a SegmentCabin (Y) for the Segment CDG-SFO of AF's Inventory
  stdair::SegmentCabin& lCDGSFOSegmentYCabin =
    stdair::FacBom<stdair::SegmentCabin>::instance().create(lYSegmentCabinKey);
  stdair::FacBomManager::instance().addToList (lCDGSFOSegment,
                                               lCDGSFOSegmentYCabin);

  // Step 0.6: leg-cabin level
  // Create a LegCabin (Y) for the Leg CDG-SFO on AF's Inventory
  stdair::LegCabin& lCDGLegYCabin =
    stdair::FacBom<stdair::LegCabin>::instance().create (lYLegCabinKey);
  stdair::FacBomManager::instance().addToList (lCDGLeg, lCDGLegYCabin);

  // Step 0.7: fare family level
  // Create a fareFamily (1) for the Segment CDG-SFO, cabin Y on AF's Inv
  stdair::FareFamily& lCDGSFOSegmentYCabin1Family =
    stdair::FacBom<stdair::FareFamily>::instance().create(l1FareFamilyKey);
  stdair::FacBomManager::instance().addToList (lCDGSFOSegmentYCabin,
                                               lCDGSFOSegmentYCabin1Family);

  // Step 0.8: booking class level
  // Create a BookingClass (Q) for the Segment CDG-SFO, cabin Y, fare
  // family 1 on AF's Inv
  stdair::BookingClass& lCDGSFOSegmentYCabin1FamilyQClass =
    stdair::FacBom<stdair::BookingClass>::instance().create(lQBookingClassKey);
  stdair::FacBomManager::instance().addToList (lCDGSFOSegmentYCabin1Family,
                                               lCDGSFOSegmentYCabin1FamilyQClass);


  // /////////// Step 1.0: Display the BOM tree //////////   
  // 1.0. Bom root level
  std::cout << lBomRoot << std::endl;
    
  // 1.1. Inventory level
  const stdair::InventoryList_T& lInventoryList =
    stdair::BomManager::getList<stdair::Inventory> (lBomRoot);
  for (stdair::InventoryList_T::const_iterator itInv = lInventoryList.begin();
       itInv != lInventoryList.end(); ++itInv) {
    const stdair::Inventory* lInv_ptr = *itInv;
    assert (lInv_ptr != NULL);

    std::cout << " " << *lInv_ptr << std::endl;
      
    // 1.2. FlightDate level
    const stdair::FlightDateList_T& lFlightDateList =
      stdair::BomManager::getList<stdair::FlightDate> (*lInv_ptr);
    for (stdair::FlightDateList_T::const_iterator itFD=lFlightDateList.begin();
         itFD != lFlightDateList.end(); ++itFD) {
      const stdair::FlightDate* lFD_ptr = *itFD;
      assert (lFD_ptr != NULL);

      std::cout << "   " << *lFD_ptr << std::endl;

      // 1.4. LegDate level
      const stdair::LegDateList_T& lLegDateList =
        stdair::BomManager::getList<stdair::LegDate> (*lFD_ptr);
      for (stdair::LegDateList_T::const_iterator itLD =
             lLegDateList.begin();
           itLD != lLegDateList.end(); ++itLD) {
        const stdair::LegDate* lLD_ptr = *itLD;
        assert (lLD_ptr != NULL);
         
        std::cout << "      " << *lLD_ptr << std::endl;

        // 1.6. LegCabin level
        const stdair::LegCabinList_T& lLegCabinList =
          stdair::BomManager::getList<stdair::LegCabin> (*lLD_ptr);
        for (stdair::LegCabinList_T::const_iterator itLC =
               lLegCabinList.begin();
             itLC != lLegCabinList.end(); ++itLC) {
          const stdair::LegCabin* lLC_ptr = *itLC;
          assert (lLC_ptr != NULL);
          
          std::cout << "        " << *lLC_ptr << std::endl;
        }
      }

      // 1.3. SegmentDate level
      const stdair::SegmentDateList_T& lSegmentDateList =
        stdair::BomManager::getList<stdair::SegmentDate> (*lFD_ptr);
      for (stdair::SegmentDateList_T::const_iterator itSD =
             lSegmentDateList.begin();
           itSD != lSegmentDateList.end(); ++itSD) {
        const stdair::SegmentDate* lSD_ptr = *itSD;
        assert (lSD_ptr != NULL);
          
        std::cout << "      " << *lSD_ptr << std::endl;
        
        // 1.5. SegmentCabin level
        const stdair::SegmentCabinList_T& lSegmentCabinList =
          stdair::BomManager::getList<stdair::SegmentCabin> (*lSD_ptr);
        for (stdair::SegmentCabinList_T::const_iterator itSC =
               lSegmentCabinList.begin();
             itSC != lSegmentCabinList.end(); ++itSC) {
          const stdair::SegmentCabin* lSC_ptr = *itSC;
          assert (lSC_ptr != NULL);
            
          std::cout << "        " << *lSC_ptr << std::endl;

          // 1.7. FareFamily level
          const stdair::FareFamilyList_T& lFareFamilyList =
            stdair::BomManager::getList<stdair::FareFamily> (*lSC_ptr);
          for (stdair::FareFamilyList_T::const_iterator itFF =
                 lFareFamilyList.begin();
               itFF != lFareFamilyList.end(); ++itFF) {
            const stdair::FareFamily* lFF_ptr = *itFF;
            assert (lFF_ptr != NULL);
              
            std::cout << "          " << *lFF_ptr << std::endl;
            
            // 1.8. BookingClass level
            const stdair::BookingClassList_T& lBookingClassList =
              stdair::BomManager::getList<stdair::BookingClass> (*lFF_ptr);
            for (stdair::BookingClassList_T::const_iterator itBC =
                   lBookingClassList.begin();
                 itBC != lBookingClassList.end(); ++itBC) {
              const stdair::BookingClass* lBC_ptr = *itBC;
              assert (lBC_ptr != NULL);
              
              std::cout << "            " << *lBC_ptr << std::endl;
            }
          }
        }
      }
    }
  }
  // Exit program:
  return 0;
}

/*!
 * \endcode
 */
