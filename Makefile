CXXFLAGS=-Wall -Wextra -Weffc++ -Werror -std=c++17
SRC=main.cpp view.cpp model.cpp controller.cpp observe.cpp

.PHONY: all test main

all: main

main: $(SRC) res.o
		g++ $(CXXFLAGS) $(SRC) -o main.out
		./main.out

test: test.cpp
		g++ $(CXXFLAGS) test.cpp -o test.out
		./test.out
