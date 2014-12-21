# Compilers and flags
CPP      = clang++
CPPFLAGS = -std=c++11 -ggdb
LD       = $(CPP)

# Targets
BIN = avl
OBJ = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
DEP = $(patsubst %.cpp, %.d, $(wildcard *.cpp))

.PHONY: all clean
	
all: $(BIN)

emscripten: emsetup all

emsetup:
	CPP=emcc

$(BIN): $(OBJ)
	$(LD) -o $@ $^

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -MM -MF $(patsubst %.o, %.d, $@) $<
	$(CPP) $(CPPFLAGS) -c $<

-include $(DEP)

clean:
	rm -f $(BIN) $(OBJ) $(DEP)
