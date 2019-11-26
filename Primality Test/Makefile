#
# CISC 4080, Project 1: Testing For Primes
#
# Author: Abadali Sheikh
# Date:   1 Feb 2018

CXXFLAGS = -std=c++17 -Wall

proj1: proj1.o random.o 
	$(CXX) $(CXXFLAGS) -o proj1 proj1.o random.o

random.o: random.cc random.h

clean:
	rm -f proj1 *.o *~ \#*
