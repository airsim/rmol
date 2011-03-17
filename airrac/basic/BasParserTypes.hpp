#ifndef __AIRRAC_BAS_BASCOMPARSERTYPES_HPP
#define __AIRRAC_BAS_BASCOMPARSERTYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
// Boost
//#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/home/classic/core.hpp>
#include <boost/spirit/home/classic/attribute.hpp>
#include <boost/spirit/home/classic/utility/functor_parser.hpp>
#include <boost/spirit/home/classic/utility/loops.hpp>
#include <boost/spirit/home/classic/utility/chset.hpp>
#include <boost/spirit/home/classic/utility/confix.hpp>
#include <boost/spirit/home/classic/iterator/file_iterator.hpp>
#include <boost/spirit/home/classic/actor/push_back_actor.hpp>
#include <boost/spirit/home/classic/actor/assign_actor.hpp>

namespace AIRRAC {

  // ///////////////////////////////////////////////////////////////////////
  //
  //  Definition of Basic Types
  //
  // ///////////////////////////////////////////////////////////////////////
  // For a file, the parsing unit is the character (char). For a string,
  // it is a "char const *".
  // typedef char const* iterator_t;
  typedef char char_t;
    
  // The types of iterator, scanner and rule are then derived from
  // the parsing unit.
  typedef boost::spirit::classic::file_iterator<char_t> iterator_t;
  typedef boost::spirit::classic::scanner<iterator_t> scanner_t;
  typedef boost::spirit::classic::rule<scanner_t> rule_t;
    
  // ///////////////////////////////////////////////////////////////////////
  //
  //  Parser related types
  //
  // ///////////////////////////////////////////////////////////////////////
  /** 1-digit-integer parser */
  typedef boost::spirit::classic::int_parser<unsigned int, 10, 1, 1> int1_p_t;
    
  /** 2-digit-integer parser */
  typedef boost::spirit::classic::uint_parser<unsigned int, 10, 2, 2> uint2_p_t;
    
  /** Up-to-2-digit-integer parser */
  typedef boost::spirit::classic::uint_parser<unsigned int, 10, 1, 2> uint1_2_p_t;    

  /** Up-to-3-digit-integer parser */
  typedef boost::spirit::classic::uint_parser<unsigned int, 10, 1, 3> uint1_3_p_t;    

  /** 4-digit-integer parser */
  typedef boost::spirit::classic::uint_parser<unsigned int, 10, 4, 4> uint4_p_t;

  /** Up-to-4-digit-integer parser */
  typedef boost::spirit::classic::uint_parser<unsigned int, 10, 1, 4> uint1_4_p_t;    

  /** character set  */
  typedef boost::spirit::classic::chset<char_t> chset_t;
    
  /** (Repeating) sequence of a given number of characters:
      repeat_p(min, max) */
  typedef boost::spirit::classic::impl::loop_traits<chset_t,
                                           unsigned int,
                                           unsigned int>::type repeat_p_t;

  /** Bounded-number-of-integers parser */
  typedef boost::spirit::classic::bounded<uint2_p_t, unsigned int> bounded2_p_t;
  typedef boost::spirit::classic::bounded<uint1_2_p_t, unsigned int> bounded1_2_p_t;
  typedef boost::spirit::classic::bounded<uint1_3_p_t, unsigned int> bounded1_3_p_t;
  typedef boost::spirit::classic::bounded<uint4_p_t, unsigned int> bounded4_p_t;
  typedef boost::spirit::classic::bounded<uint1_4_p_t, unsigned int> bounded1_4_p_t;
}
#endif // __AIRRAC_BAS_BASCOMPARSERTYPES_HPP
