// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
#include <algorithm>
// RMOL
#include <rmol/bom/PartialSumHolder.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  PartialSumHolder::PartialSumHolder () {
  }

  // //////////////////////////////////////////////////////////////////////
  PartialSumHolder::
  PartialSumHolder (const PartialSumHolder& iPartialSumHolder) {
  }

  // //////////////////////////////////////////////////////////////////////
  PartialSumHolder::~PartialSumHolder() {
    _partialSumList.clear ();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string PartialSumHolder::describeShortKey() const {
    std::ostringstream oStr;
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string PartialSumHolder::describeKey() const {
    return describeShortKey();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string PartialSumHolder::toString() const {
    std::ostringstream oStr;
    oStr << _partialSumList.size();
    return oStr.str();
  }   

  // //////////////////////////////////////////////////////////////////////
  void PartialSumHolder::toStream (std::ostream& ioOut) const {
    ioOut << toString();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void PartialSumHolder::fromStream (std::istream& ioIn) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string PartialSumHolder::shortDisplay() const {
    std::ostringstream oStr;
    oStr << describeKey();
    // Generate a CSV (Comma Separated Values) output
    oStr << "Partial Sum (K = " << _partialSumList.size() << ")" << std::endl;
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string PartialSumHolder::display() const {
    std::ostringstream oStr;
    oStr << shortDisplay();

    PartialSumList_T::const_iterator itPartialSum = _partialSumList.begin();
    for (short k=1; itPartialSum != _partialSumList.end(); itPartialSum++,k++){
      const double currentPartialSum = *itPartialSum;
      oStr << k << "; " << currentPartialSum;
    }
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  void PartialSumHolder::initSize (const int K) {
    _partialSumList.reserve (K);
  }

  // //////////////////////////////////////////////////////////////////////
  const double PartialSumHolder::getPartialSum (const int k) const {
    return _partialSumList.at (k);
  }

  // //////////////////////////////////////////////////////////////////////
  void PartialSumHolder::addPartialSum (const double iPartialSum) {
    _partialSumList.push_back (iPartialSum);
  }

  // //////////////////////////////////////////////////////////////////////
  void PartialSumHolder::sort () {
    std::sort (_partialSumList.begin(), _partialSumList.end());
  }

  // //////////////////////////////////////////////////////////////////////
  const int PartialSumHolder::getLowerBound (const double& value) const {
    PartialSumList_T::const_iterator itLowerBound =
      std::lower_bound (_partialSumList.begin(), _partialSumList.end() , value);
    const int position = itLowerBound - _partialSumList.begin();
    return position;
  }

}
