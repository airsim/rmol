// C
#include <assert.h>
// STL
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
// Boost (Extended STL)
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
// GSL Random Number Generation (GSL Reference Manual, version 1.7, Chapter 17)
#include <gsl/gsl_rng.h>
// GSL Random Number Distributions (GSL Reference Manual, version 1.7,
// Chapter 19)
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
// LATUS
#include <latus/LATUS_Service.hpp>

// Random Generator Type
const gsl_rng_type* _rngTypePtr = NULL;

// Random Generator
gsl_rng* _rngPoissonPtr = NULL;
gsl_rng* _rngGaussianPtr = NULL;

// ///////////////////////////////////////////////////
void init () {
  // Random Generator type
  _rngTypePtr = gsl_rng_default;

  // Initialise the Random Generator
  gsl_rng_env_setup ();

  // Allocate the memory for the random generator
  _rngPoissonPtr = gsl_rng_alloc (_rngTypePtr);
  _rngGaussianPtr = gsl_rng_alloc (_rngTypePtr);
}

// ///////////////////////////////////////////////////
double generatePoissonVariate (const double iMu) {
  const double result = gsl_ran_poisson (_rngPoissonPtr, iMu);
  return result;
}

// ///////////////////////////////////////////////////
double generateGaussianVariate (const double iMean, const double iStdDev) {
  const double result = iMean + gsl_ran_gaussian (_rngGaussianPtr, iStdDev);
  return result;
}

// ///////////////////////////////////////////////////
void finalise () {
  gsl_rng_free (_rngPoissonPtr);
  gsl_rng_free (_rngGaussianPtr);
}


// ///////////////////////////////////////////////////
// Time duration representing a full day
// (i.e., 24h or 1,440 minutes or 86,400 seconds)
const boost::posix_time::time_duration kDay = boost::posix_time::hours(24);
const int kDayInSeconds = static_cast<const int> (kDay.total_seconds());
const boost::gregorian::date_duration kDayDuration (1);
    

// ///////////////////////////////////////////////////
typedef std::map<std::string, double> ClassPathDistributionList_T;
typedef std::map<boost::gregorian::date, 
		 ClassPathDistributionList_T> DepDateDistributionList_T;

// ///////////////////////////////////////////////////
class CityPair {
public:
  // //////////////////////
  CityPair (const std::string& iDescription, 
	    const boost::gregorian::date& iStartDate,
	    const boost::gregorian::date& iEndDate) 
    : _description (iDescription), _currentTime (0, 0, 0, 0), 
      _totalFinalDemand (0.0), _dailyRate (0.0), _dailyEventNumber (0),
      _startDate (iStartDate), _endDate (iEndDate) {
    _rngExponentialPtr = gsl_rng_alloc (_rngTypePtr);
  }
  ~CityPair () {
    gsl_rng_free (_rngExponentialPtr);
  }

  // //////////////////////
  const std::string& getDescription() const {
    return _description;
  }

  // //////////////////////
  DepDateDistributionList_T& getDepDateDistributionList () {
    return _depDateDistributionList;
  }

  // //////////////////////
  const boost::posix_time::time_duration& getCurrentTime () const {
    return _currentTime;
  }

  // //////////////////////
  void init() {
    // Update the total final demand
    for (DepDateDistributionList_T::const_iterator itClassPathDistrib =
	   _depDateDistributionList.begin();
	 itClassPathDistrib != _depDateDistributionList.end(); 
	 itClassPathDistrib++) {
      const boost::gregorian::date& lDepDate = itClassPathDistrib->first;

      const ClassPathDistributionList_T& lClassPathDistributionList =
	itClassPathDistrib->second;
      
      for (ClassPathDistributionList_T::const_iterator itDistributionDetails=
	     lClassPathDistributionList.begin();
	   itDistributionDetails != lClassPathDistributionList.end();
	   itDistributionDetails++) {
	const std::string& lClassPath = itDistributionDetails->first;
	const double& lDistributionDetails = itDistributionDetails->second;
	_totalFinalDemand += lDistributionDetails;
      }
    }
  }

  // //////////////////////
  void setCurrentTime (const boost::posix_time::time_duration& iCurrentTime) {
    _currentTime = iCurrentTime;
  }

