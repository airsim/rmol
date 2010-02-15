bas_h_sources = \
				$(top_srcdir)/stdair/basic/BasTypes.hpp \
				$(top_srcdir)/stdair/basic/BasConst_General.hpp \
				$(top_srcdir)/stdair/basic/BasConst_Inventory.hpp \
				$(top_srcdir)/stdair/basic/BasConst_BookingClass.hpp \
				$(top_srcdir)/stdair/basic/BasConst_Yield.hpp \
				$(top_srcdir)/stdair/basic/BasConst_Period_BOM.hpp \
				$(top_srcdir)/stdair/basic/BasConst_TravelSolution.hpp \
				$(top_srcdir)/stdair/basic/StructAbstract.hpp \
				$(top_srcdir)/stdair/basic/BasChronometer.hpp \
				$(top_srcdir)/stdair/basic/BasFileMgr.hpp \
				$(top_srcdir)/stdair/basic/BasLogParams.hpp \
				$(top_srcdir)/stdair/basic/BasDBParams.hpp \
				$(top_srcdir)/stdair/basic/PassengerType.hpp \
				$(top_srcdir)/stdair/basic/ContinuousAttribute.hpp \
				$(top_srcdir)/stdair/basic/ArrivalPattern.hpp \
				$(top_srcdir)/stdair/basic/CategoricalAttribute.hpp \
				$(top_srcdir)/stdair/basic/DemandCharacteristics.hpp \
				$(top_srcdir)/stdair/basic/DemandDistribution.hpp \
				$(top_srcdir)/stdair/basic/RandomGeneration.hpp \
				$(top_srcdir)/stdair/basic/RandomGenerationContext.hpp
bas_cc_sources = \
				$(top_srcdir)/stdair/basic/BasConst.cpp \
				$(top_srcdir)/stdair/basic/BasChronometer.cpp \
				$(top_srcdir)/stdair/basic/BasFileMgr.cpp \
				$(top_srcdir)/stdair/basic/BasLogParams.cpp \
				$(top_srcdir)/stdair/basic/BasDBParams.cpp \
				$(top_srcdir)/stdair/basic/PassengerType.cpp \
				$(top_srcdir)/stdair/basic/DemandCharacteristics.cpp \
				$(top_srcdir)/stdair/basic/DemandDistribution.cpp \
				$(top_srcdir)/stdair/basic/RandomGeneration.cpp \
				$(top_srcdir)/stdair/basic/RandomGenerationContext.cpp
