#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"

using namespace std;

void add (Node* &root, int n);
Node* insert (Node* cur, int n);
void restructure (Node* &root, Node* k);
void read (Node* &root);
void print (Node* cur, int indent);

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
    getline (cin, input); 
    cout << "Your command was: " << input << endl;

    // do command
    if (input == "ADD") {
      cout << "Number to be added?" << endl;
      int n; cin >> n; cin.get();
      add (root, n);
      cout << "Done." << endl;
    }
    else if (input == "READ") { read (root); }
    else if (input == "PRINT") { print (root, 0); }
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
  print(root, 0);
  cout << endl << "k value " << k->getValue() << endl;
  restructure (root, k);
  return;
}

// insert a node with the BST algorithm
Node* insert (Node* cur, int n) {
  cout << "Inserting..." << endl;
  cout << "Cur value: " << cur->getValue() << "  N value: " << n << endl;
  if (cur->getValue() == 0) {
    cur->setValue(n);
    cur->setColor(1);
    return cur;
  }
  else if (n <= cur->getValue()) {
    if (cur->getLeft()) { return insert (cur->getLeft(), n); }
    else {
      cur->setLeft (new Node(n));
      cur->getLeft()->setColor(1);
      cur->getLeft()->setParent(cur);
      return cur->getLeft();
    }
  }
  else if (n > cur->getValue()) {
    if (cur->getRight()) { return insert (cur->getRight(), n); }
    else {
      cur->setRight (new Node(n));
      cur->getRight()->setColor(1);
      cur->getRight()->setParent(cur);
      return cur->getRight();
    }
  }
  return NULL;
}

// restructure the nodes if needed
void restructure (Node* &root, Node* k) {
  cout << "Restructuring..." << endl;
  Node* grandparent;
  Node* parent;
  Node* uncle = NULL;
  Node* sibling = NULL;
  Node* cur = root;

  // get the relatives of cur
  while (cur && cur != k) {
    cout << "Cur: " << cur->getValue() << endl;
    if (cur->getRight()) {
      cout << "cur has a right of " << cur->getRight() << endl;
    }
    cout << "K value " << k->getValue() << endl;
    if (cur->getValue() > k->getValue()) {
      if (cur->getLeft()) { cur = cur->getLeft(); }
      else { cout << "Something went wrong." << endl; return; }
    }
    else {
      if (cur->getRight()) { cur = cur->getRight(); }
      else { cout << "Something went wrong." << endl; return; }
    }
  }

  // fill in parent, grandparent
  parent = cur->getParent();
  if (!parent) { parent = root; }
  grandparent = parent->getParent();
  if (!grandparent) { grandparent = root; }
  
  // case 0: K is the root node (parent = NULL)
  if (k == root) { cout << "ROOT" << endl; cur->setColor(0); return; }
    
  // case 1: parent of K is black (no restructure needed)
  if (parent->getColor() == 0) { cout << "NONE" << endl; return; }

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

  if (uncle) { cout << "UNCLE: " << uncle->getValue() << endl; } else { cout << "NO UNCLE" << endl; }
  if (sibling) { cout << "SIBLING: " << sibling->getValue() << endl; } else { cout << "NO SIBLING" << endl; }
    
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
      Node* tempGG = root;
      if (grandparent->getParent()) { tempGG = grandparent->getParent(); }
      grandparent = grandparent->getRight();
      grandparent->getRight()->setColor(0);
      grandparent->setLeft(tempG);
      grandparent->getLeft()->setColor(1);
      grandparent->getLeft()->setLeft(uncle);
      grandparent->getLeft()->setRight(sibling);
      cout << "GRANDPARENT: " << grandparent << " w/ val " << grandparent->getValue() << endl;
      if (grandparent->getLeft())
	cout << "LEFT: " << grandparent->getLeft() << " w/ val " << grandparent->getLeft()->getValue() << endl;
      if (grandparent->getRight())
	cout << "RIGHT: " << grandparent->getRight() << " w/ val " << grandparent->getRight()->getValue() << endl;
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
      grandparent->getLeft()->setColor(1);
      grandparent->getLeft()->setLeft(uncle);
    }
  }
  //   case 2b: uncle of K is red (recolor needed)
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

  while (fin >> n) {
    add (root, n);
  }
  fin.close();
  cout << "Done." << endl;
  
  return;
}

// display the tree horizontally
void print (Node* cur, int indent) {
  if (cur == NULL) { return; }
  print (cur->getRight(), indent + 1);
  for (int i = 0; i < indent; i++) { cout << "    "; }
  if (cur->getValue() == 0) { cout << endl; }
  else {
    char c = cur->getColor() == 1 ? 'r' : 'b';
    cout << cur->getValue() << ", " << c << endl;
  }
  print (cur->getLeft(), indent + 1);
  return;
}
