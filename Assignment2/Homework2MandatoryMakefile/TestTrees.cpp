#include <iostream>
#include <string>
using namespace std;

// Sample main for program testTrees
int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  string db_filename(argv[1]);
  string query_filename(argv[2]);
  string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and query file is " << query_filename << endl;
  if (param_tree == "BST") {
    cout << "I will run the BST code " << endl;
    // Insert code for testing a BST tree.
    // ...
  } else if (param_tree == "AVL") {
    cout << "I will run the AVL code " << endl;
    // Insert code for testing an AVL tree.
    // ...
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
