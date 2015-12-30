/***************************************************************
Title:			README.txt
Author:			Michael Garod
Date Created:	10/24/2015
Class:			Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:		Ioannis Stamos
Purpose:		Assignment #3
Description:	Brief description containing which parts of the assignment were
				completed, bugs encountered, instructions on how to run
				the program, and input/output files necessary or created.
Contents:		The .zip file should contain 16 files:
				1.  cleanup.sh
				2.  CreateAndTestHash.cpp
				3.  document1_short.txt
				4.  document1.txt
				5.  DoubleProbing.h 		*** R=73
				6.  LinearProbing.h
				7.  makeall.sh
				8.  Makefile
				9. QuadraticProbing.cpp
				10. QuadraticProbing.h
				11. query_words.txt
				12. Readme.Makefile.txt
				13. README.txt
				14. SpellCheck.cpp
				15. words.txt
				16. wordsEn.txt
				
***************************************************************/

I. Parts Completed
	- All parts of this assignments were completed

II. Bugs Encountered
	- The string "injunction--and" does not get handled properly by the parser.

III. Run Instructions (see Readme.Makefile.txt for more information)
	- Makefile
		- make all
		- make run1linear
		- make run1quadratic
		- make run1double
		- make run2short
		- make run2
		- make clean
	- Shell Scripts
		- sh makeall.sh
		- sh cleanup.sh

IV. Input/Output Files
	- Input: document1_short.txt, document1.txt, query_words.txt, words.txt,
		wordsEn.txt
	- Output: Only when using the shell scripts 
		- Makefile: None
		- Shell Script: c_and_t_hash.txt, shortresults.txt, shortstats.txt, 	spellcheck.txt,	spellcheckstats.txt

V. Notes
	- The second hash prime number, R, used in DoubleHashTable is 73
	- I have additionally included makeall.sh, a shell script, which
		provides output	for every possible program of this assignment.
		- Usage from the command line: sh makeall.sh
		- Will run all 3 Hash Tables and output all results to c_and_t_hash.txt
		- Will run SpellCheck on document1_short.txt, outputting results to
			shortresults.txt and shortstats.txt
		- Will run SpellCheck on document1.txt, outputting results to
			spellcheck.txt and spellcheckstats.txt
			- These stats files use grep to search for and count words that
				could not be found, number found by swapping, deleting, and
				inserting, and the number of words skipped because they
				contained only numbers and/or punctuation
		- The script makeall.sh will immediately use make clean after
			completion. It will not clean the output text files created.
		- To cleanup the text files created use: sh cleanup.sh
