###
ROOT_DIR = `pwd`
#INSTALL_ROOTDIR = /usr/local
INSTALL_ROOTDIR = $(HOME)/dev
INSTALL_HEADDIR = $(INSTALL_ROOTDIR)/include/rmol
INSTALL_LIBDIR = $(INSTALL_ROOTDIR)/lib

###
# 32/64 bits Processor
PROC64 = 1

###
# Compilation / Linking Flags
CC_PROC_FLAG = $(if $(PROC64), -m64, )
COMP_FLAG = -g $(CC_PROC_FLAG)

###
# Tools
CC = gcc $(COMP_FLAG)
CCC = g++ $(COMP_FLAG)
SHLD = gcc $(COMP_FLAG)
LD = g++ $(COMP_FLAG)
RM = rm -f
RMR = rm -rf
CP = cp
LN = ln -s
MKDIR = mkdir -p
TAR_ZIP = tar zcf

# GSL (GNU Scientific Library)
GSL_ROOTDIR=/projects/ngi/local/Linux/gsl-1.7
GSL_LIB_PATH = $(GSL_ROOTDIR)/lib
GSL_LIB_PATH_FLAGS = $(GSL_LIB_PATH:%=-L%)
GSL_LIB_PATH_FLAGS += $(GSL_LIB_PATH:%=-Wl,--rpath=%)

# Statistical Extension to GSL (SEG)
#SEG_LIB_NAME = seg
#SEG_ROOTDIR = $(INSTALL_ROOTDIR)
#SEG_LIB_PATH = $(SEG_ROOTDIR)/lib
#SEG_LIB_PATH_FLAGS = $(SEG_LIB_PATH:%=-L%)
#SEG_LIB_PATH_FLAGS += $(SEG_LIB_PATH:%=-Wl,--rpath=%)

# Revenue Management Open Library (RMOL)
RMOL_LIB_NAME = rmol
RMOL_ROOTDIR = $(INSTALL_ROOTDIR)
RMOL_LIB_PATH = $(RMOL_ROOTDIR)/lib
RMOL_LIB_PATH_FLAGS = $(RMOL_LIB_PATH:%=-L%)
RMOL_LIB_PATH_FLAGS += $(RMOL_LIB_PATH:%=-Wl,--rpath=%)

###
# Compilation options
OBJ_PATH = $(ROOT_DIR)/obj
#INCLUDES_FLAG = -I$(GSL_ROOTDIR)/include -I$(SEG_ROOTDIR)/include
INCLUDES_FLAG = -I$(GSL_ROOTDIR)/include -I$(RMOL_ROOTDIR)/include
RELOC_FLAG = -fpic
CC_FLAGS = $(RELOC_FLAG) $(INCLUDES_FLAG)

###
# Dynamic Library options
LIB_SUFFIX = .so
SHD_LIB_FLAGS = -shared
#SHD_LIBS = $(SEG_LIB_PATH_FLAGS) -l$(SEG_LIB_NAME)
SHD_LIBS += $(GSL_LIB_PATH_FLAGS) -lgsl -lgslcblas -lm

###
# Executable options
BIN_PATH = $(ROOT_DIR)/bin
LD_FLAGS =

###
# Dynamic library building
RMOL_SRC = 	FldYieldRange.cpp FldDistributionParameters.cpp \
		FacSupervisor.cpp \
		FacAbstract.cpp FacPartialSumHolder.cpp FacBucketHolder.cpp \
		BomAbstract.cpp \
		Demand.cpp \
		Bucket.cpp BucketHolder.cpp \
		Emsr.cpp \
		Gaussian.cpp \
		DemandGeneratorList.cpp \
		PartialSumHolder.cpp \
		MCUtils.cpp
RMOL_OBJ = $(RMOL_SRC:%.cpp=$(OBJ_PATH)/%.o)
RMOL_HEAD = $(RMOL_SRC:%.cpp=%.hpp) \
			VariateList.hpp \
			DistributionParameterList.hpp \
			PartialSumList.hpp \
			BucketList.hpp
FULL_INSTALL_HEAD = $(RMOL_HEAD:%=$(INSTALL_HEADDIR)/%)

# Generated Library name
RMOL_VERSION = 0.07
RMOL_LIB_SHORT = $(RMOL_LIB_NAME)
RMOL_LIB_WOV = lib$(RMOL_LIB_SHORT)$(LIB_SUFFIX)
RMOL_LIB = $(RMOL_LIB_WOV).$(RMOL_VERSION)
SHD_LIB_FLAGS += -Wl,-soname,$(RMOL_LIB)

