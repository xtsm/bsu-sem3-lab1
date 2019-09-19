CXXFLAGS=-Wall -Wextra -Weffc++ -Werror -std=c++17

.PHONY: all test main

all: main

res.o: res.rc
		i686-w64-mingw32-windres res.rc -o res.o

main: main.cpp res.o
		i686-w64-mingw32-g++ $(CXXFLAGS) -mwindows -static main.cpp res.o -o /tmp/main.exe
		wine /tmp/main.exe

test: test.cpp
		g++ $(CXXFLAGS) test.cpp -o test.out
		./test.out

example: example.cpp
		i686-w64-mingw32-g++ $(CXXFLAGS) -mwindows -static example.cpp -o /tmp/main.exe
		wine /tmp/main.exe

