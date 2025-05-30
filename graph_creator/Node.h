#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

class Node {
 public:
  Node ();
  Node (string* label);
  ~Node ();
  string* getLabel ();
 private:
  string* label;
};
