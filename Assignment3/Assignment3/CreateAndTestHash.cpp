/***************************************************************
Title:        CreateAndTestHash.cpp
Author:       Michael Garod
Date Created: 10/24/2015
Class:        Fall 2015, CSCI 335-01, Tues & Fri 12:45pm-2:00pm
Professor:    Ioannis Stamos
Purpose:      Assignment #3
Description:  Using a given hash table, construct a dictionary from a text
              file. Then check if every word in a list is in the dictionary.
              Counts the number of probes to find each of these words.
***************************************************************/
#include "QuadraticProbing.h"
#include "LinearProbing.h"
#include "DoubleProbing.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.makeEmpty();  // Do not have to do it if you pass empty hash table

  ifstream words(words_filename), query(query_filename);
  string line;

  // Inserting into the table
  cout << "\nInserting words into the Hash table...\n";
  while(words >> line)
  {
    if (line.length() > 0)
    {
        hash_table.insert(line);
        //cout << "inserted: " << line << endl;
        //cout << "Elements: " <<hash_table.getNumElements() << endl;
        //cout << "Table size: " << hash_table.getTableSize() << endl;
    }
  }

  // Print Statistics
  printf("\nStatistics for this Hash Table:\n");
  printf("Elements in table: %i\n", hash_table.getNumElements());
  printf("Size of the table: %i\n", hash_table.getTableSize());
  printf("Load Factor: %f\n", hash_table.getLoadFactor());
  printf("Number of Collisions: %d\n", hash_table.getCollisions());

  float avg_num_collisions = static_cast<float>(hash_table.getCollisions()) / static_cast<float>(hash_table.getNumElements());
  printf("Average Number of Collisions: %f\n", avg_num_collisions);

  // Looking at query_words.txt and searching for them in the table
  cout << "\nBeginning seaching for query words:\n";
  while(query >> line)
  {
    if(hash_table.contains(line))
    {
      printf("%s: Found in %i probes\n", line.c_str(), hash_table.getNumProbes(line));
    }
    else
    {
      printf("%s: Not found in %i probes\n", line.c_str(), hash_table.getNumProbes(line));
    }
  }
}

// Sample main for program CreateAndTestHash
int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  cout << "Input words file is " << words_filename << ", and query file is " << query_filename << endl;

  if (param_flag == "linear")
  {
    cout << "I will run the linear Hash code " << endl;
    // ..code for linear Hash
    // ..By calling TestFunctionForHashTable()
    LinearHashTable<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
  }
  
  else if (param_flag == "quadratic")
  {
    cout << "I will run the quadratic Hashing code " << endl;
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
  }

  else if (param_flag == "double")
  {
    cout << "I will run the double Hashing code " << endl;
    // ..code for double Hash
    // ..By calling TestFunctionForHashTable()
    DoubleHashTable<string> double_probing_table;
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
  }

  else {
    cout << "Unknown hash type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }

  return 0;
}
