#ifndef __RMOL_BOM_HISTORICALDATAHOLDERHOLDER_HPP
#define __RMOL_BOM_HISTORICALDATAHOLDERHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
// RMOL 
#include <rmol/bom/StructAbstract.hpp>

namespace RMOL {

  /** Forward declaration. */
  struct HistoricalDataHolder;
    
  /** Define a vector (ordered list) of N HistoricalDatas. */
  typedef std::vector<HistoricalDataHolder> HistoricalDataVectorVector_T;
    
  /** Holder of a HistoricalDataHolder object.
      [Usage example] 
      When computing Q-equivalent bookings, multiple HistoricalDataHolders 
      are needed. For example, 
      a HistoricalDataHolder of 2009/09/02 AD101 NCE->CDG Y & 
      a HistoricalDataHolder of 2009/09/02 AD101 NCE->CDG K.  */
  struct HistoricalDataHolderHolder : public StructAbstract {
      
  public:
    // ////// Getters //////
    /** Get the number of HistoricalDataHolder*/
    const short getNumberOfHistoricalDataHolder () const {
      return _historicalDataVectorVector.size();
    }

    /** Get the (i+1)th HistoricalDataHolder. */
    const HistoricalDataHolder& getHistoricalDataHolder (const short i) const{
      return _historicalDataVectorVector.at(i);
    }

    // ////// Setters //////
    /** Add a HistoricalData object to the holder. */
    void addHistoricalDataHolder (const HistoricalDataHolder iHDHolder) {
      _historicalDataVectorVector.push_back(iHDHolder);
    }

    /** Dump a Business Object into an output stream.
        @param ostream& the output stream
        @return ostream& the output stream. */
    void toStream (std::ostream& ioOut) const;

    // ///////// Display Methods //////////
    /** Give a description of the structure (for display purposes). */
    const std::string describe() const;
      
    /** Display on standard output. */
    void display () const;
      
    /** Destructor. */
    virtual ~HistoricalDataHolderHolder();
      
  public:
    /** Constructor.
        <br>Protected to force the use of the Factory. */
    HistoricalDataHolderHolder ();

  private:
      
    /** The list of (N) buckets/classes. */
    HistoricalDataVectorVector_T _historicalDataVectorVector;
      
  };
}
#endif // __RMOL_BOM_HISTORICALDATAHOLDERHOLDER_HPP
  
