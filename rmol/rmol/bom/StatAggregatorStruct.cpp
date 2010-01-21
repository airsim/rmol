// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <sstream>
#include <limits>
// StdAir
#include <stdair/service/Logger.hpp>
// RMOL
#include <rmol/bom/StatAggregatorStruct.hpp>

namespace RMOL {
  
  // //////////////////////////////////////////////////////////////////////
  StatAggregatorStruct_T::
  StatAggregatorStruct_T (const StudyStatManager& iStudyStatMgr,
                          const std::string& iKey) :
    _studyStatMgr (iStudyStatMgr), _key (iKey),
    _nbOfEvents (0),
    _minimal (std::numeric_limits<int>::max()),
    _maximal (std::numeric_limits<int>::min()),
    _average (0.0),
    _totalTime (0.0){
  }
  
  // //////////////////////////////////////////////////////////////////////
  StatAggregatorStruct_T::StatAggregatorStruct_T
  (const StatAggregatorStruct_T& iStatAggregatorStruct)
    : _studyStatMgr (iStatAggregatorStruct.getStudyStatMgr()),
      _key (iStatAggregatorStruct.getPrimaryKey()),
      _nbOfEvents (iStatAggregatorStruct.getNumberOfEvents()),
      _minimal (iStatAggregatorStruct.getMinimum()),
      _maximal (iStatAggregatorStruct.getMaximum()),
      _average (iStatAggregatorStruct.getAverage()),
      _totalTime (iStatAggregatorStruct.getTotalTime()){
  }

    // //////////////////////////////////////////////////////////////////////
  const std::string StatAggregatorStruct_T::describeCurrentSimu() const {
    std::ostringstream ostr;
    ostr << describeKey() << " - nb of events: " << _nbOfEvents << ", min: "
         << _minimal << ", max: " << _maximal << ",  average :" << _average
         << ", total time: " << _totalTime; 
    return ostr.str();
  }
    
  // //////////////////////////////////////////////////////////////////////
  const std::string StatAggregatorStruct_T::describe() const {
    std::ostringstream ostr;
    ostr << describeKey() << " - nb of events: " << _nbOfEvents << ", min: "
         << _minimal << ", max: " << _maximal << ",  average :" << _average
         << ", average total time: " << _totalTime; 
    return ostr.str();
  }
  
    // //////////////////////////////////////////////////////////////////////
  const std::string StatAggregatorStruct_T::describeKey() const {
    return _key;
  }
  
    // //////////////////////////////////////////////////////////////////////
  void StatAggregatorStruct_T::display() const {
    STDAIR_LOG_DEBUG (describe());
  }

  // //////////////////////////////////////////////////////////////////////
  void StatAggregatorStruct_T::addMeasure (const double iMeasure) {
    // Set a new minimal value if the measure is lower than the minimum
    if (iMeasure < _minimal) {
      _minimal = iMeasure;
    }
    
    // Set a new maximal value if the measure is greater than the maximum
    if (iMeasure > _maximal) {
      _maximal = iMeasure;
    }
    
    // adding up the new measure to the average 
    _average = (_average * _nbOfEvents + iMeasure ) / (_nbOfEvents+1);
    
    // Increment the total time spent
    _totalTime += iMeasure;
    
    // increment the number of event
    _nbOfEvents++;
  }
    
}
