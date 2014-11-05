
include ../.configuration.mk

all: $(CONFIGURATION)/$(TARGET)

../.configuration.mk:
	@echo 'No configuration found, defaulting to Debug'
	@echo 'CONFIGURATION=Debug' > $@

CXX=clang++
INCLUDE=-I .. -I ../Include
CXXFLAGS=$(INCLUDE) -std=c++11
CXXFLAGS_DEBUG=-g
CXXFLAGS_RELEASE=-O3
CXXFLAGS_COVERAGE=

ifeq      "$(CONFIGURATION)" "Debug"
CXXFLAGS+=$(CXXFLAGS_DEBUG)
else ifeq "$(CONFIGURATION)" "Release"
CXXFLAGS+=$(CXXFLAGS_RELEASE)
else ifeq "$(CONFIGURATION)" "Coverage"
CXXFLAGS+=$(CXXFLAGS_COVERAGE)
else
$(warn Unknown build configuration: $(CONFIGURATION))
endif

SRCS=$(wildcard *.cpp)
OBJS=$(addprefix $(CONFIGURATION)/,$(subst .cpp,.o,$(SRCS)))

ifeq "$(suffix $(TARGET))" ".a"
$(CONFIGURATION)/$(TARGET): $(OBJS)
	ar rc $@ $^
else
$(CONFIGURATION)/$(TARGET): $(OBJS)
	$(CXX) -o $@ $^
endif

$(CONFIGURATION)/%.o: %.cpp
	@mkdir -p $(CONFIGURATION)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.depend.mk:
	@echo --- Regenerating dependencies. ------------------
	$(CXX) -MM $(CXXFLAGS) $(SRCS) > .depend.mk
	sed -i -re 's/(^[A-Za-z]+\.o:)/$$(CONFIGURATION)\/\1/' .depend.mk
	@echo --- Dependencies generated ----------------------

clean:
	rm -f $(OBJS) $(TARGET) $(CONFIGURATION)

remake: clean all

depend:
	@rm .depend.mk
	@$(MAKE) --no-print-directory .depend.mk

.PHONY: clean remake depend

# Dependencies
include .depend.mk
