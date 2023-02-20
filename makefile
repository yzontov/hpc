
# Use Intel C/C++ Compiler
CXX = icpc

# Compile-time flags 
CXXFLAGS = -pthread -xHOST -O3 

all: main.o util.o math.o ep.o profiles.o rules.o
	$(CXX) $(CXXFLAGS) main.o util.o math.o ep.o profiles.o rules.o -o scoring
	rm -f *.o *~
	mv scoring ../scoring


main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp

util.o: util.cpp
	$(CXX) -c $(CXXFLAGS) util.cpp

math.o: math.cpp
	$(CXX) -c $(CXXFLAGS) math.cpp

ep.o: ep.cpp
	$(CXX) -c $(CXXFLAGS) ep.cpp

profiles.o: profiles.cpp
	$(CXX) -c $(CXXFLAGS) profiles.cpp
rules.o: rules.cpp
	$(CXX) -c $(CXXFLAGS) rules.cpp

