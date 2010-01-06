// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// STDAIR
#include <stdair/STDAIR_Types.hpp>
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/basic/BasConst_Yield.hpp>
#include <stdair/basic/BasConst_Period_BOM.hpp>

namespace stdair {

  // ///////// General /////////
  /** Default very small value. */
  const double DEFAULT_EPSILON_VALUE = 0.0001; 
  
  /** Default flight speed (number of kilometers per hour). */
  const unsigned int DEFAULT_FLIGHT_SPEED = 900;

  /** Default number of generated flight dates . */
  const NbOfFlightDates_T DEFAULT_NB_OF_FLIGHTDATES = 0.0;

  
  //     // ///////// GSL /////////
  //     /** Default (GSL) random generator type. */
  //     const gsl_rng_type* DEFAULT_LATUS_RANDOM_GENERATOR_TYPE = gsl_rng_default;

  //     /** Default seed value for Exponential distribution. */
  //     const ExponentialSeed_T DEFAULT_EXPONENTIAL_SEED = 0;

  //     /** Default seed value for Exponential distribution. */
  //     const UniformSeed_T DEFAULT_UNIFORM_SEED = 0;

  //     // ///////// Labels in General Configuration Files /////////
  //     /** Default file path separator*/
  //      const std::string DEFAULT_CONFIG_FILEPATH_SEPARATOR = "/";

  //     /** Default label for RDS. */
  //     const std::string DEFAULT_CONFIG_RDS_LABEL = "rds";
  //     /** Default label for RDS file path. */
  //     const std::string DEFAULT_CONFIG_RDS_FILEPATH_LABEL = "rds_path";
  //     /** Default label for RDS Id (= folder holding RDS). */
  //     const std::string DEFAULT_CONFIG_RDS_ID_LABEL = "rds_id";
  //     /** Default label for RDS manifest. */
  //     const std::string DEFAULT_CONFIG_RDS_MANIFEST_LABEL = "rds_manifest";
  //     /** Default label for RDS airline configuration file name. */
  //     const std::string DEFAULT_CONFIG_RDS_AIRLINE_CONFIGURATION_LABEL =
  //       "airlineconfiguration";

  //     /** Default label for output files. */
  //     const std::string DEFAULT_CONFIG_OUTPUT_FILE_LABEL = "output_files";
  //     /** Default label for inventory output file name. */
  //     const std::string DEFAULT_CONFIG_INVENTORY_OUTPUT_FILE_LABEL =
  //       "inventory_output";
  //     /** Default label for simulation output file name. */
  //     const std::string DEFAULT_CONFIG_SIMULATION_OUTPUT_FILE_LABEL =
  //       "simulation_output";

  //     // ///////// Lables in RDS XML file /////////
  //     const std::string DEFAULT_CONFIG_RDS_DEMAND_ARRIVAL_FILENAME_LABEL =
  //       "demandpattern";
  //     const std::string DEFAULT_CONFIG_RDS_CANCEL_FILENAME_LABEL =
  //       "cancelratecurve"; 
  //     const std::string DEFAULT_CONFIG_RDS_CHARACTERISTIC_FILENAME_LABEL =
  //       "characteristics";
  //     const std::string DEFAULT_CONFIG_RDS_DEMAND_FILENAME_LABEL = "demands";
  //     const std::string DEFAULT_CONFIG_RDS_SCHEDULE_FILENAME_LABEL = "schedule";
  //     const std::string DEFAULT_CONFIG_RDS_FARE_FILENAME_LABEL = "fares";
  //     const std::string DEFAULT_CONFIG_RDS_YIELD_FILENAME_LABEL = "yields";
  //     const std::string DEFAULT_CONFIG_RDS_AU_RULES_FILENAME_LABEL = "aurules";
  //     const std::string DEFAULT_CONFIG_RDS_LFDTD_RULES_FILENAME_LABEL = "lfdtdrules";
  //     const std::string DEFAULT_CONFIG_RDS_DCP_FILENAME_LABEL =
  //       "datacollectionpoints";

