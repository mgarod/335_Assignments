#Title:        Makefile
#Author:       Michael Garod
#Date Created: 12/8/2015
#Class:        Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
#Professor:    Ioannis Stamos
#Purpose:      Assignment #5
#Description:  Script to easily build and clean programs necessary for this
#			   assignment. See README.txt for usage.

########################################
##
## Makefile
## LINUX compilation 
##
##############################################

#FLAGS
C++FLAG = -g -std=c++11 -Wall

#Math Library
MATH_LIBS = -lm
EXEC_DIR=.

#Rule for .cpp files
# .SUFFIXES : .cpp.o 

.cpp.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@

#Including
INCLUDES=  -I. 

LIBS_ALL =  -L/usr/lib -L/usr/local/lib $(MATH_LIBS) 

#ZEROTH PROGRAM
ALL_OBJ0=main.o Graph.o
PROGRAM_0=SearchGraph
$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

#Compiling all

all: 	
		make $(PROGRAM_0)

RunSearchGraph1:
		./$(PROGRAM_0) Graph1.txt 0
		./$(PROGRAM_0) Graph1.txt 1
		./$(PROGRAM_0) Graph1.txt 2
		./$(PROGRAM_0) Graph1.txt 3
		./$(PROGRAM_0) Graph1.txt 4

RunSearchGraph2: 	
		./$(PROGRAM_0) Graph2.txt 0
		./$(PROGRAM_0) Graph2.txt 1
		./$(PROGRAM_0) Graph2.txt 2
		./$(PROGRAM_0) Graph2.txt 3
		./$(PROGRAM_0) Graph2.txt 4
		./$(PROGRAM_0) Graph2.txt 5
		./$(PROGRAM_0) Graph2.txt 6

#Clean obj files

clean:
	(rm -f *.o; rm -f $(PROGRAM_0))

(:
