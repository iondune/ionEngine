
include ../.configuration.mk

############
# Settings #
############

# Compiler
CXX=g++

# Include Path
INCLUDE=-I .. -I ../Include

# Non-Configuration-Specific Settings
CXXFLAGS_BASE=$(INCLUDE) -std=c++11 -DGLM_FORCE_RADIANS

# Configuration-Specific Settings
CXXFLAGS_DEBUG=-g
CXXFLAGS_RELEASE=-O3
CXXFLAGS_COVERAGE=-g -O0 --coverage -fprofile-arcs -ftest-coverage


#############
# Variables #
#############

# Configuration-Specific Settings
CXXFLAGS=$(CXXFLAGS_BASE)

ifeq      "$(CONFIGURATION)" "Debug"
CXXFLAGS+=$(CXXFLAGS_DEBUG)
else ifeq "$(CONFIGURATION)" "Release"
CXXFLAGS+=$(CXXFLAGS_RELEASE)
else ifeq "$(CONFIGURATION)" "Coverage"
CXXFLAGS+=$(CXXFLAGS_COVERAGE)
else
$(warn Unknown build configuration: $(CONFIGURATION))
endif

# Files
SRCS=$(wildcard *.cpp)
OBJS=$(addprefix $(CONFIGURATION)/,$(subst .cpp,.o,$(SRCS)))


###########
# Targets #
###########

.PHONY: all clean depend remake

all: $(CONFIGURATION)/$(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET) $(CONFIGURATION) coverage.info

remake: | clean all

depend:
	@rm -f .depend.mk
	@$(MAKE) --no-print-directory .depend.mk

.depend.mk:
	@echo --- Regenerating dependencies. ------------------
	$(CXX) -MM $(CXXFLAGS_BASE) $(SRCS) > .depend.mk
	@sed -i -re 's/(^[A-Za-z0-9]+\.o:)/$$(CONFIGURATION)\/\1/' .depend.mk
	@echo --- Dependencies generated. ---------------------

../.configuration.mk:
	@echo 'No configuration found, defaulting to Debug'
	@echo 'CONFIGURATION=Debug' > $@

ifeq "$(suffix $(TARGET))" ".a"
$(CONFIGURATION)/$(TARGET): $(OBJS)
	ar rc $@ $^
else
$(CONFIGURATION)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
endif

$(CONFIGURATION)/%.o: %.cpp
	@mkdir -p $(CONFIGURATION)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Dependencies
-include .depend.mk
