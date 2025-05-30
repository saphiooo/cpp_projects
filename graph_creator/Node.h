#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

class Node {
 public:
  // constructors
  Node ();
  Node (string* label);
  // destructor
  ~Node ();
  // getter
  string* getLabel ();
 private:
  string* label;
};