  //     // ///////// BOOST Date-Time /////////
  //     // Time duration representing a full day
  //     // (i.e., 24h or 1,440 minutes or 86,400 seconds)

  //     /** Time duration representing a full day (in boost::time_duration unit).*/
  //     const Duration_T BOOST_TIME_DURATION_FOR_A_DAY =
  //       boost::posix_time::hours(24);

  //     /** Time duration representing a full day (in seconds).*/
  //     const int TIME_DURATION_FOR_A_DAY_IN_SECONDS =
  //     static_cast<const int> (BOOST_TIME_DURATION_FOR_A_DAY.total_seconds());

  //     /** Time duration representing a full hour (in seconds).*/
  //     const int TIME_DURATION_FOR_AN_HOUR_IN_SECONDS = 3600;

  //     /** Time duration representing a full minute (in seconds).*/
  //     const int TIME_DURATION_FOR_A_MINUTE_IN_SECONDS = 60;

  /** Null time duration (in boost::time_duration unit).*/
  const Duration_T NULL_BOOST_TIME_DURATION =
    boost::posix_time::hours(0)+ boost::posix_time::minutes (0)
    + boost::posix_time::seconds (0);

  //     /** Date duration representing a full day (in boost::date_duration unit).*/
  //     const DateOffSet_T BOOST_DATE_DURATION_FOR_A_DAY (1);

  //     /** Date duration representing the window of time used for statistical
  //         analysis. */
  //     const DateOffSet_T DEFAULT_ANALYSIS_TIME_WINDOW (180);

  //     /** Date duration representing the period of reservation for a
  //         typical flight. */
  //     const DateOffSet_T DEFAULT_RESERVATION_PERIOD_LENGTH (365);

  
  // //////// (Flight-)Period-related BOM ///////
  /** Default number of duration days. */
  const DayDuration_T DEFAULT_DAY_DURATION (0);
  
  /** Default date period (0-length, i.e., it lasts one day).*/
  const DatePeriod_T BOOST_DEFAULT_DATE_PERIOD (Date_T (2007, 1, 1),
                                                Date_T (2007, 1, 1));
  
  const std::string DOW_STR[] = {"Mon", "Tue", "Wed", "Thu", "Fri",
                                 "Sat", "Sun"};
  
  /** Default DOW String (e.g., "1111100"). */
  const DOW_String_T DEFAULT_DOW_STRING ("1111100");
  
  /** Default Date OffSet (e.g., 0). */
  const DateOffSet_T DEFAULT_DATE_OFFSET (0);
  
  //  // //////// General ///////
  //   /** Default update date for the General. */
  //   const Date_T DEFAULT_WORLD_SCHEDULE_UPDATE_DATE (2007,
  //                                                    boost::gregorian::Jan,
  //                                                    1);
  

  //     // //////// WholeDemand ///////
  //     /** Default update date for the WholeDemand. */
  //     const Date_T DEFAULT_WHOLE_DEMAND_UPDATE_DATE (2007,
  //                                                    boost::gregorian::Jan,
  //                                                    1);

  //     /** Default update date&time. */
  //     const DateTime_T DEFAULT_DEMAND_DATETIME (DEFAULT_WHOLE_DEMAND_UPDATE_DATE,
  //                                               NULL_BOOST_TIME_DURATION);

  // //////// Fare Rules ///////
  /** Default saturdayStay value (false). */
  const SaturdayStay_T DEFAULT_SATURDAY_STAY = false;
  
  /** Default change fees value (false). */
  const ChangeFees_T DEFAULT_CHANGE_FEES = false;
  
  /** Default non refundable value (false). */
  const NonRefundable_T DEFAULT_NON_REFUNDABLE = false;
  
  /** Default airlineCode value ('XX'). */
  const AirlineCode_T DEFAULT_AIRLINE_CODE = "XX";

  /** Default airlineCode value (''). */
  const AirlineCode_T DEFAULT_NULL_AIRLINE_CODE = "";

  /** Default airportCode value ('XXX'). */
  const AirportCode_T DEFAULT_AIRPORT_CODE = "XXX";

  /** Default family code value ('X'). */
  const ClassCode_T DEFAULT_FAMILY_CODE = "0";

