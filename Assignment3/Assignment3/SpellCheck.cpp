/***************************************************************
Title:        SpellCheck.cpp
Author:       Michael Garod
Date Created: 10/24/2015
Class:        Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:    Ioannis Stamos
Purpose:      Assignment #3
Description:  Using all words in a dictionary, insert them into a quadratic
              hash table. Then spell check all words in a document. If the doc
              word isn't in the dictionary, try words that can be constructed
              by inserting 1 character, or deleting 1 character, or swapping
              adjacent characters.
***************************************************************/

#include "QuadraticProbing.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <iterator>
using namespace std;

template <typename HashTableType>
void PopulateAndQueryTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  //hash_table.makeEmpty();  // Do not have to do it if you pass empty hash table
  cout << "after makeempty\n";
  ifstream words(words_filename), query(query_filename);
  string line;

  cout << "\nInserting dictionary into the Hash table...\n";
  while(words >> line)
  {
    if (line.length()>0)
    {
      hash_table.insert(line);
    }
  }
  printf("Statistics for this Hash Table:\n");
  printf("Elements in table: %i\n", hash_table.getNumElements());
  printf("Size of the table: %i\n", hash_table.getTableSize());
  printf("Load Factor: %f\n", hash_table.getLoadFactor());

  cout << "\nBeginning seaching for words:\n";
  while(query >> line)
  {
  	/* FORCE LOWERCASE AND REMOVE NON-ALPHA (except apostrophe)
  	/	Since our dictionary is completely lowercase, we force every word we
  	/	encounter in the query file to be completely lowercase. We also
  	/ remove any non-alpha characters. We remove everything after and
    / including apostrophes.
  	*/
  	for(int i = 0; i < line.length(); ++i)
  	{
  		if( isalpha(line[i]) )
  		{
  			line[i] = tolower(line[i]);
  		}
  		else if('\'' == line[i])
  		{ // Remove everything after and including the apostrophe
  		  while(i < line.length())
        {
          line.erase(line.begin() + i);
        }
  		}
  		else
  		{ // If it's non-alpha and not an apostrophe, delete it.
  			line.erase(line.begin() + i);
  			--i;
  		}
  	} // END FORCE LOWERCASE AND REMOVE NON-ALPHA

    // BEGIN SPELL CHECKING
  	cout << "Checking: " << line << endl;
  	if ((line.length() == 0))
  	{ // If line was "1984", then the entire string gets deleted
  		printf("\tSkipping word, likely because it was a number.\n");
  	}
  	else if(!hash_table.contains(line))
    {
    	bool match_found = false;
    	
	    /* BEGIN SWAP ADJACENT
	    /	This is O(n) or specifically O(n-1). Since this is fastest,
	    /	this will be attempted first.
	    */
	    for (int i = 0; !match_found && (i < (line.length()-1)) ; i++)
	    {
	    	// Make the swap, then see if it succeeds.
	    	std::swap(line[i], line[i+1]);
	    	if (hash_table.contains(line))
	    	{
	    		cout << "\tMatch found by swapping!\n";
    			match_found = true;
    			printf("\tDid you mean: \"%s\"\n", line.c_str());
	    	}
	    	else 
	    	{	// If it fails, undo the change, then move on
	    		std::swap(line[i], line[i+1]);
	    	}
	    } // END SWAP ADJACENT


	    /* BEGIN SINGLE DELETE
	    /	This is O(n) where n is the length of the string.
	    */
		for(int i = 0; !match_found && (i < line.length()); i++)
		{
			// Save the deleted char, make the delete
			// then see if it succeeds.
			char c = line[i];
			auto itr = line.begin() + i;
			line.erase(itr);
			
			if(hash_table.contains(line))
    		{
    			cout << "\tMatch found by single delete!\n";
    			match_found = true;
    			printf("\tDid you mean: \"%s\"\n", line.c_str());
    		}
    		else
    		{	// If it fails, undo the change, then move on
    			line.insert(itr, c);
    		}
	    } // END SINGLE DELETE


    	/* BEGIN SINGLE INSERT
    	/	This is the worst case scenario which is O(n) though specifically it is
    	/  O(26*n) where n is the string length. Due to complexity, attempt
      /  this last.
    	*/
		for(auto itr = line.begin(); !match_found && (itr != line.end()+1); advance(itr, 1))
		{
			// At every possible position...

		  	for (char c = 'a'; !match_found && (c <= 'z'); ++c)
		  	{
		  		// ... and using every possible character(26) ...
		  		// ... try inserting the character. See if it succeeds.
	    		line.insert(itr, c);
	    		if(hash_table.contains(line))
	    		{
	    			cout << "\tMatch found by single insert!\n";
	    			match_found = true;
	    			printf("\tDid you mean: \"%s\"\n", line.c_str());
	    		}
	    		else
	    		{	// If it fails, undo the change then move on.
	    			line.erase(itr);
	    		}
	    	}
	    } // END SINGLE INSERT

      // IF NO SUITIABLE MATCH CAN BE FOUND
	    if (!match_found)
	    {
	    	cout << "\tFailure: No suitable match could be found\n";
	    } // END FAIL CASE
    }
    else //if (hash_table.contains(line))
    {
    	printf("Success: \"%s\" found in the Table\n", line.c_str());
    }

    cout << endl;
  }

}
// Sample main for program SpellCheck
int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <documentfile> <dictionaryfile>" << endl;
    return 0;
  }
  string document_filename(argv[1]);
  string dictionary_filename(argv[2]);

  cout << "I will run " << argv[0] << " with parameters " << document_filename << ", " << dictionary_filename << endl;

  HashTable<string> quadratic_probing_table;
  PopulateAndQueryTable(quadratic_probing_table, dictionary_filename, document_filename);

  return 0;
}
