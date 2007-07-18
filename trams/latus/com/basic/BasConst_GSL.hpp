#ifndef __LATUS_COM_BAS_BASCONST_GSL_HPP
#define __LATUS_COM_BAS_BASCONST_GSL_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// GSL Random Number Generation (GSL Reference Manual, version 1.7, Chapter 17)
#include <gsl/gsl_rng.h>

namespace LATUS {

  namespace COM {
    
    /** Default (GSL) random generator type. */
    extern const gsl_rng_type* DEFAULT_LATUS_RANDOM_GENERATOR_TYPE;
    
  }
}
#endif // __LATUS_COM_BAS_BASCONST_GSL_HPP
