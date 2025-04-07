#ifndef NODE_H
#define NODE_H

#include "Student.h"

using namespace std;

// Node class for a linked list of Student objects.

class Node {
 public:
  // constructor/destructor
  Node(Student*);
  // Node(); // default constructor
  ~Node();

  // getters and setters
  void setNext(Node*); // set pointer to the next in the list
  Node* getNext(); // get pointer to the next in the list
  Student* getStudent(); // get the Student at this node

 private:
  Student* student; // Student object
  Node* next; // pointer to the next in the list
};

#endif
