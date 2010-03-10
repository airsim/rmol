#ifndef __STDAIR_BAS_CATEGORICALATTRIBUTELITE_HPP
#define __STDAIR_BAS_CATEGORICALATTRIBUTELITE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <map>
#include <iosfwd>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/DictionaryManager.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  /** Class modeling the distribution of values that can be taken by a
      categorical attribute. */
  template <class T>
  struct CategoricalAttributeLite {    
    public:
    /** Define the probability mass function type. */
    typedef std::map<T, Probability_T> ProbabilityMassFunction_T;
    
  public:
    // /////////////// Business Methods //////////
    /** Get value from inverse cumulative distribution. */
    const T getValue (Probability_T iCumulativeProbability) const {
      const DictionaryKey_T lKey =
        DictionaryManager::valueToKey (iCumulativeProbability);

      for (unsigned int idx = 0; idx < _size; ++idx) {
        if (_cumulativeDistribution[idx] >= lKey) {
          return _valueArray[idx];
        }
      }

      STDAIR_LOG_ERROR ("The following cumulative probability "
                        << "is out of range: " << iCumulativeProbability);
      assert (false);
      T t;
      return t;
    }
    
  public:
    // ////////////// Display Support Methods //////////
    /** Display probability mass function. */
    const std::string displayProbabilityMass () const {
      std::ostringstream oStr;

      for (unsigned int idx = 0; idx < _size; ++idx) {
        if (idx != 0) {
          oStr << ", ";
        }
        oStr << _valueArray [idx] << ":"
             << DictionaryManager::keyToValue (_cumulativeDistribution[idx]);
      }
      return oStr.str();
    }
        
  public:
    // ////////// Constructors and destructors /////////
    /** Constructor by default */
    CategoricalAttributeLite (const ProbabilityMassFunction_T& iValueMap)
      : _size (iValueMap.size()) {
      _cumulativeDistribution = new DictionaryKey_T[_size];
      _valueArray = new T[_size];
      init (iValueMap);
    }
    /** Destructor */
    virtual ~CategoricalAttributeLite () {
      // TODO: Verify that the arrays are correctly cleaned.
      delete _cumulativeDistribution; _cumulativeDistribution = NULL;
      delete _valueArray; _valueArray = NULL;
    }

  private:
    /** Default constructors. */
    CategoricalAttributeLite ();
    CategoricalAttributeLite (const CategoricalAttributeLite&);


    /** Initialise the two arrays from the given map. */
    void init (const ProbabilityMassFunction_T& iValueMap) {
      
      Probability_T cumulative_probability_so_far = 0.0;
      unsigned int idx = 0;

      // Browse the map to retrieve the values and to build the
      // cumulative probabilities.
      for (typename ProbabilityMassFunction_T::const_iterator itProbabilityMassFunction = iValueMap.begin();
           itProbabilityMassFunction != iValueMap.end();
           ++itProbabilityMassFunction, ++idx) {
        
        Probability_T attribute_probability_mass =
          itProbabilityMassFunction->second;
        if (attribute_probability_mass > 0) {
          T attribute_value = itProbabilityMassFunction->first;
          cumulative_probability_so_far += attribute_probability_mass;
          DictionaryKey_T lKey =
            DictionaryManager::valueToKey (cumulative_probability_so_far);

          // Build the two arrays.
          _cumulativeDistribution[idx] = lKey;
          _valueArray[idx] = attribute_value;
        }
      }
    }
  
  private:
    // ////////// Attributes //////////
    /** Size of the two arrays. */
    const unsigned int _size;
    
    /** Cumulative dictionary-coded distribution. */
    DictionaryKey_T* _cumulativeDistribution;

    /** The corresponding values. */
    T* _valueArray;
  };
}
#endif // __STDAIR_BAS_CATEGORICALATTRIBUTELITE_HPP
