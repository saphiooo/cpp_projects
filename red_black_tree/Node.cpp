#include "Node.h"
#include <cstddef>

using namespace std;

// constructors
Node::Node () {
  left = NULL;
  right = NULL;
  value = 0;
}

Node::Node (int v) {
  left = NULL;
  right = NULL;
  value = v;
}

// setters
void Node::setLeft (Node* l) { left = l; }
void Node::setRight (Node* r) { right = r; }
void Node::setValue (int v) { value = v; }
void Node::setColor (int c) { color = c; }

// getters
Node* Node::getLeft () { return left; }
Node* Node::getRight () { return right; }
int Node::getValue () { return value; }
int Node::getColor () { return color; }
