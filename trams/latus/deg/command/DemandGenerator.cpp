// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// LATUS Common
#include <latus/com/bom/WholeDemand.hpp>
#include <latus/com/bom/CityPair.hpp>
#include <latus/com/bom/CityPairDate.hpp>
#include <latus/com/bom/WTP.hpp>
#include <latus/com/factory/FacWholeDemand.hpp>
#include <latus/com/factory/FacCityPair.hpp>
#include <latus/com/factory/FacCityPairDate.hpp>
#include <latus/com/factory/FacWTP.hpp>
#include <latus/com/service/Logger.hpp>
// LATUS DEG
#include <latus/deg/bom/DemandStruct.hpp>
#include <latus/deg/command/DemandGenerator.hpp>

namespace LATUS {

  namespace DEG {

    // //////////////////////////////////////////////////////////////////////
    void DemandGenerator::createDemands (COM::WholeDemand& ioWholeDemand,
                                         const DemandStruct_T& iDemandStruct) {

      // If the CityPair object corresponding to the (origin, destination)
      // of the demand does not exist, create it and link it to the
      // WholeDemand object.
      COM::CityPair* lCityPair_ptr =
        ioWholeDemand.getCityPair (iDemandStruct._origin,
                                   iDemandStruct._destination);

      if (lCityPair_ptr == NULL) {
        const COM::AirportPairKey_T lAirportPairKey(iDemandStruct._origin,
                                                    iDemandStruct._destination);
        const COM::CityPairKey_T lCityPairKey (lAirportPairKey);
        lCityPair_ptr = &COM::FacCityPair::instance().create (lCityPairKey);
      
        COM::FacWholeDemand::initLinkWithCityPair (ioWholeDemand,
                                                   *lCityPair_ptr);
      }
      assert (lCityPair_ptr != NULL);
      
      // If the CityPairDate object corresponding to the departure date
      // of the demand does not exist, create it and link it to
      // the CityPair (parent).
      COM::CityPairDate* lCityPairDate_ptr =
        lCityPair_ptr->getCityPairDate (iDemandStruct._departureDate);

      if (lCityPairDate_ptr == NULL) {
        lCityPairDate_ptr = &COM::FacCityPairDate::instance().
          create (iDemandStruct._departureDate);

        COM::FacCityPair::initLinkWithCityPairDate (*lCityPair_ptr,
                                                    *lCityPairDate_ptr);
      }
      assert (lCityPairDate_ptr != NULL);

      // Create the WTP object corresponding to the demand wtp, and link it
      // to the CityPairDate (parent).
      COM::WTP& lWTP = COM::FacWTP::instance().
        create (iDemandStruct._wtp, iDemandStruct._currency,
                COM::DistributionDetails_T (iDemandStruct._demandMean,
                                            iDemandStruct._demandStdDev));
      COM::FacCityPairDate::initLinkWithWTP (*lCityPairDate_ptr, lWTP);
    }

  }
}
