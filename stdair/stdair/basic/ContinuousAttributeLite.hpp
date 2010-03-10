#ifndef __STDAIR_BAS_CONTINUOUSATTRIBUTELITE_HPP
#define __STDAIR_BAS_CONTINUOUSATTRIBUTELITE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <map>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/DictionaryManager.hpp>
#include <stdair/service/Logger.hpp>

namespace stdair {

  /** Class modeling the distribution of values that can be taken by a
      continuous attribute. */
  template <class T>
  struct ContinuousAttributeLite {
  public:
    // ///////////// Type definitions //////////////
    typedef std::multimap<T, Probability_T> ContinuousDistribution_T;
    
  public:
    // /////////////// Business Methods //////////
    /** Get value from inverse cumulative distribution. */
    const T getValue (const Probability_T& iCumulativeProbability) const {
      const DictionaryKey_T lKey =
        DictionaryManager::valueToKey (iCumulativeProbability);
      unsigned int idx = 0;

      // Find the first cumulative probablity value greater or equal to lKey.
      for (; idx < _size; ++idx) {
        if (_cumulativeDistribution[idx] >= lKey) {
          break;
        }
      }

      if (idx == 0) {
        return _valueArray[idx];
      }

      Probability_T lCumulativeCurrentPoint =
        DictionaryManager::keyToValue (_cumulativeDistribution[idx]);
      Probability_T lCumulativePreviousPoint =
        DictionaryManager::keyToValue (_cumulativeDistribution[idx-1]);
      T lValueCurrentPoint = _valueArray[idx];
      T lValuePreviousPoint = _valueArray[idx-1];

      if (lCumulativePreviousPoint == lCumulativeCurrentPoint) {
        return lValuePreviousPoint;
      }

      return lValuePreviousPoint + (lValueCurrentPoint - lValuePreviousPoint)
        * (iCumulativeProbability - lCumulativePreviousPoint)
        / (lCumulativeCurrentPoint - lCumulativePreviousPoint);
    }
    
  public:
    // ////////////// Display Support Methods //////////
    /** Display cumulative distribution */
    const std::string displayCumulativeDistribution() const {
      std::ostringstream oStr;
      
      for (unsigned int idx = 0; idx < _size; ++idx) {
        if (idx != 0) {
          oStr << ", ";
        }
        oStr << _valueArray[idx] << ":"
             << DictionaryManager::keyToValue (_cumulativeDistribution[idx]);
      }
      return oStr.str();
    }

  public:
    // ////////// Constructors and destructors /////////
    /** Constructor */
    ContinuousAttributeLite (const ContinuousDistribution_T& iValueMap)
      : _size (iValueMap.size()) {
      _cumulativeDistribution = new DictionaryKey_T[_size];
      _valueArray = new T[_size];
      init (iValueMap);
    }
    
    /** Destructor */
    virtual ~ContinuousAttributeLite () {
      // TODO: Verify that the arrays are correctly cleaned.
      delete _cumulativeDistribution; _cumulativeDistribution = NULL;
      delete _valueArray; _valueArray = NULL;
    }

  private:
    /** Constructors by default */
    ContinuousAttributeLite ();
    ContinuousAttributeLite (const ContinuousAttributeLite&);

    /** Determine inverse cumulative distribution from cumulative
        distribution (initialisation). */
    void init (const ContinuousDistribution_T& iValueMap) {
      unsigned int idx = 0;

      // Browse the map to retrieve the values and cumulative probabilities.
      for (typename ContinuousDistribution_T::const_iterator it =
             iValueMap.begin(); it != iValueMap.end(); ++it, ++idx) {
        
        T attributeValue = it->first;
        DictionaryKey_T lKey = DictionaryManager::valueToKey (it->second);
        
        // Build the two arrays.
        _cumulativeDistribution[idx] = lKey;
        _valueArray[idx] = attributeValue;
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
#endif // __STDAIR_BAS_CONTINUOUSATTRIBUTELITE_HPP
