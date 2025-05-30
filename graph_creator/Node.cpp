#include "Node.h"

// constructors
Node::Node () {
  label = NULL;
}
Node::Node (string* l) {
  label = l;
}

// destructors
Node::~Node () {
  delete label;
}

// getter
string* Node::getLabel() {
  return label;
}
