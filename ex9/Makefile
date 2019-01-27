# Zicheng He 1534763 zicheh@uw.edu
# Copyright ©2018 Zicheng He.  All rights reserved.
# This is a makefile for CSE 333 ex9
CXX = g++
CPPFLAGS = -Wall -g -std=c++11

# defalut make
all: ex9
	
ex9: ex9.o IntPair.o
	$(CXX) $(CPPFLAGS) -o $@ $^
ex9.o: ex9.cc IntPair.h
	$(CXX) $(CPPFLAGS) -c $<
IntPair.o: IntPair.cc IntPair.h
	$(CXX) $(CPPFLAGS) -c $<
# clean executable and others
clean:
	rm -rf ex9 *.o *~ ex9.dSYM
