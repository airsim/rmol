// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <iomanip>
// RMOL
#include <rmol/bom/Demand.hpp>
#include <rmol/bom/Bucket.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  Bucket::Bucket ()
    : _demand (NULL),
      _yieldRange (), _protection (0.0), _cumulatedProtection (0.0),
      _bookingLimit (0.0), _cumulatedBookingLimit (0.0),
      _generatedDemandVector (NULL) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  Bucket::Bucket (const Bucket& iBucket) :
    _demand (&iBucket.getDemand()), 
    _yieldRange (iBucket.getYieldRange()), 
    _protection (iBucket.getProtection()),
    _cumulatedProtection (iBucket.getCumulatedProtection()),
    _bookingLimit (iBucket.getBookingLimit()),
    _cumulatedBookingLimit (iBucket.getCumulatedBookingLimit()),
    _generatedDemandVector (NULL) {
  }

  // //////////////////////////////////////////////////////////////////////
  Bucket::Bucket (const FldYieldRange& iYieldRange) :
    _demand (NULL),
    _yieldRange (iYieldRange), _protection (0.0), _cumulatedProtection (0.0),
    _bookingLimit (0.0), _cumulatedBookingLimit (0.0),
    _generatedDemandVector (NULL) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  Bucket::~Bucket() {
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string Bucket::describeShortKey() const {
    std::ostringstream oStr;
    oStr << _yieldRange;
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string Bucket::describeKey() const {
    return describeShortKey();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string Bucket::toString() const {
    std::ostringstream oStr;
    oStr << describeShortKey() << ", ";
    const double pj = getUpperYield();
    const double mj = getMean();
    const double sj = getStandardDeviation();
    const double proj = getProtection();
    const double yj = getCumulatedProtection();
    const double bj = getCumulatedBookingLimit();
    oStr << std::fixed << std::setprecision (2)
         << pj << "; " << mj << "; " << sj << "; " << proj << "; " << yj
         << "; " << bj << std::endl;
    
    return oStr.str();
  }   

  // //////////////////////////////////////////////////////////////////////
  void Bucket::toStream (std::ostream& ioOut) const {
    ioOut << toString();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void Bucket::fromStream (std::istream& ioIn) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string Bucket::shortDisplay() const {
    std::ostringstream oStr;
    oStr << describeKey();
    const double pj = getUpperYield();
    const double mj = getMean();
    const double sj = getStandardDeviation();
    const double proj = getProtection();
    const double yj = getCumulatedProtection();
    const double blj = getBookingLimit();
    const double bj = getCumulatedBookingLimit();
    oStr << std::fixed << std::setprecision (2)
         << ", upper yield = " << pj << "; "
         << ", mean = " << mj << "; " << ", std_dev = " << sj << "; "
         << ", protection = " << proj << "; "
         << ", cumulative protection = " << yj << "; "
         << ", booking limit = " << blj
         << ", cumulative booking limit = " << bj << std::endl;

    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string Bucket::display() const {
    std::ostringstream oStr;
    oStr << shortDisplay();
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const FldDistributionParameters& Bucket::getDistributionParameters() const {
    assert (_demand != NULL);
    return _demand->getDistributionParameters();
  }

  // //////////////////////////////////////////////////////////////////////
  Demand& Bucket::getDemand() const {
    assert (_demand != NULL);
    return *_demand;
  }

  // //////////////////////////////////////////////////////////////////////
  void Bucket::setDemand (Demand& iDemand) {
    _demand = &iDemand;
  }

  // //////////////////////////////////////////////////////////////////////
  void Bucket::setYieldRange (const double iYield) {
    _yieldRange.setUpperYield (iYield);
    _yieldRange.setAverageYield (iYield);
    _yieldRange.setLowerYield (iYield);
  }

  // //////////////////////////////////////////////////////////////////////
  void Bucket::setDemandParameters (const double iMean, const double iSD) {
    _demand->setMean (iMean);
    _demand->setSD (iSD);
  }

  // //////////////////////////////////////////////////////////////////////
  const double Bucket::getMean() const {
    assert (_demand != NULL);
    return _demand->getMean();
  }

  // //////////////////////////////////////////////////////////////////////
  const double Bucket::getStandardDeviation() const {
    assert (_demand != NULL);
    return _demand->getStandardDeviation();
  }

  // //////////////////////////////////////////////////////////////////////
  const double Bucket::getUpperYield() const {
    return _yieldRange.getUpperYield();
  }

  // //////////////////////////////////////////////////////////////////////
  const double Bucket::getAverageYield() const {
    return _yieldRange.getAverageYield();
  }

  // //////////////////////////////////////////////////////////////////////
  const double Bucket::getLowerYield() const {
    return _yieldRange.getLowerYield();
  }

  // //////////////////////////////////////////////////////////////////////
  void Bucket::
  setGeneratedDemandVector (GeneratedDemandVector_T* iVector) {
    _generatedDemandVector = iVector;
  }

}
