#ifndef __RMOL_OPTIMIZATIONTYPE_HPP
#define __RMOL_OPTIMIZATIONTYPE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// StdAir
#include <stdair/basic/StructAbstract.hpp>

namespace RMOL {

  /**
   * Enumeration of optimization types.
   */
  struct OptimizationType : public stdair::StructAbstract {
  public:
    typedef enum { 
      OPT_MC = 0, // Single resource opt. using the Monte Carlo algorithm
      OPT_DP, // Single resource opt. using dynamic programming (DP)
      HEUR_EMSR, // Single resource opt. using EMSR heuristic
      HEUR_EMSRA, // Single resource opt. using EMSR-a heuristic
      HEUR_EMSRB, // Single resource opt. using EMSR-b heuristic
      HEUR_MC_4_QFF, // Single resource opt. using MC algorithm for QFF
      HEUR_EMSRB_4_QFF, // Single resource opt. using EMSRb for QFF
      HEUR_MRT_QFF, // Single resource pre-opt. using MRT for QFF
      LAST_VALUE
    } EN_OptimizationType;

    /**
     * Get the label as a string (e.g., "OptimalByMC", "OptimalByDP",
     * "HeuristicByEMSR", "HeuristicByEMSRa", "HeuristicByEMSRb",
     * "HeuristicByMCForQFF",
     * "HeuristicByEMSRbForQFF" or "HeuristicByMRTForQFF").
     */
    static const std::string& getLabel (const EN_OptimizationType&);

    /** Get the label as a single char 
     * (e.g., 'M', 'D', 'E', 'A', 'B', 'Q', 'C' or 'R'). 
     */
    static char getTypeLabel (const EN_OptimizationType&);

    /** Get the label as a string of a single char 
     * (e.g., "M", "D", "E", "A", "B", "Q", "C" or "R"). 
     */
    static std::string getTypeLabelAsString (const EN_OptimizationType&);

    /** List the labels. */
    static std::string describeLabels();

    /** Get the enumerated value. */
    EN_OptimizationType getType() const;

    /** Get the enumerated value as a short string 
     * (e.g., "M", "D", "E", "A", "B", "Q", "C" or "R"). 
     */
    std::string getTypeAsString() const;
    
    /**
     * Get a description of the structure (e.g., "OptimalByMC", "OptimalByDP",
     * "HeuristicByEMSR", "HeuristicByEMSRa", "HeuristicByEMSRb",
     * "HeuristicByMCForQFF",
     * "HeuristicByEMSRbForQFF" or "HeuristicByMRTForQFF").
     */
    const std::string describe() const;

  public:
    /** Comparison operator. */
    bool operator== (const EN_OptimizationType&) const;
    
  public:
    /** Constructor. */
    OptimizationType (const EN_OptimizationType&);
    /** Constructor using a char. */
    OptimizationType (const char iType);  
    /** Constructor using a string. */
    OptimizationType (const std::string& iTypeStr);
    /** Default copy constructor. */
    OptimizationType (const OptimizationType&);

  private:
    /** Default constructor. */
    OptimizationType();
  

  private:
    /** String version of the enumeration. */    
    static const std::string _labels[LAST_VALUE];
    /** Type version of the enumeration. */    
    static const char _typeLabels[LAST_VALUE];


  private:
    // //////// Attributes /////////
    /** Optimization type. */
    EN_OptimizationType _type;
  };

}
#endif // __RMOL_OPTIMIZATIONTYPE_HPP