# Generated Library path: directory where the library is generated.
# Then, it is copied into the installation library path.
LIB_PATH = $(ROOT_DIR)/lib
LIB_FULL_NAME = $(LIB_PATH)/$(RMOL_LIB)

# Installed Library path
INSTALLED_LIB_PATH = $(INSTALL_LIBDIR)
FULL_INSTALL_LIB = $(INSTALLED_LIB_PATH)/$(RMOL_LIB)
LIB_PATH_FLAGS = $(INSTALLED_LIB_PATH:%=-L%)
LIB_PATH_FLAGS += $(INSTALLED_LIB_PATH:%=-Wl,--rpath=%)


###
# Main (test) program
TEST_MAIN = optimise
TEST_MAIN_SRC = $(TEST_MAIN).cpp
TEST_MAIN_OBJ = $(TEST_MAIN_SRC:%.cpp=$(OBJ_PATH)/%.o)
LD_FLAGS += $(RMOL_LIB_PATH_FLAGS) -l$(RMOL_LIB_NAME)
FULL_BIN_NAME = $(BIN_PATH)/$(TEST_MAIN)

###
# Tar-ball
TAR_BALL = $(RMOL_LIB_NAME)_$(RMOL_VERSION).tgz

###
# Targets
first: $(LIB_FULL_NAME)
test: $(FULL_BIN_NAME)

###
# Compilation Rule
$(OBJ_PATH)/%.o: %.c
	@if [ ! -d $(OBJ_PATH) ]; then $(MKDIR) $(OBJ_PATH); fi
	@echo "Compiling $<..." && $(CC) $(CC_FLAGS) -o $@ -c $<

$(OBJ_PATH)/%.o: %.cpp
	@if [ ! -d $(OBJ_PATH) ]; then $(MKDIR) $(OBJ_PATH); fi
	@echo "Compiling $<..." && $(CCC) $(CC_FLAGS) -o $@ -c $<

# Makefile debug target
print_%_value:
	@echo $($*)

###
# Dynamic Library Linking
$(LIB_FULL_NAME): $(RMOL_OBJ)
	@if [ ! -d $(LIB_PATH) ]; then $(MKDIR) $(LIB_PATH); fi
	@echo "Linking $@..." \
	&& $(SHLD) $(SHD_LIB_FLAGS) -o $@ $(RMOL_OBJ) $(SHD_LIBS)

# Library Header Installing
$(FULL_INSTALL_HEAD): $(RMOL_HEAD)
	@if [ ! -d $(INSTALL_HEADDIR) ]; then $(MKDIR) $(INSTALL_HEADDIR); fi
	@(echo "Installing $(RMOL_HEAD) in $(INSTALL_HEADDIR)"; \
	$(CP) $(RMOL_HEAD) $(INSTALL_HEADDIR)) 2> /dev/null \
	|| echo "You need to be root to install in $(INSTALL_ROOTDIR)"

# Library Installing
$(FULL_INSTALL_LIB): $(LIB_FULL_NAME)
	@if [ ! -d $(INSTALL_LIBDIR) ]; then $(MKDIR) $(INSTALL_LIBDIR); fi
	@(echo "Installing $(RMOL_LIB_WOV) ($(RMOL_LIB)) in $(INSTALL_LIBDIR)"; \
	$(RM) $(INSTALL_LIBDIR)/$(RMOL_LIB); \
	$(CP) $< $(INSTALL_LIBDIR); \
	cd $(INSTALL_LIBDIR); $(RM) $(RMOL_LIB_WOV); \
	$(LN) $(RMOL_LIB) $(RMOL_LIB_WOV); cd $(ROOT_DIR)) 2> /dev/null \
	|| echo "You need to be root to install in $(INSTALL_ROOTDIR)"


###
# Executable Linking
$(FULL_BIN_NAME): install $(TEST_MAIN_OBJ)
	@if [ ! -d $(BIN_PATH) ]; then $(MKDIR) $(BIN_PATH); fi
	@echo "Linking $@" && $(LD) $(LD_FLAGS) -o $@ $(TEST_MAIN_OBJ) \
	&& echo "Type bin/$(TEST_MAIN) to start playing"

###
# Cleaning the object, library and executable files and directories
clean:
	@$(RM) *~ core.* $(TAR_BALL)
	@$(RMR) $(OBJ_PATH) $(LIB_PATH) $(BIN_PATH)

tar: clean
	@$(TAR_ZIP) $(TAR_BALL) INSTALL Makefile *.hpp *.cpp \
	$(TEST_MAIN_SRC)

install: $(FULL_INSTALL_HEAD) $(FULL_INSTALL_LIB)
