CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g 
LDFLAGS =  

SRC = $(wildcard source/*.cpp) $(wildcard source/utils/*.cpp) $(wildcard source/osm/*.cpp) $(wildcard source/graphviewer/*.cpp)
OBJ = $(SRC:.cc=.o)
EXEC = rideshare

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)
