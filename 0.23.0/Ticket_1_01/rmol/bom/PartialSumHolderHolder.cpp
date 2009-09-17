// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <istream>
#include <ostream>
// RMOL
#include <rmol/bom/PartialSumHolder.hpp>
#include <rmol/bom/PartialSumHolderHolder.hpp>

namespace RMOL {

  // //////////////////////////////////////////////////////////////////////
  PartialSumHolderHolder::PartialSumHolderHolder () {
  }

  // //////////////////////////////////////////////////////////////////////
  PartialSumHolderHolder::~PartialSumHolderHolder() {
    _partialSumHolderList.clear ();
  }

  // //////////////////////////////////////////////////////////////////////
  const std::string PartialSumHolderHolder::describeShortKey() const {
    std::ostringstream oStr;
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string PartialSumHolderHolder::describeKey() const {
    return describeShortKey();
  }

  // //////////////////////////////////////////////////////////////////////
  std::string PartialSumHolderHolder::toString() const {
    std::ostringstream oStr;
    return oStr.str();
  }   

  // //////////////////////////////////////////////////////////////////////
  void PartialSumHolderHolder::toStream (std::ostream& ioOut) const {
    ioOut << toString();
  }
  
  // //////////////////////////////////////////////////////////////////////
  void PartialSumHolderHolder::fromStream (std::istream& ioIn) {
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string PartialSumHolderHolder::shortDisplay() const {
    std::ostringstream oStr;
    oStr << describeKey();
    return oStr.str();
  }
  
  // //////////////////////////////////////////////////////////////////////
  const std::string PartialSumHolderHolder::display() const {
    std::ostringstream oStr;
    oStr << shortDisplay();

    PartialSumHolderList_T::const_iterator itPartialSumHolder = 
      _partialSumHolderList.begin();
    for (short j = 1; itPartialSumHolder != _partialSumHolderList.end(); 
         itPartialSumHolder++, j++) {
      const PartialSumHolder* currentPartialSumHolder_ptr = *itPartialSumHolder;
      assert (currentPartialSumHolder_ptr != NULL);
      
      oStr << j << "; " << currentPartialSumHolder_ptr->display();
    }
    return oStr.str();
  }

  // //////////////////////////////////////////////////////////////////////
  const short PartialSumHolderHolder::getSize () const {
    return _partialSumHolderList.size();
  }

  // //////////////////////////////////////////////////////////////////////
  PartialSumHolder& PartialSumHolderHolder::
  getPreviousPartialSumHolder () const {
    PartialSumHolder* resultPartialSumHolder_ptr=  *_itPreviousPartialSumHolder;
    assert (resultPartialSumHolder_ptr != NULL);
    return (*resultPartialSumHolder_ptr);
  }

  // //////////////////////////////////////////////////////////////////////
  PartialSumHolder& PartialSumHolderHolder::
  getCurrentPartialSumHolder () const {
    PartialSumHolder* resultPartialSumHolder_ptr = *_itCurrentPartialSumHolder;
    assert (resultPartialSumHolder_ptr != NULL);
    return (*resultPartialSumHolder_ptr);
  }

  // //////////////////////////////////////////////////////////////////////
  bool PartialSumHolderHolder::hasNotReachedEnd () const {
    bool result = (_itCurrentPartialSumHolder != _partialSumHolderList.end());
    return result;
  }

  // //////////////////////////////////////////////////////////////////////
  void PartialSumHolderHolder::
  addPartialSumHolder (PartialSumHolder& ioPartialSumHolder) {
    _partialSumHolderList.push_back (&ioPartialSumHolder);
  }

  // //////////////////////////////////////////////////////////////////////
  void PartialSumHolderHolder::begin () {
    _itCurrentPartialSumHolder = _partialSumHolderList.begin();
    _itPreviousPartialSumHolder = _partialSumHolderList.begin();
  }

  // //////////////////////////////////////////////////////////////////////
  void PartialSumHolderHolder::iterate () {
    if (_itCurrentPartialSumHolder != _partialSumHolderList.begin()) {
      _itPreviousPartialSumHolder++;

    } else {
      assert (_itPreviousPartialSumHolder == _partialSumHolderList.begin());
    }

    if (_itCurrentPartialSumHolder != _partialSumHolderList.end()) {
      _itCurrentPartialSumHolder++;
    }
  }

}
