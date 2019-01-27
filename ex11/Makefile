# Zicheng He 1534763 zicheh@uw.edu
# Copyright ©2018 Zicheng He.  All rights reserved.
# This is a makefile for CSE 333 ex11
CXX = g++
CPPFLAGS = -Wall -g -std=c++11

# defalut make
all: ex11
	
ex11: ex11.o Vector.o
	$(CXX) $(CPPFLAGS) -o $@ $^
ex11.o: ex11.cc Vector.h
	$(CXX) $(CPPFLAGS) -c $<
Vector.o: Vector.cc Vector.h
	$(CXX) $(CPPFLAGS) -c $<
# clean executable and others
clean:
	rm -rf ex11 *.o *~ ex11.dSYM