  // //////////////////////
  void resetForCurrentDate (const boost::gregorian::date iCurrentDate) {
    // Reset the current time to midnight
    setCurrentTime (boost::posix_time::time_duration (0, 0, 0, 0));

    // Reset the daily number of events
    _dailyEventNumber = 0;

    // Re-calculate the daily rate (final demand weighted by a modulation,
    // e.g., here, according to a Weibull distribution).
    updateDailyRate (iCurrentDate);

    // Generate the next event
    addEvent ();
  }

  // //////////////////////
  double generateExponentialVariate (const double iLambda) {
    const double lMu = 1/iLambda;
    const double result = gsl_ran_exponential (_rngExponentialPtr, lMu);
    return result;
  }

  // //////////////////////
  void addEvent () {
    // Generate a random variate, expressed in (fractional) day
    const double lExponentialVariateInDays =
      generateExponentialVariate (_dailyRate);

    // Convert the variate in a number of seconds
    const int lExponentialVariateInSeconds =
      static_cast<const int> (lExponentialVariateInDays * kDayInSeconds);
	
    // Convert the variate in a (Boost typedef) time duration
    const boost::posix_time::time_duration lExponentialVariate =
      boost::posix_time::seconds (lExponentialVariateInSeconds);
	
    // Add the inter-arrival time to the current time
    _currentTime += lExponentialVariate;

    // Add an event
    if (_currentTime <= kDay) {
      _dailyEventNumber++;
    }
  }

  // //////////////////////
  void updateDailyRate (const boost::gregorian::date iCurrentDate) {

    /**
       Note that the following method of pro-rating the daily rate, from
       the final annual demand, may appear cumbersome, as:
       1. We discretise a continuous distribution, just to get a typical
       S-curve booking pattern.
       2. We normalise that distribution, so as to get the corresponding
       cdf (cumulative distribution function) equal to 1 on [0, infinite[.
       3. Moreover, in reality, we should first fit the parameters of that
       S-curve distribution with the corresponding observations.
          
       Therefore, in the final version, we'll certainly use directly the
       discrete distributions corresponding to the observations (historical
       date) made beforehand. But as those observations may be difficult
       to obtain, the following method is just handy for now.
    */

    /**
       The result is the daily rate, expressed as a number of events (per day).
       (lambda => mu = 1/ lambda), e.g., lambda = 10 => mu = 0.1 (= 2.4h,
       i.e., in average, an event occurs every 2.4h).
    */
    _dailyRate = 0.0;

    // The first day open to reservation, there is no reservation:
    // _dailyRate = 0.0
    if (_startDate == iCurrentDate) {
      return;
    }
  
    // Simulation length-time (expressed as a number of days)
    const boost::gregorian::date_duration lSimulationLength =
      _endDate - _startDate;
    const int lSimulationLengthInDays =
      static_cast<const int> (lSimulationLength.days());

    // DEBUG
    // return (_totalFinalDemand / lSimulationLengthInDays);
  
    // Current length-time (expressed as a number of days)
    const boost::gregorian::date_duration lCurrentDuration =
      iCurrentDate - _startDate;
    const double lCurrentDurationInDays =
      static_cast<const double> (lCurrentDuration.days());
  
    /** Ratio on the x-absciss for the Weibull distribution
	(GSL, Chapter 19, p209 on GSL Reference Manual for GSL v1.7). */
    const double lXRatio = 2.0 / lSimulationLengthInDays;

    /** The daily rate is pro-rated/weighted according to the
	Weibull distribution (see above for the reference in the GSL).
	The a and b parameters are taken equal to respectively 2 and 3. */
    const double lCurrentDurationInWeibullX = lCurrentDurationInDays * lXRatio;
    const double lPreviousDurationInWeibullX =
      (lCurrentDurationInDays - 1.0) * lXRatio;

    /**
       There's also a normalisation factor, so as the CDF be equal
       to one when x is equal to lSimulationLengthInDays.
       Hence, we're looking for a normalisation constant (let's name it nc)
       such as: f_pdf (x) = nc . Weibull_pdf (lXRatio . x).
       We get:
       nc = lXRatio / Weibull_cdf (lXRatio . lSimulationLengthInDays), and:
       f_cdf (x) = Weibull_cdf (lXRatio . x)
       / Weibull_cdf (lXRatio . lSimulationLengthInDays).
    */
    const double lSimulationLengthInWeibullX = 
      lSimulationLengthInDays * lXRatio;
    const double lNormalisationConstant =
      1 / gsl_cdf_weibull_P (lSimulationLengthInWeibullX, 2, 3);
  
    const double lDailyIncrementalRate = lNormalisationConstant
      * (gsl_cdf_weibull_P (lCurrentDurationInWeibullX, 2, 3)
	 - gsl_cdf_weibull_P (lPreviousDurationInWeibullX, 2, 3));

    _dailyRate = _totalFinalDemand * lDailyIncrementalRate;
  }

