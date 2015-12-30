#include <iostream>
#include <string>
using namespace std;

// Sample main for program testTrees
int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <string> <string2>" << endl;
    return 0;
  }
  string db_filename(argv[1]);
  string str1(argv[2]);
  string str2(argv[3]);
  cout << "Input file is " << db_filename << " ";
  cout << "String 1 is " << str1 << "   and string 2 is " << str2 << endl;
  return 0;
}
