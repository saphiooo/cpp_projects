#include "Queue.h"
#include "Node.h"
#include <cstddef>

using namespace std;

Queue::Queue () {
  head = NULL;
}

Queue::Queue (Node* n) {
  head = n;
}

// enqueue a node
void Queue::enqueue (Node* n) {
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

// dequeue the first node
Node* Queue::dequeue () {
  Node* cur = head;
  if (head == NULL) { // nothing in the list
    return NULL;
  }
  else if (head->getNext() == NULL) { // head exists, next does not
    head = NULL;
    return cur;
  }
  else { // head and next exist
    head = head->getNext();
    return cur;
  }
}

// getter
Node* Queue::getHead () {
  return head;
}