  // //////////////////////
  void display() const {
    std::cout << _description << "; ";

    int j = 1;
    for (DepDateDistributionList_T::const_iterator itClassPathDistrib =
	   _depDateDistributionList.begin();
	 itClassPathDistrib != _depDateDistributionList.end(); 
	 itClassPathDistrib++, j++) {
      const boost::gregorian::date& lDepDate = itClassPathDistrib->first;
      if (j != 1) {
	std::cout << "         ";
      }
      std::cout << lDepDate << "; ";

      const ClassPathDistributionList_T& lClassPathDistributionList =
	itClassPathDistrib->second;
      
      int k = 1;
      for (ClassPathDistributionList_T::const_iterator itDistributionDetails=
	     lClassPathDistributionList.begin();
	   itDistributionDetails != lClassPathDistributionList.end();
	   itDistributionDetails++, k++) {
	const std::string& lClassPath = itDistributionDetails->first;
	if (k != 1) {
	  std::cout << "                      ";
	}
	std::cout << lClassPath << "; ";
	const double& lDistributionDetails = itDistributionDetails->second;
	std::cout << lDistributionDetails << "; " << std::endl;
      }
    }

    // Summary
    std::cout << _description << "; Total final demand: " << _totalFinalDemand
	      << std::endl;
  }

  // //////////////////////
  void displayCurrent() const {
    std::cout << _description << "; Daily Rate: " 
	      << std::fixed << std::setprecision(2) << _dailyRate
	      << "; Current Time: " << _currentTime 
	      << "; Daily Nb of Events: " << _dailyEventNumber
	      << std::endl;
  }

private:
  // //////////////////////
  CityPair() {}
  CityPair(const CityPair&) {}

private:
  // //////////////////////
  const std::string _description;
  DepDateDistributionList_T _depDateDistributionList;
  const boost::gregorian::date _startDate;
  const boost::gregorian::date _endDate;
  boost::posix_time::time_duration _currentTime;
  double _totalFinalDemand;
  double _dailyRate;
  int _dailyEventNumber;
  gsl_rng* _rngExponentialPtr;
};

// ///////////////////////////////////////////////////
typedef std::map<std::string, CityPair*> CityPairList_T;
typedef std::map<boost::posix_time::time_duration, CityPair*> EventList_T;

// ///////////////////////////////////////////////////
class CityPairList {
public:
  // //////////////////////
  CityPairList (const boost::gregorian::date& iStartDate,
		const boost::gregorian::date& iEndDate) 
    : _startDate (iStartDate), _endDate (iEndDate) {}
  ~CityPairList () {}

  // //////////////////////
  static double& 
  getDistributionDetailsInstance (const std::string& iClassPath,
				  ClassPathDistributionList_T& ioClassPathDistributionList) {
    ClassPathDistributionList_T::iterator itDistributionDetails =
      ioClassPathDistributionList.find (iClassPath);
    if (itDistributionDetails == ioClassPathDistributionList.end()) {
      double aDistributionDetails = 0.0;
      const bool insertSucceeded = ioClassPathDistributionList.
	insert (ClassPathDistributionList_T::
		value_type (iClassPath, 
			    aDistributionDetails)).second;
      if (insertSucceeded == false) {
	std::cerr << "Insertion failed for " << iClassPath << std::endl;
	assert (insertSucceeded == true);
      }

      ClassPathDistributionList_T::iterator itDistributionDetails =
	ioClassPathDistributionList.find (iClassPath);
      assert (itDistributionDetails != ioClassPathDistributionList.end());

      double& resultDistributionDetails = itDistributionDetails->second;
      return resultDistributionDetails;

    } else {
      double& resultDistributionDetails = itDistributionDetails->second;
      return resultDistributionDetails;
    }
  }

