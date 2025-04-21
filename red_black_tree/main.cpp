 #include <iostream>
#include <fstream>
#include <string>
#include "Node.h"

using namespace std;

void add (Node* &root, int n);
Node* find (Node* root, int n);
void leftRotate (Node* &root, Node* n);
void rightRotate (Node* &root, Node* n);
void insert (Node* &root, Node* p, int n);
Node* search (Node* root, int n);
//void remove (Node* &root, int n);
//void destroy (Node* &root, Node* p, int n);
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
    cout << "ADD - add a node to the tree" << endl;
    cout << "READ - read nodes from a file" << endl;
    cout << "SEARCH - search for a node in the tree" << endl;
    cout << "REMOVE - remove a node from the tree" << endl;
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
    else if (input == "SEARCH") {
      cout << "Number to search?" << endl;
      int n; cin >> n; cin.get();
      Node* k = search (root, n);
      if (k) { cout << "Found." << endl; }
      else { cout << "Node doesn't exist." << endl; }
    }
    else if (input == "REMOVE") {
      cout << "Number to delete?" << endl;
      int n; cin >> n; cin.get();
      //remove (root, n);
      cout << "Done." << endl;
    }
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
  Node* p = find (root, n);
  insert (root, p, n);
  root->setColor(0);
  print(root, 0);
  return;
}

// find where to insert the node with the BST algorithm
// this differs from the SEARCH function in that find returns the parent of the node
// and search returns the node
Node* find (Node* root, int n) {
  cout << "Inserting..." << endl;
  Node* cur = root;
  Node* parent = NULL;
  while (cur && cur->getValue() != 0) {
    parent = cur;
    if (n <= cur->getValue()) {
      cur = cur->getLeft();
    }
    else {
      cur = cur->getRight();
    }
  }
  return parent;
}

// insert the node needed
void insert (Node* &root, Node* p, int k) {
  Node* n = new Node(k);
  n->setParent(p);
  n->setColor(1);

  cout << "Restructuring..." << endl;

  // case 0: N is the root node (parent = NULL)
  if (!p) {
    root = n;
    n->setParent(NULL);
    n->setColor(0);
    return;
  }

  // N's parent exists...
  if (n->getValue() <= p->getValue()) { p->setLeft(n); }
  else { p->setRight(n); }

  // case 1: N's parent is black (no restructure needed)
  if (p->getColor() == 0) { return; }

  // all the cases that might cause segfault errors:
  
  // get relatives of node
  Node* g = n->getParent()->getParent();
  Node* u = g->getLeft();
  if (p->getValue() <= g->getValue()) {
    u = g->getRight();
  }
  Node* s = p->getLeft();
  if (n->getValue() <= p->getValue()) {
    s = p->getRight();
  }

  // REWRITE: changed recursive function to iterative function
  // I kept getting into infinite loops, lol...

  while (n && n->getParent() && n->getParent()->getColor() != 0) {
    // case 2: P is red (restructure/recolor needed)
    //   case 2a: U is black or null (restructure needed)
    // algorithm from https://www.programiz.com/dsa/red-black-tree
    // recoloring info from https://pages.cs.wisc.edu/~cs400/readings/Red-Black-Trees/
    if (!u || u->getColor() == 0) {
      // N <= P <= G
      if (n->getValue() <= p->getValue() && p->getValue() <= g->getValue()) {
	p->setColor(0);
	g->setColor(1);
	rightRotate(root, g);
      }
      // N > P, P <= G
      else if (n->getValue() > p->getValue() && p->getValue() <= g->getValue()) {
	leftRotate(root, p);
	p->getParent()->setColor(0);
	g->setColor(1);
	rightRotate(root, g);
	print(root, 0);
      }
      // N > P > G
      else if (n->getValue() > p->getValue() && p->getValue() > g->getValue()) {
	p->setColor(0);
	g->setColor(1);
	leftRotate(root, g);
      }
      // N <= P, P > G
      else if (n->getValue() <= p->getValue() && p->getValue() > g->getValue()) {
	rightRotate(root, p);
	p->getParent()->setColor(0);
	g->setColor(1);
	leftRotate(root, g);	
      }
    }
    
    //   case 2b: U is red (recolor needed)
    else if (u->getColor() == 1) {
      g->setColor(1);
      p->setColor(0);
      u->setColor(0);
    }

    cout << "n " << n->getValue() << endl;
    cout << "par " << n->getParent()->getValue() << endl;
    cout << "par col " << n->getParent()->getColor() << endl;
  }
  return;
}

// left rotate
void leftRotate (Node* &root, Node* n) {
  Node* rc = n->getRight();
  Node* rclc = rc->getLeft();
  
  n->setRight(rclc);
  if (rclc) {
    rclc->setParent(n);
  }
  if (!n->getParent()) {
    root = rc;
    rc->setParent(NULL);
  }
  else if (n->getValue() <= n->getParent()->getValue()) {
    n->getParent()->setLeft(rc);
  }
  else {
    n->getParent()->setRight(rc);
  }
  rc->setLeft(n);
  n->setParent(rc);
  return;
}

// right rotate
void rightRotate (Node* &root, Node* n) {
  Node* lc = n->getLeft();
  Node* lcrc = lc->getRight();
  n->setLeft(lcrc);
  if (lcrc) {
    lcrc->setParent(n);
  }
  if (n->getParent() == NULL) {
    root = lc;
    lc->setParent(NULL);
  }
  else if (n->getValue() > n->getParent()->getValue()) {
    n->getParent()->setRight(lc);
  }
  else {
    n->getParent()->setLeft(lc);
  }
  lc->setRight(n);
  n->setParent(lc);
  return;
}

// search for a number in the tree
Node* search (Node* root, int n) {
  Node* cur = root;
  while (cur->getValue() != n) {
    if (n < cur->getValue() && cur->getLeft()) { cur = cur->getLeft(); }
    else if (n > cur->getValue() && cur->getRight()) { cur = cur->getRight(); }
    else { return NULL; }
  }
  return cur;
}
/*
// delete a number from the tree
void remove (Node* &root, int n) {
  Node* p = find (root, n);
  destroy (root, p, n);
  root->setColor(0);
  return;
}


void destroy (Node* &root, Node* p, int n) {
  Node* k;
  if (p->getValue() <= n) { k = n->getLeft(); }
  else { k = n->getRight(); }

  Node* s = k->getRight();
  while (s && s->getLeft()) {
    s = s->getLeft();
  }

  
}
*/
// read numbers from a file
void read (Node* &root) {
  // file info
  cout << "Name of file?" << endl;
  string fname;
  getline (cin, fname); 

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
