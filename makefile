Project: main.o
	g++ -g -std=c++11 -Wall main.o -o Project

main.o: main.cpp CPU.h CPU.cpp
	g++ -g -std=c++11 -Wall -c main.cpp

clean:
	rm *.o Project
