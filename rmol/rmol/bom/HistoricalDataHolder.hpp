#ifndef __RMOL_BOM_HISTORICALDATAHOLDER_HPP
#define __RMOL_BOM_HISTORICALDATAHOLDER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>
// RMOL
#include <rmol/bom/StructAbstract.hpp>

namespace RMOL {
    
  /** HistoricalDataHolder
      [Usage example] 
      Forecast remaining demand 10 days before departure for flight
      2009/09/02 AD101 NCE->CDG Y. 
      HistoricalDataHolder will be the Vector of [45;60;58] if the remaining 
      demand 10days before departure of the following similar flights:
        2009/08/05 AD101 NCE->CDG Y: 45
        2009/08/12 AD101 NCE->CDG Y: 60
        2009/08/19 AD101 NCE->CDG Y: 58 */
  struct HistoricalDataHolder : public StructAbstract {
      
  public:
    // Getters
    /** Get the number of historical data. */
    const double getNumberOfHistoricalData() const {
      return _historicalDataVector.size();
    }

    /** Get the historical data. */
    const double& getHistoricalData(const short i) const {
      return _historicalDataVector.at(i);
    }
    
    /** Get the mean of the data*/
    const double getMean () const;

    /** Get the standard deviation of the data*/
    const double getStandardDeviation (const double& iMean) const;

    /** Add historical data to the holder. */
    void addHistoricalData (const double iHistoricalData) {
      _historicalDataVector.push_back(iHistoricalData);
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
      
    /** Destructors. */
    virtual ~HistoricalDataHolder();
      
  public:
    /** Constructors. */
    HistoricalDataHolder ();

    HistoricalDataHolder (const HistoricalDataHolder&);
      
  private:
    /** Vector of historical data. */
    std::vector<double> _historicalDataVector;
  };
}
#endif // __RMOL_BOM_HISTORICALDATAHOLDER_HPP
