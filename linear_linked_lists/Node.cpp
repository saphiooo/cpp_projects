#include "Node.h"

using namespace std;

// constructor implementation
// pass in pointer to a Student; returns nothing
Node::Node (Student* s) {
  student = s;
  next = NULL;
}

// optional default constructor
// no arguments; returns nothing
// Node::Node () {
// student = new Student();
// next = NULL;
// }

// destructor
// no arguments; returns nothing
Node::~Node () {
  delete &student;
  next = NULL;
}

// set pointer to the next in the list
// pass in pointer to a Node; returns nothing
void Node::setNext (Node* n) {
  next = n;
}

// get pointer to the next in the list
// no arguments; returns pointer to the Node
Node* Node::getNext () {
  return next;
}

// get Student at this Node
// no arguments; returns pointer to the Student
Student* Node::getStudent() {
  return student;
}
