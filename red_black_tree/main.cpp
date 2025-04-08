#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"

using namespace std;

void add (Node* &root, int n);
Node* insert (Node* cur, int n);
void restructure (Node* &root, Node* k);
void read (Node* &root);
void print (Node* root);

int main () {
  cout << "Beginning the Red-Black Tree program." << endl;

  Node* root = new Node();
  root->setColor(0); // root is black
  bool running = true;

  while (running) {
    // commands
    cout << "Your commands are:" << endl;
    cout << "ADD - add a single node" << endl;
    cout << "READ - read nodes from a file" << endl;
    cout << "PRINT - print the tree" << endl;
    cout << "QUIT - quit the program" << endl << endl;

    string input;
    getline (cin, input); cin.get();

    // do command
    if (input == "ADD") {
      cout << "Number to be added?" << endl;
      int n; cin >> n; cin.get();
      add (root, n);
      cout << "Done." << endl;
    }
    else if (input == "READ") { read (root); }
    else if (input == "PRINT") { print (root); }
    else if (input == "QUIT") {
      cout << "Sorry to see you go." << endl;
      running = false;
    }
    else { cout << "Huh?" << endl; }
    cout << endl;
  }

  return 0;
}

// main function for adding a node to the tree
void add (Node* &root, int n) {
  Node* k = insert (root, n);
  restructure (root, k);
  return;
}

// insert a node with the BST algorithm
Node* insert (Node* cur, int n) {
  Node* cur = root;
  if (cur->getValue() == 0) {
    cur->setValue(n);
    cur->setColor(1);
    return cur;
  }
  else if (n <= cur->getValue()) {
    if (cur->getLeft()) { insert (cur->getLeft(), n); }
    else {
      cur->setLeft (new Node(n));
      cur->getLeft()->setColor(1);
      return cur->getLeft();
    }
  }
  else if (n > cur->getValue()) {
    if (cur->getRight()) { insert (cur->getRight(), n); }
    else {
      cur->setRight (new Node(n));
      cur->getRight()->setColor(1);
      return cur->getRight();
    }
  }
  return NULL;
}

// restructure the nodes if needed
void restructure (Node* &root, Node* k) {
  Node* grandparent = root;
  Node* parent = root;
  Node* uncle = NULL;
  Node* cur = root;
  Node* sibling = NULL;
  
  // get the relatives of cur
  while (cur && cur != k) {
    if (cur->getValue() <= k) {
      if (cur->getLeft()) {
	grandparent = parent;
	parent = cur;
	cur = cur->getLeft();
      }
      else { cout << "Something went wrong." << endl; return; }
    }
    else {
      if (cur->getRight()) {
	grandparent = parent;
	parent = cur;
	cur = cur->getRight();
      }
      else { cout << "Something went wrong." << endl; return; }
    }
  }
    
  // case 1: parent of K is black (no restructure needed)
  if (parent->getColor() == 0) { return; }

  // fill in uncle and sibling nodes
  if (parent == grandparent->getLeft()) {
    if (grandparent->getRight()) { uncle = grandparent->getRight(); }
  }
  else {
    if (grandparent->getLeft()) { uncle = grandparent->getLeft(); }
  }
  if (cur == parent->getLeft()) {
    if (parent->getRight()) { sibling = parent->getRight(); }
  }
  else {
    if (parent->getLeft()) { sibling = parent->getLeft(); }
  }
    
  // case 2: parent of K is red (restructure/recolor needed)
  //   case 2a: uncle of K is black or null (restructure needed)
  if (!uncle || uncle->getColor() == 0) {
    // K < parent of K < G
    if (cur->getValue() <= parent->getValue() &&
	parent->getValue() <= grandparent->getValue()) {
      Node* tempG = grandparent;
      grandparent = grandparent->getLeft();
      grandparent->setColor(0);
      grandparent->setRight(tempG);
      grandparent->getRight()->setColor(1);
      grandparent->getRight()->setLeft(sibling);
      grandparent->getRight()->setRight(uncle);
    }
    else if (cur->getValue() > parent->getValue() &&
	     parent->getValue() <= grandparent->getValue()) {
      Node* tempG = grandparent;
      grandparent = grandparent->getLeft()->getRight();
      grandparent->setColor(0);
      grandparent->setLeft(parent);
      grandparent->getLeft()->setLeft(sibling);
      grandparent->getLeft()->setRight(NULL);
      grandparent->setRight(tempG);
      grandparent->getRight()->setColor(1);
      grandparent->getRight()->setRight(uncle);
    }
    else if (cur->getValue() > parent->getValue() &&
	     parent->getValue() > grandparent->getValue()) {
      Node* tempG = grandparent;
      grandparent = grandparent->getRight();
      grandparent->getRight()->setColor(0);
      grandparent->setLeft(tempG);
      grandparent->getLeft()->setColor(1);
      grandparent->getLeft()->setLeft(uncle);
      grandparent->getLeft()->setRight(sibling);
    }
    else if (cur->getValue() <= parent->getValue() &&
	     parent->getValue() > grandparent->getValue()) {
      Node* tempG = grandparent;
      grandparent = grandparent->getRight()->getLeft();
      grandparent->setColor(0);
      grandparent->setRight(parent);
      grandparent->getRight()->setRight(sibling);
      grandparent->getRight()->setLeft(NULL);
      grandparent->setLeft(tempG);
      grandparent->getLeft->setColor(1);
      grandparent->getLeft->setLeft(uncle);
    }
  }
  //   case 2b: sibling of K is red (recolor needed)
  else if (uncle->getColor() == 1) {
    grandparent->setColor(1);
    parent->setColor(0);
    uncle->setColor(0);
    // resolve potential double-red scenario
    restructure (root, grandparent); 
  }
  return;
}

// read numbers from a file
void read (Node* &root) {
  // file info
  cout << "Name of file?" << endl;
  string fname;
  getline (cin, fname); cin.get();

  // open file
  ifstream fin (fname);
  cout << "Reading... ";
  int n;

  while (fin >> x) {
    add (root, n);
  }
  fin.close();
  cout << "Done." << endl;
  
  return;
}

// display the tree horizontally
void print (Node* root, int indent) {
  if (cur == NULL) { return; }
  print (cur->getRight(), indent + 1);
  for (int i = 0; i < indent; i++) { cout << "    "; }
  if (cur->getValue() == 0) { cout << endl; }
  char c = cur->getColor() == 1 ? 'r' : 'b';
  else { cout << cur->getValue() << ", " << c << endl; }
  print (cur->getLeft(), indent + 1);
  return;
}
