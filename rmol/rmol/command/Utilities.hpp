#ifndef __RMOL_COMMAND_UTILITIES_HPP
#define __RMOL_COMMAND_UTILITIES_HPP
// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <vector>

namespace RMOL {

  struct Utilities {

    /** Returns the minimum element of a given vector*/
    static void getMinimumElement (double* oMinValue, std::vector<double>&); 

    /** Return mean for the given elements of a vector. */
    static void getMean (double& oMean, std::vector<double>&);

    /** Return standard deviation for the given elements of a vector and  
        precomputed mean. */
    static void getStandardDeviation (double& oSD, std::vector<double>&,
                                      double& iMean);

    /** Return mean & standard deviation for given elements of a vector. */
    static void getMeanAndStandardDeviation (std::vector<double>* ioMean_SD,
                                             std::vector<double>&);

    /** Return the input vector after adding a value. */
    static void AddAValueToAVector (std::vector<double>& ioVector, 
                                    double iValue);

    /** Return the input vector after multiplying a value. */
    static void MultiplyAValueToAVector (std::vector<double>& ioVector, 
                                         double iValue);

    /** Return first input vector after adding 2nd input vector to it. */
    static void AddTwoVectors (std::vector<double>& ioVector, 
                               std::vector<double>& iVector);
    
  };

}

#endif // __RMOL_COMMAND_UTILITIES_HPP
