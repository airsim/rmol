## command sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

check_PROGRAMS = full_calculator functor_parser number_parser \
		parameter_parser spirit_parser subrule_parser \
		schedule_parser

full_calculator_SOURCES = full_calculator.cpp
full_calculator_LDADD = $(BOOST_LIB)

functor_parser_SOURCES = functor_parser.cpp
functor_parser_LDADD = $(BOOST_LIB)

number_parser_SOURCES = number_parser.cpp
number_parser_LDADD = $(BOOST_LIB)

parameter_parser_SOURCES = parameter_parser.cpp
parameter_parser_LDADD = $(BOOST_LIB)

spirit_parser_SOURCES = spirit_parser.cpp
spirit_parser_LDADD = $(BOOST_LIB)

subrule_parser_SOURCES = subrule_parser.cpp
subrule_parser_LDADD = $(BOOST_LIB)

schedule_parser_SOURCES = schedule_parser.cpp
schedule_parser_LDADD = $(BOOST_LIB)

EXTRA_DIST = test_full_calculator.sh test_functor_parser.sh \
		test_number_parser.sh test_parameter_parser.sh \
		test_spirit_parser.sh test_subrule_parser.sh
