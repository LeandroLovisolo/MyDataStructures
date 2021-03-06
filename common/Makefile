# This Makefile is intended to be included from a directory with source code.
# It requires the BIN variable to be defined in the parent Makefile.

# Compilers and flags
LD          = $(CXX)
CXXFLAGS   := $(CXXFLAGS) -std=c++11 -I../common
ifdef USE_EMSCRIPTEN
  CXXFLAGS := $(CXXFLAGS) -DEMSCRIPTEN
  LDFLAGS  := $(LDFLAGS) -s NO_EXIT_RUNTIME=1
else
  CXX       = clang++
  CXXFLAGS := $(CXXFLAGS) -ggdb
endif

# Targets and dependencies
ifdef USE_EMSCRIPTEN
  ALL = $(OBJ)
else
  ALL = $(BIN)
endif
OBJ   = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
DEP   = $(patsubst %.cpp, %.d, $(wildcard *.cpp))

.PHONY: all js clean

all: $(ALL)

js:
	emmake make all USE_EMSCRIPTEN=1

$(BIN): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MM -MF $(patsubst %.o, %.d, $@) $<
	$(CXX) $(CXXFLAGS) -c $<

-include $(DEP)

clean:
	rm -f $(BIN) $(OBJ) $(DEP)
