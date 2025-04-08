#ifndef NODE_H
#define NODE_H

using namespace std;

class Node {
 public:
  Node ();
  Node (int v);
  // getters and setters
  void setLeft (Node* l);
  void setRight (Node* r);
  void setValue (int v);
  Node* getLeft ();
  Node* getRight ();
  int getValue ();
 private:
  Node* left;
  Node* right;
  int value;
};

#endif
