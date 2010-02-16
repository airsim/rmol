#ifndef __STDAIR_BAS_CATEGORICALATTRIBUTE_HPP
#define __STDAIR_BAS_CATEGORICALATTRIBUTE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <iosfwd>
// STDAIR
#include <stdair/STDAIR_Types.hpp>

namespace stdair {

  /** Class modeling the distribution of values that can be taken by a
      categorical attribute. */
  template <class T>
  struct CategoricalAttribute {

  public:
    /** Define the probability mass function type. */
    typedef std::map<T, Probability_T> ProbabilityMassFunction_T;

    /** Define the inverse cumulative distribution type. */
    typedef std::map<Probability_T, T> InverseCumulativeDistribution_T;
    
  public:
    // ///////////// Getters ///////////
    /** Get the probability mass function. */
    const std::map<T,Probability_T>& getProbabilityMassFunction() const {
      return _probabilityMassFunction;
    }
  
    /** Get the inverse cumulative distribution. */
    const InverseCumulativeDistribution_T& getInverseCumulativeDistribution () const {
      return _inverseCumulativeDistribution;
    }

    // ///////////// Setters ///////////
    /** Set the probability mass function */
    void setProbabilityMassFunction (const ProbabilityMassFunction_T& iProbabilityMassFunction) {
      _probabilityMassFunction = iProbabilityMassFunction;
      determineInverseCumulativeDistributionFromProbabilityMassFunction();
    }

  public:
    // /////////////// Business Methods //////////
    /** Get value from inverse cumulative distribution. */
    const T getValue (Probability_T iCumulativeProbability) const {
      return _inverseCumulativeDistribution.
        lower_bound (iCumulativeProbability)->second;
    }
    
  public:
    // ////////////// Display Support Methods //////////
    /** Display probability mass function. */
    const std::string displayProbabilityMassFunction () const {
      std::ostringstream oStr;
      unsigned int idx = 0;
      
      for (typename ProbabilityMassFunction_T::const_iterator it =
             _probabilityMassFunction.begin();
           it != _probabilityMassFunction.end(); ++it, ++idx) {
        if (idx != 0) {
          oStr << ", ";
        }
        oStr << it->first << ":" << it->second;        
      }
      
      return oStr.str();
    }
    
    /** Display inverse cumulative distribution. */
    const std::string displayInverseCumulativeDistribution () const {
      std::ostringstream oStr;
      
      for (typename InverseCumulativeDistribution_T::const_iterator it = 
             _inverseCumulativeDistribution.begin();
           it != _inverseCumulativeDistribution.end(); ++it) {
        oStr << "cumulative prob: " << it->first
                 << "  value: " << it->second << std::endl;
      }

      return oStr.str();
    }
    
  public:
    // ////////// Constructors and destructors /////////
    /** Constructor by default */
    CategoricalAttribute (const ProbabilityMassFunction_T& iProbabilityMassFunction)
      : _probabilityMassFunction (iProbabilityMassFunction) {
      determineInverseCumulativeDistributionFromProbabilityMassFunction();
    }
    /** Default constructors. */
    CategoricalAttribute () { }
    CategoricalAttribute (const CategoricalAttribute& iCategoricalAttribute)
      : _probabilityMassFunction (iCategoricalAttribute._probabilityMassFunction) {
      determineInverseCumulativeDistributionFromProbabilityMassFunction();
    }

    /** Destructor */
    virtual ~CategoricalAttribute () { }


    /** Determine inverse cumulative distribution from probability mass function (initialisation). */
    void determineInverseCumulativeDistributionFromProbabilityMassFunction () {
      Probability_T cumulative_probability_so_far = 0.0;
      for (typename ProbabilityMassFunction_T::const_iterator itProbabilityMassFunction = _probabilityMassFunction.begin();
           itProbabilityMassFunction != _probabilityMassFunction.end();
           ++itProbabilityMassFunction) {
        Probability_T attribute_probability_mass = itProbabilityMassFunction->second;
        if (attribute_probability_mass > 0) {
          T attribute_value = itProbabilityMassFunction->first;
          cumulative_probability_so_far += attribute_probability_mass;
          _inverseCumulativeDistribution[cumulative_probability_so_far] = attribute_value;
        }
      }
    }
  
  private:
    // ////////// Attributes //////////
    /** Probability mass function */
    ProbabilityMassFunction_T _probabilityMassFunction;
    
    /** Inverse cumulative distribution */
    InverseCumulativeDistribution_T _inverseCumulativeDistribution;
    
  };
}
#endif // __STDAIR_BAS_CATEGORICALATTRIBUTE_HPP
