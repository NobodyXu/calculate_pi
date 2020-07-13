CXX := clang++
CXXFLAGS := -std=c++17 -Ofast -ffast-math -flto

SRCS=$(wildcard *.cc)
EXES=$(SRCS:.cc=)

%: %.cc utility.hpp
	$(CXX) $(CXXFLAGS) $< -o $@
