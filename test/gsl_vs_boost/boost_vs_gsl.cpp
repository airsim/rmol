// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iostream>
// GSL
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
// Boost Math
#include <boost/math/distributions/binomial.hpp>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/special_functions/round.hpp>

// Alias for the Boost::Math namespace
namespace bm = boost::math;

// /////////////////////// M A I N //////////////////////////////
int main (int argc, char* agrv[]) {

  //
  std::cout << std::endl
            << "Compare Boost.Math vs GSL (GNU Scientific Library)"
            << std::endl;

  std::cout
    << "* For the GSL, see http://www.gnu.org/software/gsl/manual/html_node/"
    << std::endl
    << "* For Boost.Math, see "
    << "http://www.boost.org/doc/libs/1_44_0/libs/math/doc/sf_and_dist/html/index.html"
    << std::endl;
  std::cout
    << "All the following resuls are compared with a precision of 1e-8. "
    << std::endl
    << "If one of those results are not equal for GSL and Boost, "
    << "the program aborts."
    << std::endl << std::endl;

  const double precision = 1e-8;

  //
  const double mean = 10.0;
  const double sigma = 2.0;

  // Boost distributions need first to be instantiated
  bm::normal normalDistribution (mean, sigma);

  std::cout
    << "___________________________________________" << std::endl
    << "   pdf and cdf of a normal distribution    " << std::endl
    << "___________________________________________" << std::endl << std::endl;
  std::cout << std::setprecision(7);
  std::cout << std::setw(15) << std::left << "Mean = " << mean << std::endl;
  std::cout << std::setw(15) << std::left << "Sigma = " << sigma << std::endl;
  std::cout << std::endl;

  std::cout
    << "_______________________________________________________________________"
    << std::endl
    << "                   GSL           Boost           GSL           Boost   "
    << std::endl
    << " Value (x)         pdf            pdf            cdf            cdf "
    << std::endl
    << "_______________________________________________________________________"
    << std::endl;

  for (double x = mean - 5*sigma; x <= mean + 5*sigma; ++x) {
    // 
    std::cout << std::fixed << std::setprecision(3)
              << std::setw(10) << std::right << x;

    // Normal pdf (probability distribution function)
    const double lNormalPdfGSL = gsl_ran_gaussian_pdf (x - mean, sigma);
    const double lNormalPdfBoost = bm::pdf (normalDistribution, x);

    // Normal cdf (cumulated probability distribution function)
    const double lNormalCdfGSL = gsl_cdf_gaussian_P (x - mean, sigma);
    const double lNormalCdfBoost = bm::cdf (normalDistribution, x);

    // Print probabilities
    std::cout << std::fixed << std::setprecision(5)
              << std::setw(15) << std::right << lNormalPdfGSL
              << std::setw(15) << std::right << lNormalPdfBoost
              << std::setw(15) << std::right << lNormalCdfGSL
              << std::setw(15) << std::right << lNormalCdfBoost
              << std::endl;

    // Check that the GSL results are the same of those from Boost Math
    assert (bm::round (lNormalPdfGSL / precision)
            == bm::round (lNormalPdfBoost / precision));
    assert (bm::round (lNormalCdfGSL / precision)
            == bm::round (lNormalCdfBoost / precision));
  }
  
  std::cout
    << "___________________________________________" << std::endl
    << " Inverse of cdf for a normal distribution  " << std::endl
    << "___________________________________________" << std::endl << std::endl;
  std::cout << std::setprecision(7);
  std::cout << std::setw(15) << std::left << "Mean = " << mean << std::endl;
  std::cout << std::setw(15) << std::left << "Sigma = " << sigma << std::endl;
  std::cout << std::endl;

  std::cout
    << "_______________________________________________________________________"
    << std::endl
    << "                   GSL           Boost           GSL           Boost   "
    << std::endl
    << " Value (x)        icdf           icdf           1-icdf         1-icdf "
    << std::endl
    << "_______________________________________________________________________"
    << std::endl;

  for (double prob = 0.05; prob < 1.0; prob += 0.05) {
    // 
    std::cout << std::fixed << std::setprecision(3)
              << std::setw(10) << std::right << prob;

    // Inverse normal cdf
    const double lInverseNormalCdfGSL =
      mean + gsl_cdf_gaussian_Pinv (prob, sigma);
    const double lInverseNormalCdfBoost =
      bm::quantile (normalDistribution, prob);

    // Complement of the inverse normal cdf
    const double lComplementInverseNormalCdfGSL =
      mean + gsl_cdf_gaussian_Qinv (prob, sigma);
    const double lComplementInverseNormalCdfBoost =
      bm::quantile (bm::complement (normalDistribution, prob));

    // Print values (quantiles)
    std::cout << std::fixed << std::setprecision(5)
              << std::setw(15) << std::right << lInverseNormalCdfGSL
              << std::setw(15) << std::right << lInverseNormalCdfBoost
              << std::setw(15) << std::right << lComplementInverseNormalCdfGSL
              << std::setw(15) << std::right << lComplementInverseNormalCdfBoost
              << std::endl;

    // Check that the GSL results are the same of those from Boost Math
    assert (bm::round (lInverseNormalCdfGSL / precision)
            == bm::round (lInverseNormalCdfBoost / precision));
    assert (bm::round (lComplementInverseNormalCdfGSL / precision)
            == bm::round (lComplementInverseNormalCdfBoost / precision));
  }
  
  //
  std::cout << std::endl;
  
  return 0;
}