  // //////////////////////
  static ClassPathDistributionList_T& 
  getClassPathDistributionListInstance (const boost::gregorian::date& iDepDate,
					DepDateDistributionList_T& ioDepDateDistributionList) {
    DepDateDistributionList_T::iterator itClassPathDistrib =
      ioDepDateDistributionList.find (iDepDate);
    if (itClassPathDistrib == ioDepDateDistributionList.end()) {
      ClassPathDistributionList_T aClassPathDistributionList;
      const bool insertSucceeded = 
	ioDepDateDistributionList.insert (DepDateDistributionList_T::
					  value_type (iDepDate, 
						      aClassPathDistributionList)).second;
      if (insertSucceeded == false) {
	std::cerr << "Insertion failed for " << iDepDate << std::endl;
	assert (insertSucceeded == true);
      }

      DepDateDistributionList_T::iterator itClassPathDistrib =
	ioDepDateDistributionList.find (iDepDate);
      assert (itClassPathDistrib != ioDepDateDistributionList.end());

      ClassPathDistributionList_T& resultClassPathDistributionList =
	itClassPathDistrib->second;
      return resultClassPathDistributionList;

    } else {
      ClassPathDistributionList_T& resultClassPathDistributionList =
	itClassPathDistrib->second;
      return resultClassPathDistributionList;
    }
  }

  // //////////////////////
  CityPair&
  getCityPairInstance (const std::string& iCityPair) {
    CityPairList_T::iterator itDepDateDistrib = _cityPairList.find (iCityPair);
    if (itDepDateDistrib == _cityPairList.end()) {
      CityPair* aCityPair_ptr = new CityPair (iCityPair, _startDate, _endDate);
      assert (aCityPair_ptr != NULL);

      const bool insertSucceeded = 
	_cityPairList.insert (CityPairList_T::
			       value_type (iCityPair, 
					   aCityPair_ptr)).second;
      if (insertSucceeded == false) {
	std::cerr << "Insertion failed for " << iCityPair << std::endl;
	assert (insertSucceeded == true);
      }

      itDepDateDistrib = _cityPairList.find (iCityPair);
      assert (itDepDateDistrib != _cityPairList.end());
    }

    CityPair* resultCityPair_ptr = itDepDateDistrib->second;
    assert (resultCityPair_ptr != NULL);

    return (*resultCityPair_ptr);
  }

  // //////////////////////
  bool readAndProcessInputFile (const std::string& iInputFileName) {

    // Open the input file
    std::ifstream inputFile (iInputFileName.c_str());
    if (! inputFile) {
      return false;
    }
    
    char buffer[80];
    double dval = 0.0;
    std::string dvalStr;
    short i = 1;
    bool hasAllPArams = true;

    std::string aCityPairStr;
    std::string aClassPath;
    boost::gregorian::date aDepDate;
    double aMean = 0.0;
    
    while (inputFile.getline (buffer, sizeof (buffer), ';')) {
      std::istringstream iStringStr (buffer);

      bool hasRead = false;

      if (i == 1) {
	hasAllPArams = true;
      }

      if (i == 1 || i == 2 || i == 3) {
	hasRead = (iStringStr >> dvalStr);
      }

      if (i == 4) {
	hasRead = (iStringStr >> dval);
      }
      
      if (hasRead) {
	if (i == 1) {
	  aCityPairStr = dvalStr;
	  // std::cout << "City Pair = '" << aCityPairStr << "'" << std::endl;

	} else if (i == 2) {
	  aDepDate = boost::gregorian::from_simple_string (dvalStr);
	  // std::cout << "Date = '" << aDepDate << "'" << std::endl;

	} else if (i == 3) {
	  aClassPath = dvalStr;
	  // std::cout << "Class Path = '" << aClassPath << "'" << std::endl;

	} else if (i == 4) {
	  aMean = dval;
	  // std::cout << "Mean = '" << aMean << "'" << std::endl;

	  CityPair& aCityPair = getCityPairInstance (aCityPairStr);

	  DepDateDistributionList_T& aDepDateDistributionList = 
	    aCityPair.getDepDateDistributionList();

	  ClassPathDistributionList_T& aClassPathDistributionList =
	    CityPairList::getClassPathDistributionListInstance (aDepDate,
								aDepDateDistributionList);

	  double& aDistributionDetails =
	    CityPairList::getDistributionDetailsInstance (aClassPath,
							  aClassPathDistributionList);

	  aDistributionDetails = aMean;

	  i = 0;
	}
	i++;
          
      } else {
	hasAllPArams = false;
      }

    }
    
    if (!inputFile.eof()) {
      std::cerr << "Problem when reading input file \"" << iInputFileName
		<< "\"" << std::endl;
    }

    return true;
  }

