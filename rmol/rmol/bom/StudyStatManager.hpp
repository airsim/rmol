#ifndef __RMOL_BOM_STUDYSTATMANAGER_HPP
#define __RMOL_BOM_STUDYSTATMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// RMOL
#include <rmol/bom/BomAbstract.hpp>
#include <rmol/bom/StatAggregatorStructList.hpp>

namespace RMOL {

  /** Class managing all the statistics in the process. */
  class StudyStatManager : public BomAbstract {
    friend class FacStudyStatManager;
  public:
    // /////////// Getters //////////////
    /** Function which returns the statAggregatorStruct corresponding
        to the string given in parameter.
        If it does not exist, it is created.*/
    StatAggregatorStruct_T& getStatAggregator(const std::string&);

    // ///////// Busines methods //////////
    /** Dump a Business Object into an output stream.
        @param ostream& the output stream. */
    void toStream (std::ostream&) const;

    /** Read a Business Object from an input stream.
        @param istream& the input stream. */
    void fromStream (std::istream&);

    /** Get the serialised version of the Place object. */
    std::string toString() const;

    /** Get a string describing the whole key (differentiating two objects
        at any level). */
    const std::string describeKey() const;

    /** Get a string describing the short key (differentiating two objects
        at the same level). */
    const std::string describeShortKey() const;

    /** Setting up a measure. */
    void addMeasure (const std::string, const double);
    
    // ///////// Display Methods //////////
    /** Give a description of the statistics (for display purposes). */
    const std::string describe() const;
    
    /** Display the full StudyStatManager context. */
    void display() const;
    
  private:
    /** Constructors are private so as to force the usage of the Factory
        layer. */
    /** Default constructors. */
    StudyStatManager ();
    StudyStatManager (const StudyStatManager&);
      
    /** Destructor. */
    virtual ~StudyStatManager();
    
    /** Get the list of stat aggregators for the current simulation. */
    StatAggregatorStructList_T& getStatAggregatorStructList() {
      return _statAggregatorStructList;
    }
    
  private:
    
    /** StatAggregatorStructList_T which is a STL map linking
        StatAggregatorStruct Keys and StatAggregatorStruct for the
        current simulation. */
    StatAggregatorStructList_T _statAggregatorStructList;
  };

}
#endif // __RMOL_BOM_STUDYSTATMANAGER_HPP
