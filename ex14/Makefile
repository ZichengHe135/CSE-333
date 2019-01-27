# Zicheng He 1534763 zicheh@uw.edu
# Copyright ©2018 Zicheng He.  All rights reserved.
# This is a makefile for CSE 333 ex14
CXX = g++
CPPFLAGS = -Wall -g -std=c++11

# defalut make
all: ex14
	
ex14: ex14.o Cartesian.o Polar.o
	$(CXX) $(CPPFLAGS) -o $@ $^
ex14.o: ex14.cc Coordinate.h Cartesian.h Polar.h
	$(CXX) $(CPPFLAGS) -c $<
Cartesian.o: Cartesian.cc Cartesian.h Coordinate.h
	$(CXX) $(CPPFLAGS) -c $<
Polar.o: Polar.cc Polar.h Coordinate.h
	$(CXX) $(CPPFLAGS) -c $<
# clean executable and others
clean:
	rm -rf ex14 *.o *~ ex14.dSYM
