// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
#include <cmath>
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/bom/BomManager.hpp>
#include <stdair/bom/SegmentCabin.hpp>
#include <stdair/bom/BookingClass.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/basic/BasConst_Curves.hpp>
#include <rmol/bom/Utilities.hpp>
#include <rmol/command/DemandInputPreparation.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  bool DemandInputPreparation::
  prepareDemandInput (const stdair::SegmentCabin& iSegmentCabin) {
    bool isSucceeded = true;

    // Browse the list of booking classes and sum the price-oriented
    // demand foreast and the product-oriented demand forecast.
    const stdair::BookingClassList_T& lBCList =
      stdair::BomManager::getList<stdair::BookingClass> (iSegmentCabin);
    for (stdair::BookingClassList_T::const_iterator itBC = lBCList.begin();
         itBC != lBCList.end(); ++itBC) {
      stdair::BookingClass* lBC_ptr = *itBC;
      assert (lBC_ptr != NULL);

      const double& lPriceDemMean = lBC_ptr->getPriceDemMean();
      const double& lPriceStdDev = lBC_ptr->getPriceDemStdDev();
      const double& lProductDemMean = lBC_ptr->getProductDemMean();
      const double& lProductStdDev = lBC_ptr->getProductDemStdDev();

      lBC_ptr->setMean (lPriceDemMean + lProductDemMean);
      lBC_ptr->setStdDev (sqrt(lPriceStdDev*lPriceStdDev
                                  + lProductStdDev*lProductStdDev));
    }

    return isSucceeded;
  }
  
}
