// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
// StdAir
#include <stdair/stdair_exceptions.hpp>
// RMOL
#include <rmol/OptimizationType.hpp>

namespace RMOL {
  
  // //////////////////////////////////////////////////////////////////////
    /**
     * Get the label as a string (e.g., "OptimalByMC", "OptimalByDP",
     * "HeuristicByEMSR", "HeuristicByEMSRa", "HeuristicByEMSRb",
     * "HeuristicByMCForQFF",
     * "HeuristicByEMSRbForQFF" or "HeuristicByMRTForQFF").
     */
  const std::string OptimizationType::_labels[LAST_VALUE] =
    { "OptimalByMC", "OptimalByDP",
      "HeuristicByEMSR", "HeuristicByEMSRa", "HeuristicByEMSRb",
      "HeuristicByMCForQFF", "HeuristicByEMSRbForQFF", "HeuristicByMRTForQFF" };

  // //////////////////////////////////////////////////////////////////////
  const char OptimizationType::
  _typeLabels[LAST_VALUE] = { 'M', 'D', 'E', 'A', 'B', 'Q', 'C', 'R' };

  // //////////////////////////////////////////////////////////////////////
  OptimizationType::OptimizationType()
    : _type (LAST_VALUE) {
    assert (false);
  }

  // //////////////////////////////////////////////////////////////////////
  OptimizationType::OptimizationType (const OptimizationType& iOptimizationType)
    : _type (iOptimizationType._type) {
  }

  // //////////////////////////////////////////////////////////////////////
  OptimizationType::
  OptimizationType (const EN_OptimizationType& iOptimizationType)
    : _type (iOptimizationType) {
  }

  // //////////////////////////////////////////////////////////////////////
  OptimizationType::OptimizationType (const char iType) {
    switch (iType) {
    case 'M': _type = OPT_MC; break;
    case 'D': _type = OPT_DP; break;
    case 'E': _type = HEUR_EMSR; break;
    case 'A': _type = HEUR_EMSRA; break;
    case 'B': _type = HEUR_EMSRB; break;
    case 'Q': _type = HEUR_MC_4_QFF; break;
    case 'C': _type = HEUR_EMSRB_4_QFF; break;
    case 'R': _type = HEUR_MRT_QFF; break;
    default: _type = LAST_VALUE; break;
    }

    if (_type == LAST_VALUE) {
      const std::string& lLabels = describeLabels();
      std::ostringstream oMessage;
      oMessage << "The optimization type '" << iType
               << "' is not known. Known optimization types: " << lLabels;
      throw stdair::CodeConversionException (oMessage.str());
    }
  }   

  // //////////////////////////////////////////////////////////////////////
  OptimizationType::OptimizationType (const std::string& iTypeStr) {  
    for (unsigned short idx = 0; idx != LAST_VALUE; ++idx) {
      if (iTypeStr.compare(_labels[idx]) == 0) { 
        _type = static_cast<EN_OptimizationType> (idx);
        break; 
      } else {
        _type = LAST_VALUE;
      }
    }
    if (_type == LAST_VALUE) {
      const std::string& lLabels = describeLabels();
      std::ostringstream oMessage;
      oMessage << "The optimization type '" << iTypeStr
               << "' is not known. Known optimization types: " << lLabels;
      throw stdair::CodeConversionException (oMessage.str());
    }
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string& OptimizationType::
  getLabel (const EN_OptimizationType& iType) {
    return _labels[iType];
  }
  
  // //////////////////////////////////////////////////////////////////////
  char OptimizationType::getTypeLabel (const EN_OptimizationType& iType) {
    return _typeLabels[iType];
  }

  // //////////////////////////////////////////////////////////////////////
  std::string OptimizationType::
  getTypeLabelAsString (const EN_OptimizationType& iType) {
    std::ostringstream oStr;
    oStr << _typeLabels[iType];
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string OptimizationType::describeLabels() {
    std::ostringstream ostr;
    for (unsigned short idx = 0; idx != LAST_VALUE; ++idx) {
      if (idx != 0) {
        ostr << ", ";
      }
      ostr << _labels[idx];
    }
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  OptimizationType::EN_OptimizationType OptimizationType::getType() const {
    return _type;
  }
  
  // //////////////////////////////////////////////////////////////////////
  std::string OptimizationType::getTypeAsString() const {
    std::ostringstream oStr;
    oStr << _typeLabels[_type];
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string OptimizationType::describe() const {
    std::ostringstream ostr;
    ostr << _labels[_type];
    return ostr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  bool OptimizationType::operator== (const EN_OptimizationType& iType) const {
    return (_type == iType);
  }
  
}
