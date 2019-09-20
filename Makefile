CXXFLAGS=-Wall -Wextra -Weffc++ -Werror -std=c++17
SRC=main.cpp view.cpp model.cpp controller.cpp

.PHONY: all test main

all: main

res.o: res.rc
		i686-w64-mingw32-windres res.rc -o res.o

main: $(SRC) res.o
		i686-w64-mingw32-g++ $(CXXFLAGS) -mwindows -static $(SRC) res.o -o /tmp/main.exe
		wine /tmp/main.exe

test: test.cpp
		g++ $(CXXFLAGS) test.cpp -o test.out
		./test.out
