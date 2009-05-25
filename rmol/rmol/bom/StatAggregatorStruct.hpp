#ifndef __RMOL_BOM_STATAGGREGATORSTRUCT_HPP
#define __RMOL_BOM_STATAGGREGATORSTRUCT_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>

namespace RMOL {
  
    // Forward declarations
  class StudyStatManager;
  
  /** Utility Structure for the aggregator of statistic values. */
  struct StatAggregatorStruct_T {
    /** Constructors. */
    StatAggregatorStruct_T (const StudyStatManager&,
                            const std::string&);
    
    StatAggregatorStruct_T (const StatAggregatorStruct_T&);
    
    // /////////// Getters //////////////
    /** Get the parent class. */
    const StudyStatManager& getParent() const {
      return getStudyStatMgr();
    }
    
    /** Get the StudyStatManager (parent class). */
    const StudyStatManager& getStudyStatMgr() const {
      return _studyStatMgr;
      }
    
    /** Get the primary key. */
    const std::string getPrimaryKey() const {
      return getStatAggregatorStructKey();
    }

    /** Get the StatAggregatorStruct key. */
    const std::string getStatAggregatorStructKey() const {
      return _key;
    }
    
    /** Get the number of events. */
    const unsigned int getNumberOfEvents() const {
      return _nbOfEvents;
    }
    
    /** Get the minimal value. */
    const double getMinimum() const {
      return _minimal;
    }
    
    /** Get the maximal value. */
    const double getMaximum() const {
      return _maximal;
    }
    
    /** Get the average value. */
    const double getAverage() const {
      return _average;
    }
    
    /** Get the total time value (in seconds). */
    const double getTotalTime() const {
      return _totalTime;
    }
    
    // ///////// Setters //////////
    
    // ///////// Display Methods //////////
    /** Give a description of the structure for the current simulation. */
    const std::string describeCurrentSimu() const;
    
    /** Give a description of the structure (which is a resume of statistics
        from all simulation runs). */
    const std::string describe() const;
    
    /** Get a string describing the key. */
    const std::string describeKey() const;
    
    /** Display the StatAggregatorStruct context. */
    void display() const;
    
    // ///////// Business Methods //////////
    /** add meassure. */
    void addMeasure (const double);

  private:
    // /////////////// Attributes //////////
    // Parent
    /** Parent class: StudyStatManager. */
    const StudyStatManager& _studyStatMgr;
    
    // Primary Key
    /** StatAggregatorStruct Key is composed of a dedicated string. */
    std::string _key;
    
    // Attributes
    unsigned int _nbOfEvents;
    double _minimal;
    double _maximal;
    double _average;
    double _totalTime;
    
  };
  
}
#endif // __RMOL_BOM_STATAGGREGATORSTRUCT_HPP
