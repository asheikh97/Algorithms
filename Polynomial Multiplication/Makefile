# ######################################################################
# #
# # Author: Abadali Sheikh
# # Date:   2 December 2019
# #
# ######################################################################

# if you want to use a debugger, add a "-g" flag to the next line
CXXFLAGS=-Wall -Wno-sign-compare -std=c++1z 

main: main.o Polynomial.o Polynomial.h random.o
	g++ -o main $(CXXFLAGS) main.o Polynomial.o random.o

main.o: main.cc 

Polynomial.o: Polynomial.cc Polynomial.h

random.o: random.cc random.h

clean:
	@/bin/rm -f *~ \#*\# core* main *.o