  // //////////////////////
  void init () {
    for (CityPairList_T::const_iterator itCityPair = _cityPairList.begin();
	 itCityPair != _cityPairList.end(); itCityPair++) {
      CityPair* lCityPair_ptr = itCityPair->second;
      assert (lCityPair_ptr != NULL);
      lCityPair_ptr->init();
    }
  }

  // //////////////////////
  void display () const {
    for (CityPairList_T::const_iterator itCityPair = _cityPairList.begin();
	 itCityPair != _cityPairList.end(); itCityPair++) {
      CityPair* lCityPair_ptr = itCityPair->second;
      assert (lCityPair_ptr != NULL);

      lCityPair_ptr->display();
    }
  }

  // //////////////////////
  void generateEventsForAllCityPairs (const boost::gregorian::date& iCurrentDate,
				      EventList_T& ioEventList) {
    for (CityPairList_T::const_iterator itCityPair = _cityPairList.begin();
	 itCityPair != _cityPairList.end(); itCityPair++) {
      CityPair* lCityPair_ptr = itCityPair->second;
      assert (lCityPair_ptr != NULL);

      // * Reset the current time to midnight.
      // * Re-calculate the daily booking rate (final demand modulated by a
      //   given distribution, e.g., Weibull).
      // * Calculate the time of the next event
      lCityPair_ptr->resetForCurrentDate (iCurrentDate);

      // Initialise the map of next event times
      const boost::posix_time::time_duration& lCityPairCurrentTime =
	lCityPair_ptr->getCurrentTime();
      const bool insertSucceeded =
	ioEventList.insert (EventList_T::value_type (lCityPairCurrentTime,
						     lCityPair_ptr)).second;
      if (insertSucceeded == false) {
	// The event time may already exist in the list
	EventList_T::const_iterator itEvent = 
	  ioEventList.find (lCityPairCurrentTime);
	assert (itEvent != ioEventList.end());
	
	// Add one second to the current event, so that there's no overlap
	const boost::posix_time::time_duration lCityPairAlteredCurrentTime =
	  lCityPairCurrentTime + boost::posix_time::seconds(1);
	lCityPair_ptr->setCurrentTime (lCityPairAlteredCurrentTime);
	const bool insertAlterSucceeded = ioEventList.
	  insert (EventList_T::value_type (lCityPairAlteredCurrentTime,
					   lCityPair_ptr)).second;
	if (insertAlterSucceeded == false) {
	  std::cerr << "Insertion failed for " << lCityPairAlteredCurrentTime
		    << " and " << lCityPair_ptr->getDescription() << std::endl;
	  assert (insertAlterSucceeded == true);
	}
      }
    }
  }

  // //////////////////////
  void addEvent (CityPair& ioCityPair, EventList_T& ioEventList) {
    // Current time
    const boost::posix_time::time_duration& lCityPairCurrentTime =
      ioCityPair.getCurrentTime();

    // Remove the current event from the event list
    const int removedNb = ioEventList.erase (lCityPairCurrentTime);
    if (removedNb != 1) {
      // DEBUG
      std::cout << "WARNING: removed " << removedNb
		<< " for the current time " << lCityPairCurrentTime
		<< " (for " << ioCityPair.getDescription()
		<< ") can not be found in the event list. Event List: " 
		<< std::endl;
      int j = 1;
      for (EventList_T::const_iterator itEvent = ioEventList.begin();
	   itEvent != ioEventList.end(); itEvent++, j++) {
	const CityPair* lCityPair_ptr = itEvent->second;
	std::cout << "[" << j << "]; " << lCityPair_ptr->getDescription() 
		  << "; time: " << itEvent->first << std::endl;
      }
      return;
    }

    // Generate the next event for that city pair
    ioCityPair.addEvent();

    // Add that new event to the event list
    const boost::posix_time::time_duration& lCityPairNewCurrentTime = 
      ioCityPair.getCurrentTime();
    const bool insertSucceeded =
      ioEventList.insert (EventList_T::value_type (lCityPairNewCurrentTime,
						   &ioCityPair)).second;
    if (insertSucceeded == false) {
      std::cerr << "Insertion failed for " << lCityPairNewCurrentTime
		<< " and " << ioCityPair.getDescription() << std::endl;
      assert (insertSucceeded == true);
    }
  }

  // //////////////////////
  void simulate () {

    // Initialise the city pair objects
    init();

    // Re-initialisaton of the current date (of the simulation)
    boost::gregorian::date lCurrentDate = _startDate;

    // Total number of events generated for the simulation
    int lTotalEventNumber = 0;

    while (lCurrentDate < _endDate) {

      EventList_T lEventList;
      // Generate the list of next events, one for each city pair
      generateEventsForAllCityPairs (lCurrentDate, lEventList);

      // Start the simulation day corresponding to the booking date
      boost::posix_time::time_duration lCurrentTime (0, 0, 0, 0);

      // Current number of events
      int lTotalDailyEventNumber = 0;

      // Repeat until the current time exceeds 24h (i.e., 86,400 seconds)
      while (lCurrentTime <= kDay) {
	// Dequeue the next event from the event list
	EventList_T::const_iterator itNextEventCityPair = lEventList.begin();
	if (itNextEventCityPair == lEventList.end()) {
	  std::cout << "No more city pair..." << std::endl;
	  break;
	}

	CityPair* lCityPair_ptr = itNextEventCityPair->second;
	assert (lCityPair_ptr != NULL);

	// Update the current time
	lCurrentTime = lCityPair_ptr->getCurrentTime();

	// Add an event
	if (lCurrentTime <= kDay) {
	  lTotalDailyEventNumber++; lTotalEventNumber++;
	  addEvent (*lCityPair_ptr, lEventList);

	  // DEBUG
	  // lCityPair_ptr->displayCurrent();
	}
      }

      // DEBUG
      /**
      if (lTotalDailyEventNumber != 0) {
	std::cout << "Current date: " << lCurrentDate 
		  << "; Total Daily Nb of Events: " << lTotalDailyEventNumber
		  << "; Total Nb of Events: " << lTotalEventNumber
		  << std::endl;
      }
      */

      // Add a day
      lCurrentDate += kDayDuration;
    }
  }

private:
  // //////////////////////
  CityPairList () {}
  CityPairList (const CityPairList&) {}

private:
  // //////////////////////
  CityPairList_T _cityPairList;
  const boost::gregorian::date _startDate;
  const boost::gregorian::date _endDate;
};

// /////////////// M A I N /////////////////
int main (int argc, char* argv[]) {
  try {
    
    // Simulation length (time length) / date range for the simulation
    const boost::gregorian::date kStartDate (2007, boost::gregorian::Jan, 1);
    const boost::gregorian::date kEndDate (2008, boost::gregorian::Jan, 1);
    
    // Length of the Simulation (number of runs)
    int K = 2;

    // Input O&D Demand File
    std::string lFilename ("demand.csv");

    // Read the command-line parameters
    if (argc >= 1 && argv[1] != NULL) {
      std::istringstream istr (argv[1]);
      istr >> K;
    }

    if (argc >= 2 && argv[2] != NULL) {
      std::istringstream istr (argv[2]);
      istr >> lFilename;
    }

    // Initialisation of random generators
    init();

    std::cout << "Simulation#; Lambda_Sum; Total_Event#; Gaussian_Variate; "
              << std::endl;
    
    // 
    CityPairList aCityPairList (kStartDate, kEndDate);
    const bool hasFileBeenRead = 
      aCityPairList.readAndProcessInputFile (lFilename);
    if (hasFileBeenRead == false) {
      std::cerr << "Can not parse the \"" << lFilename 
		<< "\" file (hint: check that it exists)." << std::endl;
      return -1;
    }

    // Perform K simulations    
    for (int i=0; i != K; i++) {
      aCityPairList.simulate();
      aCityPairList.display();
    }

    // Cleaning of random generators
    finalise();
    
    // Initialise the context
    //LATUS::LATUS_Service latusService;

    // Launch a simulation
    //latusService.simulate ();

    
  } catch (const std::exception& stde) {
    std::cerr << "Standard exception: " << stde.what() << std::endl;
    return -1;
    
  } catch (...) {
    return -1;
  }
  
  return 0;
}
