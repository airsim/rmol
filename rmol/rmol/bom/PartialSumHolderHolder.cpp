// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// C
#include <assert.h>
// STL
#include <iostream>
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
  const short PartialSumHolderHolder::getSize () const {
    return _partialSumHolderList.size();
  }

  // //////////////////////////////////////////////////////////////////////
  void PartialSumHolderHolder::toStream (std::ostream& ioOut) const {
    PartialSumHolderList_T::const_iterator itPartialSumHolder = 
      _partialSumHolderList.begin();
    for (short j=1; itPartialSumHolder != _partialSumHolderList.end(); 
	 itPartialSumHolder++, j++) {
      const PartialSumHolder* currentPartialSumHolder_ptr =
	*itPartialSumHolder;
      assert (currentPartialSumHolder_ptr != NULL);

      ioOut << j << "; " << (*currentPartialSumHolder_ptr);
    }
  }

  // //////////////////////////////////////////////////////////////////////
  void PartialSumHolderHolder::display () const {
    toStream (std::cout);
  }

  // //////////////////////////////////////////////////////////////////////
  PartialSumHolder& PartialSumHolderHolder::
  getPreviousPartialSumHolder () const {
    PartialSumHolder* resultPartialSumHolder_ptr = 
      *_itPreviousPartialSumHolder;
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
