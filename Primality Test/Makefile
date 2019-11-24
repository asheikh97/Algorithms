#
# CISC 4080, Project 1: Testing For Primes
#
# Author: A. G. Werschulz
# Date:   1 Feb 2018

CXXFLAGS = -std=c++11 -Wall

main: main.o random.o 
	$(CXX) $(CXXFLAGS) -o main main.o random.o

random.o: random.cc random.h

clean:
	rm -f main *.o *~ \#*