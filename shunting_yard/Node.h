#ifndef NODE_H
#define NODE_H

using namespace std;

class Node {
 public:
  // constructors
  Node (); 
  Node (char c);
  ~Node (); 
  // getters and setters
  void setLeft (Node* l);
  void setRight (Node* r);
  void setNext (Node* n);
  void setValue (char v);
  Node* getLeft ();
  Node* getRight ();
  Node* getNext ();
  char getValue ();
 private:
  Node* left;
  Node* right;
  Node* next;
  char value;
};

#endif
