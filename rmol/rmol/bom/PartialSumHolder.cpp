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
  void PartialSumHolder::toStream (std::ostream& ioOut) const {
    // Generate a CSV (Comma Separated Values) output
    ioOut << "Partial Sum (K = " << _partialSumList.size() << "); " 
	  << std::endl;

    PartialSumList_T::const_iterator itPartialSum = _partialSumList.begin();
    for (short k=1; itPartialSum != _partialSumList.end(); itPartialSum++,k++){
      const double currentPartialSum = *itPartialSum;
      ioOut << k << "; " << currentPartialSum;
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void PartialSumHolder::display () const {
    toStream (std::cout);
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

}
