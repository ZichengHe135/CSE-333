# Zicheng He 1534763 zicheh@uw.edu
# Copyright ©2018 Zicheng He.  All rights reserved.
# This is a makefile for CSE 333 ex16
CXX = g++
CPPFLAGS = -Wall -g -std=c++11

# defalut make
all: ex16
	
ex16: ex16.o Listen.o
	$(CXX) $(CPPFLAGS) -o $@ $^
ex16.o: ex16.cc Listen.h
	$(CXX) $(CPPFLAGS) -c $<
Listen.o: Listen.cc Listen.h
	$(CXX) $(CPPFLAGS) -c $<
# clean executable and others
clean:
	rm -rf ex16 *.o *~ ex16.dSYM
