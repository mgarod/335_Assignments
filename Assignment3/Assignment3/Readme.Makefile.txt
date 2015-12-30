/***************************************************************
Title:          Readme.Makefile.txt
Author:         Michael Garod
Date Created:   10/24/2015
Class:          Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:      Ioannis Stamos
Purpose:        Assignment #3
Description:    This file was given as with the assignment.
***************************************************************/

You will use this exact Makefile for your homework 3. Failure to do so will result in deduction of 10 points. Do not alter the Makefile in anyway. Do NOT rename it to anything like makefile or makefile.txt or Makefile.txt. 

You have to name your main files (one for file for each program) as follows:

CreateAndTestHash.cpp

SpellCheck.cpp

Threre is no exception in the above rule. Make sure that the files are spelled exactly like that. The names are case sensitive. Failure to do so will result in the deduction of 5 points. Your main files should include (via means of includes) all the code. No other will be needed to be compilled.

The Makefile makes it easier for us to compile your program and test them. Makes it also easier for you.

You can start with the files QuadraticProbing.h and QuadraticProbing.cpp from the book for the implementation of quadratic probing. Note that the file QuadraticProbing.cpp can be used unchanged for your other implementations, since it only contains functions what have to do
with primes.

So you should use the following files:

QuadraticProbing.h
LinearProbing.h
DoubleProbing.h
QuadraticProbing.cpp

in addition to your two main files.

Here what happens if you compile using the provided files:
-----LINUX TERMINAL----
bash-3.2$ make clean
(rm -f *.o; rm -f CreateAndTestHash; rm -f SpellCheck)
bash-3.2$ make all
make CreateAndTestHash
g++ -g -std=c++11 -Wall -I.   -c CreateAndTestHash.cpp -o CreateAndTestHash.o
g++ -g -std=c++11 -Wall -o ./CreateAndTestHash CreateAndTestHash.o -I.  -L/usr/lib -L/usr/local/lib -lm 
make SpellCheck
g++ -g -std=c++11 -Wall -I.   -c SpellCheck.cpp -o SpellCheck.o
g++ -g -std=c++11 -Wall -o ./SpellCheck SpellCheck.o -I.  -L/usr/lib -L/usr/local/lib -lm 
bash-3.2$ ./CreateAndTestHash document1.txt 
Usage: ./CreateAndTestHash <wordsfilename> <queryfilename> <flag>
bash-3.2$ ./CreateAndTestHash words.txt query_words.txt linear
Input words file is words.txt, and query file is query_words.txt
I will run the linear Hash code 
bash-3.2$ ./CreateAndTestHash words.txt query_words.txt quadratic
Input words file is words.txt, and query file is query_words.txt
I will run the quadratic Hashing code 
bash-3.2$ ./CreateAndTestHash words.txt query_words.txt double
Input words file is words.txt, and query file is query_words.txt
I will run the double Hashing code 
bash-3.2$ ./SpellCheck
Usage: ./SpellCheck <documentfile> <dictionaryfile>
bash-3.2$ ./SpellCheck document1_short.txt wordsEn.txt
I will run ./SpellCheck with parameters document1_short.txt, wordsEn.txt
----END LINUX TERMINAL---

By typing make all everything is compiled. The executables if compiled correctly will be placed in CreateAndTestHash and SpellCheck.
By typing make clean the directory is cleaned from object files and executables. Call this command before you compile.

You can run each program by means of the Makefile if you with, but you can also use the command line option. So for instance if you type

make run1linear

then program CreateAndTestHash will run with option linear, etc.

Finally, you can compile one program individually by just typing make <Program Name>, for example

make SpellCheck

