# Usage:
# make										# compile the program
# make clean								# remove previous build
# make run									# clean, compile and run the program

CXX	:= g++
CXX_FLAGS := -std=c++20 -ggdb

BIN	:= bin
SRC	:= src
INCLUDE	:= include

LIBRARIES   :=
EXECUTABLE	:= main

all: $(BIN)/$(EXECUTABLE)

run: clean all
		clear -x
		@echo "Executing files..."
		./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
		@echo "Compiling the program..."
		$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)
		@echo "Program compiled!"

clean:
		@echo "Cleaning up..."
		-rm $(BIN)/* -f
