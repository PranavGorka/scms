CXX = g++
CXXFLAGS = -std=c++26 -Iinclude -Wall

SRC = src/Logger.cpp src/main.cpp
OBJ = $(SRC:.cpp=.o)

all: scms

scms: $(OBJ)
	$(CXX) $(CXXFLAGS) -o build/scms $(OBJ)

clean:
	rm -f src/*.o build/scms
