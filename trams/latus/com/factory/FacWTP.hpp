#ifndef __LATUS_COM_FAC_FACWTP_HPP
#define __LATUS_COM_FAC_FACWTP_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>
#include <latus/com/bom/DistributionDetails.hpp>

namespace LATUS {

  namespace COM {

    // Forward declarations
    class WTP;
    
    /** Factory for WTP objects. */
    class FacWTP : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacWTP& */
      static FacWTP& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacWTP::instance() */
      virtual ~FacWTP();

      /** Create a new WTP object.
          <br>This new object is added to the list of instantiated objects.
          @return WTP& The newly created object. */
      WTP& create (const PriceValue_T& iWTPValue,
                   const PriceCurrency_T& iWTPCurrency,
                   const DistributionDetails_T&);

    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacWTP () {}

    private:
      /** The unique instance.*/
      static FacWTP* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACWTP_HPP
