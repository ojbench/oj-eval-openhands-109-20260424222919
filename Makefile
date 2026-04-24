CXX = g++
CXXFLAGS = -std=c++17 -O2

code: code.cpp
	$(CXX) $(CXXFLAGS) -o code code.cpp

clean:
	rm -f code *.o