  /** Default classCode value ('X'). */
  const ClassCode_T DEFAULT_CLASS_CODE = "X";

  /** Default number of airlines. */
  const NbOfAirlines_T DEFAULT_NBOFAIRLINES = 0;

  /** Default classCode value (''). */
  const ClassCode_T DEFAULT_NULL_CLASS_CODE = "";

  /** Default flightPathCode value (''). */
  const FlightPathCode_T DEFAULT_FLIGHTPATH_CODE = "";

  //     // //////// DemandFeatures ///////
  //     /** Default SaturdayStay average ratio of demand (value between [0, 100]). */
  //     const SaturdayStayRatio_T DEFAULT_SATURDAY_STAY_RATIO = 50;

  //     /** Default Change fees average ratio (value between [0, 100]). */
  //     const ChangeFeesRatio_T DEFAULT_CHANGE_FEES_RATIO = 50;

  //     /** Default Non refundable average ratio (value between [0, 100]). */
  //     const NonRefundableRatio_T DEFAULT_NON_REFUNDABLE_RATIO = 50;

  //     /** Default passenger type (Leisure or Business). */
  //     const PassengerType_T DEFAULT_PASSENGER_TYPE = "L";

  //     /** Default distribution pattern identifier. */
  //     const DistributionPatternId_T DEFAULT_DISTRIBUTION_PATTERN_ID = "";

  //     /** Default cancellation rate curve identifier. */
  //     const CancellationRateCurveId_T DEFAULT_CANCELLATION_RATE_CURVE_ID = "";

  //     /** Default airline preference identifier. */
  //     const AirlinePreferenceId_T DEFAULT_AIRLINE_PREFERENCE_ID = "";

  //     /** Default percentage pair of cancellation and no-show. */
  //     const CancellationNoShowRatePair_T DEFAULT_PERCENTAGE_PAIR (0.0, 0.0);

  //     /** Default characteristics pattern identifier. */
  //     const CharacteristicsPatternId_T DEFAULT_CHARACTERISTICS_PATTERN_ID = "";

  // //////// (Segment-)Class-related BOM ///////
  /** Default distance value (kilometers). */
  const Distance_T DEFAULT_DISTANCE_VALUE = 0;

  /** Default number of bookings (with counted cancellation)
      for BookingClass. */
  const NbOfBookings_T DEFAULT_CLASS_NB_OF_BOOKINGS = 0;

  /** Default number of booking (without cancellation)
      demands for BookingClass. */
  const NbOfBookings_T DEFAULT_CLASS_TOTAL_NB_OF_BOOKINGS = 0;

  /** Default unconstrained demand for BookingClass. */
  const NbOfBookings_T DEFAULT_CLASS_UNCONSTRAINED_DEMAND = 0;

  /** Default remaining future demand mean for BookingClass. */
  const NbOfBookings_T DEFAULT_CLASS_REMAINING_DEMAND_MEAN = 0;

  /** Default remaining futre demand standard deviation for BookingClass. */
  const NbOfBookings_T DEFAULT_CLASS_REMAINING_DEMAND_STANDARD_DEVIATION = 0;

  /** Default number of cancellations for BookingClass. */
  const NbOfCancellations_T DEFAULT_CLASS_NB_OF_CANCELLATIONS = 0;

  /** Default number of no-shows for BookingClass. */
  const NbOfNoShows_T DEFAULT_CLASS_NB_OF_NOSHOWS = 0;

  /** Default cabin capacity for Leg cabins. */
  const CabinCapacity_T DEFAULT_CABIN_CAPACITY = 0.0;

  /** Default commited space value for Leg cabins. */
  const CommitedSpace_T DEFAULT_COMMITED_SPACE = 0.0;

  /** Default commited space value for Leg cabins. */
  const BlockSpace_T DEFAULT_BLOCK_SPACE = 0.0;
    
  /** Default availability for BookingClass. */
  const Availability_T DEFAULT_CLASS_AVAILABILITY = 0.0;

  /** Default boolean for censorship flag given the status of
      availability for BookingClass. */
  const CensorshipFlag_T DEFAULT_CLASS_CENSORSHIPFLAG = false;

