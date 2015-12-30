#include <iostream>
#include <string>
using namespace std;

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
  return 0;
}
