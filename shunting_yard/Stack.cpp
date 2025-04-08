#include "Stack.h"
#include "Node.h"
#include <cstddef>

using namespace std;

Stack::Stack () {
  head = NULL;
}

Stack::Stack (Node* n) {
  head = n;
}

void Stack::push (Node* n) {
  Node* cur = head;
  if (head == NULL) {
    head = n;
  }
  else {
    while (cur->getNext() != NULL) {
      cur = cur->getNext();
    }
    cur->setNext(n);
  }
  return;
}

Node* Stack::pop () {
  Node* prev = head;
  Node* cur = head;
  if (head == NULL) {
    return NULL;
  }
  else if (head->getNext() == NULL) {
    head = NULL;
    return cur;
  }
  else {
    cur = cur->getNext();
    while (cur->getNext() != NULL) {
      cur = cur->getNext();
      prev = prev->getNext();
    }
    prev->setNext(NULL);
    return cur;
  }
}

Node* Stack::peek () {
  Node* cur = head;
  if (head == NULL) {
    return NULL;
  }
  else {
    while (cur->getNext() != NULL) {
      cur = cur->getNext();
    }
    return cur;
  }
}
  
// getter
Node* Stack::getHead () {
  return head;
}
