## command sub-directory
include $(top_srcdir)/Makefile.common

MAINTAINERCLEANFILES = Makefile.in

check_PROGRAMS = random_cycle_test \
				single_date_simulator \
				simulator \
				parser spirit_parser

random_cycle_test_SOURCES = random_cycle_test.cpp
random_cycle_test_LDADD = $(BOOST_LIB) \
		$(top_builddir)/@PACKAGE@/liblatus.la

single_date_simulator_SOURCES = single_date_simulator.cpp
single_date_simulator_LDADD = $(BOOST_LIB) \
		$(top_builddir)/@PACKAGE@/liblatus.la

#full_event_generator_SOURCES = full_event_generator.cpp
#full_event_generator_LDADD = $(BOOST_LIB) \
#		$(top_builddir)/@PACKAGE@/liblatus.la

simulator_SOURCES = simulator.cpp
simulator_LDADD = $(BOOST_LIB) \
		$(top_builddir)/@PACKAGE@/liblatus.la

parser_SOURCES = parser.cpp
parser_LDADD = $(BOOST_LIB)

spirit_parser_SOURCES = spirit_parser.cpp
spirit_parser_LDADD = $(BOOST_LIB)

EXTRA_DIST = test_single_date_simulator.sh test_full_event_generator.sh \
			test_simulator.sh test_parser.sh test_spirit_parser.sh \
			samples/*.csv db/*.csv db/*.sql
