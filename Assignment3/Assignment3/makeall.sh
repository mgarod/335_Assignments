# Title:		makeall.sh
# Author:		Michael Garod
# Date Created:	10/24/2015
# Class:		Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
# Professor:	Ioannis Stamos
# Purpose:		Assignment #3
# Description:	A shell script that will run all programs required for this
#				assignment write all output to appropriately named files.
# Dependencies:	Makefile
# Output files:	c_and_t_hash.txt, shortresults.txt,	shortstats.txt,
#				spellcheck.txt, spellcheckstats.txt
# Run with:		sh makeall.sh
# Note:			This script will clean up objects before, and after running.
#				The output files created are not cleaned at any point in this
#				script. See cleanup.sh to clean these output files.

make clean
make all
printf "Now running LINEAR HASH\n\n" > c_and_t_hash.txt
make run1linear >> c_and_t_hash.txt

printf "\n***************************************************************\n\n" >> c_and_t_hash.txt

printf "Now running QUADRATIC HASH\n\n" >> c_and_t_hash.txt
make run1quadratic >> c_and_t_hash.txt

printf "\n***************************************************************\n\n" >> c_and_t_hash.txt

printf "Now running DOUBLE HASH with R=73\n\n" >> c_and_t_hash.txt
make run1double >> c_and_t_hash.txt

###########################################################################

make run2short > shortresults.txt

printf "Number of failed words:\n" > shortstats.txt
grep 'failure:' shortresults.txt -i -c >> shortstats.txt

printf "\nNumber of words found by swap\n" >> shortstats.txt
grep 'swapping!' shortresults.txt -i -c >> shortstats.txt 

printf "\nNumber of words found by deletion\n" >> shortstats.txt
grep 'delete!' shortresults.txt -i -c >> shortstats.txt 

printf "\nNumber of words found by single insert\n" >> shortstats.txt
grep 'insert!' shortresults.txt -i -c >> shortstats.txt 

printf "\nNumber of words skipped (numeric words)\n" >> shortstats.txt
grep 'skipping word' shortresults.txt -i -c >> shortstats.txt

###########################################################################

make run2 > spellcheck.txt
make clean

printf "Number of failed words:\n" > spellcheckstats.txt
grep 'failure:' spellcheck.txt -i -c >> spellcheckstats.txt

printf "\nNumber of words found by swap\n" >> spellcheckstats.txt
grep 'swapping!' spellcheck.txt -i -c >> spellcheckstats.txt 

printf "\nNumber of words found by deletion\n" >> spellcheckstats.txt
grep 'delete!' spellcheck.txt -i -c >> spellcheckstats.txt 

printf "\nNumber of words found by single insert\n" >> spellcheckstats.txt
grep 'insert!' spellcheck.txt -i -c >> spellcheckstats.txt 

printf "\nNumber of words skipped (numeric words)\n" >> spellcheckstats.txt
grep 'skipping word' spellcheck.txt -i -c >> spellcheckstats.txt