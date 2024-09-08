CXX=g++
CXXFLAGS=-Wall -Wextra -Wpedantic -std=c++17 -O3 -fopenmp -march=native

TARGET=graveler
.PHONY: all, branch, clean
all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

branch: $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -DBRANCH -o $(TARGET) $^
	
clean:
	$(RM) $(TARGET)
