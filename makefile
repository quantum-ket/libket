DLL = libket.so 

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

CXX = g++
CXXFLAGS = -fPIC -shared -std=c++17 -g -Wall -Werror
CXXLINK = -lboost_program_options -lpthread -lboost_serialization

all: $(DLL)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(DLL): $(OBJ) 
	$(CXX) $(CXXFLAGS) $(CXXLINK) -o $@ $^

install: $(DLL)
	cp $(DLL) /usr/lib/
	cp include/ket.hpp /usr/include/ket
	cp include/libket.hpp /usr/include/libket

uninstall:
	rm -f /usr/lib/$(DLL)
	rm -f /usr/include/ket
	rm -f /usr/include/libket -r

clean:
	rm -f $(OBJ) $(DLL)
