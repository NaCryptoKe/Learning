CXX = g++

CXXFLAGS = -Wall -std=c++17 -Iinclude

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f main test app
