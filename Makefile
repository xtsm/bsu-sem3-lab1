CXXFLAGS=-Wall -Wextra -Weffc++ -Werror -std=c++17
SRC=main.cpp tostring_visitor.cpp min_visitor.cpp

.PHONY: all test main

all: main

main: $(SRC)
		g++ $(CXXFLAGS) $(SRC) -o main.out
		./main.out

test: test.cpp
		g++ $(CXXFLAGS) test.cpp -o test.out
		./test.out