  /** Default list of censorship flag given the status of 
      availability for BookingClass. */
  const CensorshipFlagList_T DEFAULT_CLASS_CENSORSHIPFLAG_LIST = std::vector<CensorshipFlag_T>();

  /** Default booking limit value for BookingClass. */
  const BookingLimit_T DEFAULT_CLASS_BOOKING_LIMIT = 9999.0;

  /** Default authorization level for BookingClass. */
  const AuthorizationLevel_T DEFAULT_CLASS_AUTHORIZATION_LEVEL = 9999.0;

  /** Default MAX value of authorization level for BookingClass. */
  const AuthorizationLevel_T DEFAULT_CLASS_MAX_AUTHORIZATION_LEVEL = 9999.0;

  /** Default MIN value of authorization level for BookingClass. */
  const AuthorizationLevel_T DEFAULT_CLASS_MIN_AUTHORIZATION_LEVEL = 0.0;

  /** Default over-booking rate for BookingClass. */
  const OverbookingRate_T DEFAULT_CLASS_OVERBOOKING_RATE = 0.0;

  /** Default booking rate for OnD bookings over overall class bookings. */
  const BookingRatio_T DEFAULT_OND_BOOKING_RATE = 0.0;

  /** Default closed class code. */
  const ClassCode_T DEFAULT_CLOSED_CLASS_CODE = "CC";
    
  /** Default Fare value for BookingClass. */
  const Fare_T DEFAULT_CLASS_FARE_VALUE = 0.0;

  /** Default yield value for a virtual class. */
  const Yield_T DEFAULT_CLASS_YIELD_VALUE = 0.0;

  /** Default Revenue value. */
  const Revenue_T DEFAULT_REVENUE_VALUE = 0.0;

  /** Default load factor value (100%). */
  const Percentage_T DEFAULT_LOAD_FACTOR_VALUE = 100.0;

  // //////// (Leg-)YieldRange-related BOM ///////
  /** Default yield value. */
  const Yield_T DEFAULT_YIELD_VALUE = 0.0;

  /** Default yield max value. */
  const Yield_T DEFAULT_YIELD_MAX_VALUE = std::numeric_limits<double>::max();
    
  /** Default number of bookings for YieldRangeStruct_T. */
  const NbOfBookings_T DEFAULT_YIELD_NB_OF_BOOKINGS = 0.0;

  /** Default booking number. */
  const Identity_T DEFAULT_BOOKING_NUMBER = 0;

  /** Default cancellation number for YieldRangeStruct_T. */
  const NbOfCancellations_T DEFAULT_YIELD_NB_OF_CANCELLATIONS = 0.0;

  /** Default no-shows number for YieldRangeStruct_T. */
  const NbOfNoShows_T DEFAULT_YIELD_NB_OF_NOSHOWS = 0.0;

  /** Default availability for YieldRangeStruct_T. */
  const Availability_T DEFAULT_YIELD_AVAILABILITY = 0.0;

  /** Default boolean for booking limit availability for
      YieldRangeStruct_T. */
  const CensorshipFlag_T DEFAULT_YIELD_CENSORSHIPFLAG = false;
  
  /** Default booking limit value for YieldRangeStruct_T. */
  const BookingLimit_T DEFAULT_YIELD_BOOKING_LIMIT = 0.0;
  
  /** Default over-booking rate for YieldRangeStruct_T. */
  const OverbookingRate_T DEFAULT_YIELD_OVERBOOKING_RATE = 0.0;
  
  // //////// OnD-related BOM ///////
  /** Default value of Fare. */
  const Fare_T DEFAULT_OND_FARE_VALUE = 0.0;

  //     /** Default number of bookings. */
  //     const NbOfBookings_T DEFAULT_OND_NB_OF_BOOKINGS = 0.0;

  //     /** Default remaining future demand mean for OnD. */
  //     const NbOfBookings_T DEFAULT_OND_REMAINING_DEMAND_MEAN = 0.0;

