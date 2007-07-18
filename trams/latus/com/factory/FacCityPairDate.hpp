#ifndef __LATUS_COM_FAC_FACCITYPAIRDATE_HPP
#define __LATUS_COM_FAC_FACCITYPAIRDATE_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
// LATUS Common
#include <latus/com/factory/FacBomAbstract.hpp>
#include <latus/com/bom/CityPairDateList.hpp>

namespace LATUS {
  
  namespace COM {

    /** Forward declarations. */
    class CityPairDate;
    class ClassPath;
    
    /** Factory for CityPairDate objects. */
    class FacCityPairDate : public FacBomAbstract {
    public:
      /** Provide the unique instance.
          <br>The singleton is instantiated when first used
          @return FacCityPairDate& */
      static FacCityPairDate& instance();

      /** Destructor.
          <br>The Destruction put the _instance to NULL
          in order to be clean for the next FacCityPairDate::instance() */
      virtual ~FacCityPairDate();

      /** Create a new CityPairDate object.
          <br>This new object is added to the list of instantiated objects.
          @return CityPairDate& The newly created object. */
      CityPairDate& create (const boost::gregorian::date& iDepDate);

      /** Initialise the link between a CityPairDate and a ClassPath.
          @param CityPairDate&
          @param ClassPath&
          @exception FacExceptionNullPointer
          @exception FacException.*/
      static void initLinkWithClassPath (CityPairDate&, ClassPath&);

      /** Create a new ClassPath object with the given parameters.
          <br>This new object is added to the list of instantiated objects.
          <br>Any missing intermediary object (CityPairDate)
          will be created and added to the corresponding children list. */
      static void createClassPath (CityPairDate&,
                                   const std::string& iClassPathDescription,
                                   const double iDistributionMean,
                                   const double iDistributionStdDev);
      
    protected:
      /** Default Constructor.
          <br>This constructor is protected in order to ensure the singleton
          pattern.*/
      FacCityPairDate () {}

    private:
      /** The unique instance.*/
      static FacCityPairDate* _instance;
    };

  }
}
#endif // __LATUS_COM_FAC_FACCITYPAIRDATE_HPP
