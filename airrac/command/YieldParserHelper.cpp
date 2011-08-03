// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <cassert>
#include <fstream>
#include <vector>
// StdAir
#include <stdair/basic/BasFileMgr.hpp>
#include <stdair/basic/BasConst_Request.hpp>
#include <stdair/bom/BomRoot.hpp>
#include <stdair/service/Logger.hpp>
// Airrac
#include <airrac/command/YieldParserHelper.hpp>
#include <airrac/command/YieldRuleGenerator.hpp>

namespace AIRRAC {

  namespace YieldParserHelper {

    // //////////////////////////////////////////////////////////////////
    //  Semantic actions
    // //////////////////////////////////////////////////////////////////

    ParserSemanticAction::
    ParserSemanticAction (YieldRuleStruct& ioYieldRule)
      : _yieldRule (ioYieldRule) {
    }      
   
    // //////////////////////////////////////////////////////////////////
    storeYieldId::
    storeYieldId (YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeYieldId::operator() (unsigned int iYieldId,
                                   boost::spirit::qi::unused_type,
                                   boost::spirit::qi::unused_type) const {
      _yieldRule.setYieldID (iYieldId);
      
      // DEBUG
      //STDAIR_LOG_DEBUG ( "Yield Id: " << _yieldRule.getYieldID ());

      const stdair::AirlineCode_T lEmptyAirlineCode ("");
      _yieldRule.setAirlineCode(lEmptyAirlineCode);
      _yieldRule.clearAirlineCodeList();
      const stdair::ClassCode_T lEmptyClassCode ("");
      _yieldRule.setClassCode(lEmptyClassCode);
      _yieldRule.clearClassCodeList();
      _yieldRule._itSeconds = 0; 

    }
    
    // //////////////////////////////////////////////////////////////////
    storeOrigin ::
    storeOrigin (YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeOrigin::operator() (std::vector<char> iChar,
                                  boost::spirit::qi::unused_type,
                                  boost::spirit::qi::unused_type) const {
       const stdair::AirportCode_T lOrigin (iChar.begin(), iChar.end());
       _yieldRule.setOrigin (lOrigin);
       // DEBUG
       //STDAIR_LOG_DEBUG ( "Origin: " << _yieldRule.getOrigin ());
    }

    // //////////////////////////////////////////////////////////////////
    storeDestination ::
    storeDestination (YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeDestination::operator() (std::vector<char> iChar,
                                       boost::spirit::qi::unused_type,
                                       boost::spirit::qi::unused_type) const {
       const stdair::AirportCode_T lDestination (iChar.begin(), iChar.end());
       _yieldRule.setDestination (lDestination);
       // DEBUG
       //STDAIR_LOG_DEBUG ( "Destination: " << _yieldRule.getDestination ());
    }

    // //////////////////////////////////////////////////////////////////
    storeTripType ::
    storeTripType (YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeTripType::operator() (std::vector<char> iChar,
                                    boost::spirit::qi::unused_type,
                                    boost::spirit::qi::unused_type) const {
      const stdair::TripType_T lTripType (iChar.begin(), iChar.end());
      if (lTripType == "OW" || lTripType == "RT") {
         _yieldRule.setTripType (lTripType);
      } else {
        // ERROR
        STDAIR_LOG_ERROR ("Invalid trip type  " << lTripType);
      }                       
      // DEBUG
      //STDAIR_LOG_DEBUG ("TripType: " << _yieldRule.getTripType ());
    }

    
    // //////////////////////////////////////////////////////////////////
    storeDateRangeStart::
    storeDateRangeStart (YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeDateRangeStart::operator() (boost::spirit::qi::unused_type,
                                          boost::spirit::qi::unused_type,
                                          boost::spirit::qi::unused_type) const {
      const stdair::Date_T& lDateStart = _yieldRule.calculateDate ();
      _yieldRule.setDateRangeStart (lDateStart);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Date Range Start: "<< _yieldRule.getDateRangeStart ());
    }

    // //////////////////////////////////////////////////////////////////
    storeDateRangeEnd::
    storeDateRangeEnd(YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeDateRangeEnd::operator() (boost::spirit::qi::unused_type,
                                        boost::spirit::qi::unused_type,
                                        boost::spirit::qi::unused_type) const {
      const stdair::Date_T& lDateEnd = _yieldRule.calculateDate ();
      // As a Boost date period (DatePeriod_T) defines the last day of
      // the period to be end-date - one day, we have to add one day to that
      // end date before.
      const stdair::DateOffset_T oneDay (1);
      const stdair::Date_T lBoostDateEnd = lDateEnd + oneDay;
      _yieldRule.setDateRangeEnd (lBoostDateEnd);
       // DEBUG
       //STDAIR_LOG_DEBUG ("Date Range End: " << _yieldRule.getDateRangeEnd ());
    }

    // //////////////////////////////////////////////////////////////////
    storeStartRangeTime::
    storeStartRangeTime (YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeStartRangeTime::operator() (boost::spirit::qi::unused_type,
                                          boost::spirit::qi::unused_type,
                                          boost::spirit::qi::unused_type) const {
      const stdair::Duration_T& lTimeStart = _yieldRule.calculateTime ();
      _yieldRule.setTimeRangeStart (lTimeStart);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Time Range Start: " << _yieldRule.getTimeRangeStart ());
      // Reset the number of seconds
      _yieldRule._itSeconds = 0;
    }

    // //////////////////////////////////////////////////////////////////
    storeEndRangeTime::
    storeEndRangeTime (YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeEndRangeTime::operator() (boost::spirit::qi::unused_type,
                                        boost::spirit::qi::unused_type,
                                        boost::spirit::qi::unused_type) const {
      const stdair::Duration_T& lTimeEnd = _yieldRule.calculateTime ();
      _yieldRule.setTimeRangeEnd (lTimeEnd);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Time Range End: " << _yieldRule.getTimeRangeEnd ());
      // Reset the number of seconds
      _yieldRule._itSeconds = 0;
    }

    // //////////////////////////////////////////////////////////////////
    storePOS ::
    storePOS (YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storePOS::operator() (std::vector<char> iChar,
                               boost::spirit::qi::unused_type,
                               boost::spirit::qi::unused_type) const {
      const stdair::CityCode_T lPOS (iChar.begin(), iChar.end());
      if (lPOS == _yieldRule.getOrigin() || lPOS == _yieldRule.getDestination() ) {
        _yieldRule.setPOS (lPOS);
      } else if (lPOS == "ROW") {
        const stdair::CityCode_T lPOSROW ("ROW");
        _yieldRule.setPOS (lPOSROW);
      } else if (lPOS == stdair::DEFAULT_POS) {
        _yieldRule.setPOS (stdair::DEFAULT_POS);
      } else {
        // ERROR
        STDAIR_LOG_ERROR ("Invalid point of sale " << lPOS);
      }
      // DEBUG
      //STDAIR_LOG_DEBUG ("POS: " << _yieldRule.getPOS ());
    }

    // //////////////////////////////////////////////////////////////////
    storeCabinCode ::
    storeCabinCode (YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeCabinCode::operator() (char iChar,
                                     boost::spirit::qi::unused_type,
                                     boost::spirit::qi::unused_type) const {
      std::ostringstream ostr;
      ostr << iChar;
      const std::string& cabinCodeStr = ostr.str();
      const stdair::CabinCode_T lCabinCode (cabinCodeStr);
      _yieldRule.setCabinCode (lCabinCode);
     
      // DEBUG
      //STDAIR_LOG_DEBUG ("Cabin Code: " << _yieldRule.getCabinCode ());                 
    
    }

    // //////////////////////////////////////////////////////////////////
    storeChannel ::
    storeChannel (YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeChannel::operator() (std::vector<char> iChar,
                                   boost::spirit::qi::unused_type,
                                   boost::spirit::qi::unused_type) const {
      const stdair::ChannelLabel_T lChannel (iChar.begin(), iChar.end());
      if (lChannel != "IN" && lChannel != "IF" && lChannel != "DN"
          && lChannel != "DF" && lChannel != stdair::DEFAULT_CHANNEL) {
        // ERROR
        STDAIR_LOG_ERROR ("Invalid channel " << lChannel);
      }
      _yieldRule.setChannel (lChannel);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Channel: " << _yieldRule.getChannel ());
    }

    // //////////////////////////////////////////////////////////////////
    storeYield::
    storeYield (YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeYield::operator() (double iYield,
                                boost::spirit::qi::unused_type,
                                boost::spirit::qi::unused_type) const {
      const stdair::YieldValue_T lYield= iYield;
      _yieldRule.setYield (lYield);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Yield: " << _yieldRule.getYield ());
    }

    // //////////////////////////////////////////////////////////////////
    storeAirlineCode ::
    storeAirlineCode (YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeAirlineCode::operator() (std::vector<char> iChar,
                                       boost::spirit::qi::unused_type,
                                       boost::spirit::qi::unused_type) const {

      const stdair::AirlineCode_T lAirlineCode (iChar.begin(), iChar.end());
      // Update the airline code
      _yieldRule.setAirlineCode (lAirlineCode);
      // Insertion of this airline Code list in the whole AirlineCode name
      _yieldRule.addAirlineCode (lAirlineCode); 
      // DEBUG
      //STDAIR_LOG_DEBUG ( "Airline code: " << lAirlineCode);
    }

    // //////////////////////////////////////////////////////////////////
    storeClass ::
    storeClass (YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void storeClass::operator() (std::vector<char> iChar,
                                 boost::spirit::qi::unused_type,
                                 boost::spirit::qi::unused_type) const {
      std::ostringstream ostr;
      for (std::vector<char>::const_iterator lItVector = iChar.begin();
         lItVector != iChar.end();
         lItVector++) {
        ostr << *lItVector;
      }
      const std::string& classCodeStr = ostr.str();
      const stdair::ClassCode_T lClassCode (classCodeStr);
      // Insertion of this class Code list in the whole classCode name
      _yieldRule.addClassCode (lClassCode);
      // DEBUG
      //STDAIR_LOG_DEBUG ("Class Code: " << classCodeStr);
    }
    
    // //////////////////////////////////////////////////////////////////
    doEndYield::
    doEndYield (stdair::BomRoot& ioBomRoot,
               YieldRuleStruct& ioYieldRule)
      : ParserSemanticAction (ioYieldRule),
        _bomRoot (ioBomRoot) {
    }
    
    // //////////////////////////////////////////////////////////////////
    void doEndYield::operator() (boost::spirit::qi::unused_type,
                                boost::spirit::qi::unused_type,
                                boost::spirit::qi::unused_type) const {
      // DEBUG
      // STDAIR_LOG_DEBUG ("Do End");
      // Generation of the yield rule object.
      YieldRuleGenerator::createAirportPair (_bomRoot, _yieldRule);
      STDAIR_LOG_DEBUG (_yieldRule.describe());
    }  
    
    // ///////////////////////////////////////////////////////////////////
    //
    //  Utility Parsers
    //
    // ///////////////////////////////////////////////////////////////////
    /** Namespaces. */
    namespace bsq = boost::spirit::qi;
    namespace bsa = boost::spirit::ascii;
    
    /** 1-digit-integer parser */
    stdair::int1_p_t int1_p;
    
    /** 2-digit-integer parser */
    stdair::uint2_p_t uint2_p;

    /** 4-digit-integer parser */
    stdair::uint4_p_t uint4_p;
    
    /** Up-to-4-digit-integer parser */
    stdair::uint1_4_p_t uint1_4_p;

    /** Time element parsers. */
    stdair::hour_p_t hour_p;
    stdair::minute_p_t minute_p;
    stdair::second_p_t second_p;

    /** Date element parsers. */
    stdair::year_p_t year_p;
    stdair::month_p_t month_p;
    stdair::day_p_t day_p;
        
    // //////////////////////////////////////////////////////////////////
    //  (Boost Spirit) Grammar Definition
    // //////////////////////////////////////////////////////////////////
    
    // //////////////////////////////////////////////////////////////////
    YieldRuleParser::YieldRuleParser (stdair::BomRoot& ioBomRoot,
                                      YieldRuleStruct& ioYieldRule) :
      YieldRuleParser::base_type(start),
      _bomRoot(ioBomRoot), _yieldRule(ioYieldRule) {

      start = *(comments | yield_rule);

      comments = (bsq::lexeme[bsq::repeat(2)[bsa::char_('/')]
                              >> +(bsa::char_ - bsq::eol)
                              >> bsq::eol]
                  | bsq::lexeme[bsa::char_('/') >>bsa::char_('*') 
                                >> +(bsa::char_ - bsa::char_('*')) 
                                >> bsa::char_('*') >> bsa::char_('/')]);
      
      yield_rule =  yield_id
        >> ';' >> origin >> ';' >> destination
        >> ';' >> tripType
        >> ';' >> dateRangeStart >> ';' >> dateRangeEnd
        >> ';' >> timeRangeStart >> ';' >> timeRangeEnd
        >> ';' >> point_of_sale >>  ';' >> cabinCode
        >> ';' >> channel >> ';' >> yield
        >> +( ';' >> segment )
        >> yield_rule_end[doEndYield(_bomRoot, _yieldRule)];
        ;

      yield_id = uint1_4_p[storeYieldId(_yieldRule)];

      origin = bsq::repeat(3)[bsa::char_("A-Z")][storeOrigin(_yieldRule)];
      
      destination =  
        bsq::repeat(3)[bsa::char_("A-Z")][storeDestination(_yieldRule)];

      
tripType =
        bsq::repeat(2)[bsa::char_("A-Z")][storeTripType(_yieldRule)];
      
      dateRangeStart = date[storeDateRangeStart(_yieldRule)];

      dateRangeEnd = date[storeDateRangeEnd(_yieldRule)];

      date = bsq::lexeme
        [year_p[boost::phoenix::ref(_yieldRule._itYear) = bsq::labels::_1]
        >> '-'
        >> month_p[boost::phoenix::ref(_yieldRule._itMonth) = bsq::labels::_1]
        >> '-'
        >> day_p[boost::phoenix::ref(_yieldRule._itDay) = bsq::labels::_1] ];

      timeRangeStart = time[storeStartRangeTime(_yieldRule)];
      
      timeRangeEnd = time[storeEndRangeTime(_yieldRule)];

      time =  bsq::lexeme
        [hour_p[boost::phoenix::ref(_yieldRule._itHours) = bsq::labels::_1]
        >> ':'
        >> minute_p[boost::phoenix::ref(_yieldRule._itMinutes) = bsq::labels::_1]      
        >> - (':' >> second_p[boost::phoenix::ref(_yieldRule._itSeconds) = bsq::labels::_1]) ];

      point_of_sale = bsq::repeat(3)[bsa::char_("A-Z")][storePOS(_yieldRule)];

      cabinCode = bsa::char_("A-Z")[storeCabinCode(_yieldRule)];

      channel = bsq::repeat(2)[bsa::char_("A-Z")][storeChannel(_yieldRule)];

      yield = bsq::double_[storeYield(_yieldRule)];

      segment = bsq::repeat(2)[bsa::char_("A-Z")][storeAirlineCode(_yieldRule)]
        >> ';'
        >> bsq::repeat(1,bsq::inf)[bsa::char_("A-Z")][storeClass(_yieldRule)];

      yield_rule_end = bsa::char_(';');

      // BOOST_SPIRIT_DEBUG_NODE (YieldParser);
      BOOST_SPIRIT_DEBUG_NODE (start);
      BOOST_SPIRIT_DEBUG_NODE (comments);
      BOOST_SPIRIT_DEBUG_NODE (yield_rule);
      BOOST_SPIRIT_DEBUG_NODE (yield_id);
      BOOST_SPIRIT_DEBUG_NODE (origin);
      BOOST_SPIRIT_DEBUG_NODE (destination);
      BOOST_SPIRIT_DEBUG_NODE (tripType);
      BOOST_SPIRIT_DEBUG_NODE (dateRangeStart);
      BOOST_SPIRIT_DEBUG_NODE (dateRangeEnd);
      BOOST_SPIRIT_DEBUG_NODE (date);
      BOOST_SPIRIT_DEBUG_NODE (timeRangeStart);
      BOOST_SPIRIT_DEBUG_NODE (timeRangeEnd);
      BOOST_SPIRIT_DEBUG_NODE (time);
      BOOST_SPIRIT_DEBUG_NODE (point_of_sale);
      BOOST_SPIRIT_DEBUG_NODE (cabinCode);
      BOOST_SPIRIT_DEBUG_NODE (channel);
      BOOST_SPIRIT_DEBUG_NODE (yield);
      BOOST_SPIRIT_DEBUG_NODE (segment);
      BOOST_SPIRIT_DEBUG_NODE (yield_rule_end);
     
    }
    
  }


  /////////////////////////////////////////////////////////////////////////
  //
  //  Entry class for the file parser
  //
  /////////////////////////////////////////////////////////////////////////

  // //////////////////////////////////////////////////////////////////////
  YieldFileParser::YieldFileParser (stdair::BomRoot& ioBomRoot,
                                    const std::string& iFilename)
    : _filename (iFilename), _bomRoot (ioBomRoot) {
    init();
  }

  // //////////////////////////////////////////////////////////////////////
  void YieldFileParser::init() {

    // Check that the file exists and is readable
    const bool doesExistAndIsReadable =
      stdair::BasFileMgr::doesExistAndIsReadable (_filename);

    if (doesExistAndIsReadable == false) {
      STDAIR_LOG_ERROR ("The yield schedule file " << _filename
                        << " does not exist or can not be  read.");
      
      throw YieldInputFileNotFoundException ("The yield file " + _filename + " does not exist or can not be read");
    }
  }
    
  // //////////////////////////////////////////////////////////////////////
  void YieldFileParser::generateYieldStore () {
    
    STDAIR_LOG_DEBUG ("Parsing yield input file: " << _filename);

    // File to be parsed
    std::ifstream fileToBeParsed (_filename.c_str(), std::ios_base::in);

    // Check the filename exists and can be open
    if (fileToBeParsed == false) {
      STDAIR_LOG_ERROR ("The yield store file " << _filename
                        << " can not be open."
                        << std::endl);

      throw YieldInputFileNotFoundException ("The file " + _filename
                                             + " does not exist or can not be read");
    }
    
    // Create an input iterator
    stdair::base_iterator_t inputBegin (fileToBeParsed);

    // Convert input iterator to an iterator usable by spirit parser  
    stdair::iterator_t 
      start (boost::spirit::make_default_multi_pass (inputBegin));
    stdair::iterator_t end;

    // Initialise the parser (grammar) with the helper/staging structure.
    YieldParserHelper::YieldRuleParser lYParser(_bomRoot, _yieldRule);
      
    // Launch the parsing of the file and, thanks to the doEndYield
    // call-back structure, the building of the whole BomRoot BOM
    const bool hasParsingBeenSuccesful = 
       boost::spirit::qi::phrase_parse (start, end, lYParser,
                                        boost::spirit::ascii::space);
      
    if (hasParsingBeenSuccesful == false) {
      // TODO: decide whether to throw an exceqption
      STDAIR_LOG_ERROR ("Parsing of yield input file: " << _filename
                        << " failed");
      throw YieldFileParsingFailedException ("Parsing of yield input file: "
                                            + _filename + " failed");
    }
    if  (start != end) {
      // TODO: decide whether to throw an exception
      STDAIR_LOG_ERROR ("Parsing of yield input file: " << _filename
                        << " failed");
      throw YieldFileParsingFailedException ("Parsing of yield input file: "
                                            + _filename + " failed");
    }
    if (hasParsingBeenSuccesful == true && start == end) {
      STDAIR_LOG_DEBUG ("Parsing of yield input file: " << _filename
      << " succeeded");
    }
    
  }
    
}