  //     /** Default remaining futre demand standard deviation for OnD. */
  //     const NbOfBookings_T DEFAULT_OND_REMAINING_DEMAND_STANDARD_DEVIATION = 0.0;
    
      // //////// Travel Solutions ///////
      /** Default Minimum connection time. */
      const Duration_T DEFAULT_MINIMUM_CONNECTION_TIME (0, 30, 0);

      /** Default Matching Indicator value. */
      const MatchingIndicator_T DEFAULT_MATCHING_INDICATOR (0.0);

      /** Default price value (0.0). */
  //     const PriceValue_T DEFAULT_PRICE_VALUE (0.0);

      /** Default currency (euro). */
      const PriceCurrency_T DEFAULT_CURRENCY ("EUR");

      /** Default availability status for a travel solution. */
      const AvailabilityStatus_T DEFAULT_AVAILABILITY_STATUS = false;

  //     // //////// Cancellation ///////
  //     /** Default Fare value */
  //     const Fare_T DEFAULT_FARE_VALUE = 0.0;
    
  //     /** Default number of bookings. */
  //     const NbOfBookings_T DEFAULT_NB_OF_BOOKINGS = 0;

  //     /** Default date&time. */
  //     const DateTime_T DEFAULT_CANCELLATION_DATETIME
  //          (DEFAULT_WORLD_SCHEDULE_UPDATE_DATE,
  //           NULL_BOOST_TIME_DURATION);
    
  //     // //////// CityPair ////////
  //     /** Default booking date for BookingDay. */
  //     const Date_T DEFAULT_BOOKING_DATE (2007, boost::gregorian::Jan, 1);
    
  //     /** Default departure date for CityPairDate. */
  //     const Date_T DEFAULT_DEPARTURE_DATE (2008, boost::gregorian::Jan, 1);
    
  //     /** Date duration representing the time during which a flight-date is open
  //         to the reservation (in boost::date_duration unit).*/
  //     const DateOffSet_T DEFAULT_FLIGHT_DATE_RESERVATION_DURATION (365);

  //     /** Default number of seats required whenever a demand is processed into
  //         the simulator. */
  //     const unsigned short DEFAULT_NUMBER_OF_REQUIRED_SEATS = 1;

  //     // //////// Flight Period Actions ////////
  //     // //////// RMS mode  ///////
  //     /** Default forecaster mode. */
  //     const ForecasterMode_T DEFAULT_FORECAST_MODE = "NoForecast";

  //     /** First forecaster mode. */
  //     const ForecasterMode_T FIRST_FORECAST_MODE = "Forecaster1";

  //     /** Basic forecaster mode. */
  //     const ForecasterMode_T BASIC_FORECAST_MODE = "BasicForecaster";

  //     /** Neural forecaster mode. */
  //     const ForecasterMode_T NEURAL_FORECAST_MODE = "NeuralForecaster";

  //     /** Q forecaster mode. */
  //     const ForecasterMode_T Q_FORECAST_MODE = "QForecaster";

  //     /** Default optimizer mode. */
  //     const OptimizerMode_T DEFAULT_OPTIMIZER_MODE = "FCFS";

  //     /** Optimizer mode for rules like LF & DTD threshold. */
  //     const OptimizerMode_T LF_DTD_RULES_OPTIMIZER_MODE = "LFDTDRules";
    
  //     /** Optimizer mode for EMSR heuristic. */
  //     const OptimizerMode_T EMSR_OPTIMIZER_MODE = "EMSR";
    
  //     /** Optimizer mode for EMSR-a heuristic. */
  //     const OptimizerMode_T EMSRA_OPTIMIZER_MODE = "EMSRa";

  // //     /** Optimizer mode for EMSR-a with sell up probability. */
  // //     const OptimizerMode_T EMSRA_SELLUP_OPTIMIZER_MODE = "EMSRaSellup";

  //     /** Optimizer mode for EMSR-b heuristic. */
  //     const OptimizerMode_T EMSRB_OPTIMIZER_MODE = "EMSRb";

  //     /** Optimizer mode for Optimal Optimization by Monte-Carlo. */
  //     const OptimizerMode_T MC_OPTIMIZER_MODE = "MC";

