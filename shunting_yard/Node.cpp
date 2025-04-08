#include "Node.h"
#include <cstddef>

using namespace std;

// constructors/destructors
Node::Node () {
  left = NULL;
  right = NULL;
  next = NULL;
  value = '0';
}

Node::Node (char c) {
  value = c;
}

Node::~Node () {
  delete left;
  delete right;
  delete next;
  left = NULL;
  right = NULL;
  next = NULL;
}

// setters
void Node::setLeft (Node* l) { left = l; }
void Node::setRight (Node* r) { right = r; }
void Node::setNext (Node* n) { next = n; }
void Node::setValue (char v) { value = v; }

// getters
Node* Node::getLeft () { return left; }
Node* Node::getRight () { return right; }
Node* Node::getNext () { return next; }
char Node::getValue () { return value; }
