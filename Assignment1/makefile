EXE = TestMatrix
OBJS = main.o
SOURCE = main.cpp
CC = g++
DEBUG = -g -Wall
CFLAGS = -std=c++11 -c $(DEBUG)
LFLAGS = -std=c++11 $(DEBUG)

$(EXE): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXE)

main.o: main.cpp matrix.h
	$(CC) $(CFLAGS) $(SOURCE)

all: $(EXE)

clean: $(OBJS) $(EXE)
	rm $(OBJS) $(EXE)