  //     /** Optimizer mode for Leg-Based Iterative DAVN Optimization with
  //         Monte-Carlo. */
  //     const OptimizerMode_T LB_ITERATIVE_DAVN_OPTIMIZER_WITH_MC_MODE = "LB_DAVN_MC";

  //     /** Optimizer mode for Leg-Based Iterative DAVN Optimization with
  //         EMSR. */
  //     const OptimizerMode_T LB_ITERATIVE_DAVN_OPTIMIZER_WITH_EMSR_MODE = "LB_DAVN_EMSR";
    
  // //     /** No sell-up for optimizer by default*/
  // //     const SellupFlagForOptimizer_T DEFAULT_SELLUP_FLAG_FOR_OPTIMIZER = false;

  //     /** Defaut control mode. */
  //     const ControlMode_T DEFAULT_CONTROL_MODE = "STD";

  //     /** Theft control mode. */
  //     const ControlMode_T THEFT_CONTROL_MODE = "THEFT";

  //     /** Default number of draws for Monte-Carlo Integration method. */
  //     const int DEFAULT_NUMBER_OF_RANDOM_DRAWS = 1000;

  //      /** Default epsilon for convergence test. */
  //     const double DEFAULT_CONVERGENCE_EPSILON = 0.1;

  //     /** Default max number of iterations for Iterative DAVN. */
  //     const int DEFAULT_NB_OF_ITERATIONS_DAVN = 10;

  //     // //////// Characteristics  ///////
  //     /** Default k-factor (0.3).*/
  //     const Multiplier_T DEFAULT_KFACTOR = 0.3;
    
  //     /** Default basefare [used for computing WTP] (0).*/
  //     const Fare_T DEFAULT_BASEFARE = 0;
    
  //     /** Default elasticity multiplier [used for computing WTP] (1.5). */
  //     const Multiplier_T DEFAULT_EMULTIPLIER = 1.5;

  //     // //////// DICO mode  ///////
  //     /** Default DICO studied airline. */
  //     const AirlineCode_T DEFAULT_DICO_AIRLINE = "AD";
  //     //const AirlineCode_T DEFAULT_DICO_STUDIED_AIRLINE = "AA";

  //     /** Default second studied airline for DICO. */
  //     const AirlineCode_T DEFAULT_SECOND_DICO_AIRLINE = "AL";
  //     //const AirlineCode_T DEFAULT_SECOND_DICO_STUDIED_AIRLINE = "BA";

  //     /** Default DICO studied date. */
  //     const Date_T DEFAULT_DICO_STUDIED_DATE (2009, boost::gregorian::Jun, 29);
  //     //const Date_T DEFAULT_DICO_STUDIED_DATE (2009, boost::gregorian::Jun, 27);

  //     /** Default DICO optimiser (dico mode). */
  //     const DicoOptimizerMode_T DEFAULT_DICO_OPTIMIZER = "dico";

  //     /** Default DICO optimiser (robust dico mode). */
  //     const DicoOptimizerMode_T DEFAULT_ROBUST_DICO_OPTIMIZER =
  //       "robustdico";

  //     /** Default DICO optimiser (fast robust dico mode). */
  //     const DicoOptimizerMode_T DEFAULT_FAST_ROBUST_DICO_OPTIMIZER =
  //       "fastrobustdico";

  // //////// Inventory-related BOM ///////
  /** Default Bid-Price. */
  const BidPrice_T DEFAULT_BID_PRICE = 0.0;
  
  /** Default Bid-Price Vector. */
  const BidPriceVector_T DEFAULT_BID_PRICE_VECTOR = std::vector<BidPrice_T>();

  /** Maximum number of legs linked to a single flight-date.
      <br>Note that the number of derived segments is n*(n+1)/2 if n
      is the number of legs. */
  const unsigned short MAXIMUM_NUMBER_OF_LEGS_IN_FLIGHT = 7;
  
  /** Maximum number of segments linked to a single O&D
      (Origin & Destination). */
  const unsigned short MAXIMUM_NUMBER_OF_SEGMENTS_IN_OND = 3;

}
