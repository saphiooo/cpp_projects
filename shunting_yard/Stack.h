#ifndef STACK_H
#define STACK_H

#include "Node.h"

using namespace std;

class Stack {
 public:
  // constructors
  Stack ();
  Stack (Node* n);
  // stack functions
  void push (Node* n);
  Node* pop ();
  Node* peek ();
  // getter
  Node* getHead ();
 private:
  Node* head;
};

#endif
