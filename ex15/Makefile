# Zicheng He 1534763 zicheh@uw.edu
# Copyright ©2018 Zicheng He.  All rights reserved.
# This is a makefile for CSE 333 ex15
CXX = g++
CPPFLAGS = -Wall -g -std=c++11

# defalut make
all: ex15
	
ex15: ex15.o connect.o
	$(CXX) $(CPPFLAGS) -o $@ $^
ex15.o: ex15.cc connect.h
	$(CXX) $(CPPFLAGS) -c $<
connect.o: connect.cc connect.h
	$(CXX) $(CPPFLAGS) -c $<
# clean executable and others
clean:
	rm -rf ex15 *.o *~ ex15.dSYM
