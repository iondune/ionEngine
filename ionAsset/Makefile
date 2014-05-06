CXX=clang++
INCLUDE=-I ../ \
	-I ~/include/glm/ \
	-I ~/include/stb/
CXXFLAGS=$(INCLUDE) -g -std=c++11

SRCS=$(shell find . -name "*.cpp")
OBJS=$(subst .cpp,.o,$(SRCS))

TARGET=libionAsset.a

all: $(TARGET)

UCT: $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(TARGET): $(OBJS)
	ar rc $@ $^

clean:
	rm -f $(OBJS) libionAsset.a

remake: clean all

depend: .depend.mk
	@echo Regenerating local dependencies.
	@makedepend -Y $(SRCS) $(HDRS) -I ../ -f.depend.mk > /dev/null 2>&1
	@rm .depend.mk.bak

.depend.mk:
	@touch .depend.mk

# Dependencies
include .depend.mk
