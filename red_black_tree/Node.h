#include <cstddef>

using namespace std;

class Node {
 public:
  // constructors
  Node ();
  Node (int);

  // setters
  void setLeft (Node*);
  void setRight (Node*);
  void setValue (int);
  void setColor (int);

  // getters
  Node* getLeft ();
  Node* getRight ();
  int getValue ();
  int getColor ();
  
 private:
  int value;
  int color;
  Node* left;
  Node* right;
};
