#ifndef __LATUS_COM_FAC_FACCITYPAIR_HPP
#define __LATUS_COM_FAC_FACCITYPAIR_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>
#include <latus/com/bom/CityPairList.hpp>
#include <latus/com/bom/ClassPathDistributionList.hpp>
#include <latus/com/bom/DepDateDistributionList.hpp>

namespace LATUS {

  namespace COM {

    /** Forward declarations. */
    struct CityPairKey_T;
    class CityPair;
    class CityPairDate;
    
    /** Factory for CityPair objects. */
    class FacCityPair : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacCityPair& */
      static FacCityPair& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacCityPair::instance() */
      virtual ~FacCityPair();

      /** Create a new CityPair object.
          <br>This new object is added to the list of instantiated objects.
          @return CityPair& The newly created object. */
      CityPair& create (const CityPairKey_T&);

      /** Initialise the link between a CityPair and a CityPairDate.
          @param CityPair&
          @param CityPairDate&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithCityPairDate (CityPair&, CityPairDate&);

      /** Create a new ClassPath object with the given parameters.
          <br>This new object is added to the list of instantiated objects.
          <br>Any missing intermediary object (CityPair and/or CityPairDate)
          will be created and added to the corresponding children list. */
      static void createClassPath (CityPair&,
                                   const boost::gregorian::date& iDepDate,
                                   const std::string& iCabinCode,
                                   const std::string& iClassCode,
                                   const double iDistributionMean,
                                   const double iDistributionStdDev);
    
    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacCityPair () {}

    private:
      /** The unique instance.*/
      static FacCityPair* _instance;
    };
  }
}
#endif // __LATUS_COM_FAC_FACCITYPAIR_HPP
