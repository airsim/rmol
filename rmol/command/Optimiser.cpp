// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/basic/BasChronometer.hpp>
#include <stdair/bom/LegCabin.hpp>
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/StudyStatManager.hpp>
#include <rmol/bom/MCOptimiser.hpp>
#include <rmol/bom/Emsr.hpp>
#include <rmol/bom/DPOptimiser.hpp>
#include <rmol/command/Optimiser.hpp>

namespace RMOL {

  // ////////////////////////////////////////////////////////////////////
  void Optimiser::
  optimalOptimisationByMCIntegration (const int K,
                                      stdair::LegCabin& ioLegCabin) {
    // Call the class performing the actual algorithm
    MCOptimiser::optimalOptimisationByMCIntegration (K, ioLegCabin);
  }

  // ////////////////////////////////////////////////////////////////////
  void Optimiser::
  optimalOptimisationByMCIntegration (const int K, 
                                      stdair::LegCabin& ioLegCabin,
                                      StudyStatManager& ioStudyStatManager) {
    stdair::BasChronometer lMCIntegrationBasChrono;
    lMCIntegrationBasChrono.start();
    // Call the class performing the actual algorithm
    MCOptimiser::optimalOptimisationByMCIntegration (K, ioLegCabin,
                                                     ioStudyStatManager);
    const double lMCIntegrationTime = lMCIntegrationBasChrono.elapsed();
    ioStudyStatManager.addMeasure ("MCIntegrationRunningTime",
                                   lMCIntegrationTime);
  }

  // ////////////////////////////////////////////////////////////////////
  void Optimiser::optimalOptimisationByDP (stdair::LegCabin& ioLegCabin) {
    DPOptimiser::optimalOptimisationByDP (ioLegCabin);
  }

  // ////////////////////////////////////////////////////////////////////
  void Optimiser::heuristicOptimisationByEmsr (stdair::LegCabin& ioLegCabin) {
    Emsr::heuristicOptimisationByEmsr (ioLegCabin);
  }

  // ////////////////////////////////////////////////////////////////////
  void Optimiser::
  heuristicOptimisationByEmsr (stdair::LegCabin& ioLegCabin,
                               StudyStatManager& ioStudyStatManager) {
    stdair::BasChronometer lEMRSBasChrono;
    lEMRSBasChrono.start();
    Emsr::heuristicOptimisationByEmsr (ioLegCabin);
    const double lEMRSTime = lEMRSBasChrono.elapsed();
    ioStudyStatManager.addMeasure ("EMSRRunningTime", lEMRSTime);
  }

  // ////////////////////////////////////////////////////////////////////
  void Optimiser::heuristicOptimisationByEmsrA (stdair::LegCabin& ioLegCabin) {
    Emsr::heuristicOptimisationByEmsrA (ioLegCabin);
  }
  
  // ////////////////////////////////////////////////////////////////////
  void Optimiser::heuristicOptimisationByEmsrB (stdair::LegCabin& ioLegCabin) {
    Emsr::heuristicOptimisationByEmsrB (ioLegCabin);
  }
  
}
