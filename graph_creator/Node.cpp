#include "Node.h"

Node::Node () {
  label = NULL;
}

Node::Node (string* l) {
  label = l;
}

Node::~Node () {
  delete label;
}

string* Node::getLabel() {
  return label;
}
