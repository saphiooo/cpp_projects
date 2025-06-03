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
void remove (Node* &root, int n);
void destroy (Node* &root, Node* n, int c);
void destroyHelper (Node* &root, Node* x);
void read (Node* &root);
void print (Node* cur, int indent);
void transplant (Node* &root, Node* a, Node* b);

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

    // do command
    if (input == "ADD") {
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
      remove (root, n);
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
  return;
}

// find where to insert the node with the BST algorithm
// this differs from the SEARCH function in that find returns the parent of the node
// and search returns the node, which, yeah, I agree, should be refactored
// into a singular function, but I don't wanna. :P
Node* find (Node* root, int n) {
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

  Node* g;
  Node* u;
  
  // all the cases that might cause segfault errors:
  while (n && n->getParent() && n->getParent()->getColor() != 0) {
    // get relatives of node
    g = n->getParent()->getParent(); 
    u = g->getLeft(); 
    if (p->getValue() <= g->getValue()) {
      u = g->getRight();
    }

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
	print(root, 0);
	p->getParent()->setColor(0);
	g->setColor(1);
	leftRotate(root, g);
      }
      
      n = n->getParent();
      if (n) { p = n->getParent(); }
    }
    
    //   case 2b: U is red (recolor needed)
    else if (u->getColor() == 1) {
      g->setColor(1);
      p->setColor(0);
      u->setColor(0);

      n = g;
      if (n) { p = n->getParent(); }
    }

    root->setColor(0);
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
  if (n->getParent() == NULL || n->getParent()->getValue() == 0) {
    root = rc;
    rc->setParent(NULL);
  }
  else if (n->getValue() <= n->getParent()->getValue()) {
    n->getParent()->setLeft(rc);
    rc->setParent(n->getParent());
  }
  else {
    n->getParent()->setRight(rc);
    rc->setParent(n->getParent());
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
  if (n->getParent() == NULL || n->getParent()->getValue() == 0) {
    root = lc;
    lc->setParent(NULL);
  }
  else if (n->getValue() > n->getParent()->getValue()) {
    n->getParent()->setRight(lc);
    lc->setParent(n->getParent());
  }
  else {
    n->getParent()->setLeft(lc);
    lc->setParent(n->getParent());
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

// delete a number from the tree
void remove (Node* &root, int k) {
  Node* n = search (root, k);
  if (n) {
    int c = n->getColor();
    destroy(root, n, c);
    if (root && root->getValue() != 0)
      root->setColor(0);
    else
      root = new Node();
    return;
  }
  else { cout << "Couldn't find that node." << endl; return; }
}

// "remove" the node, causing double blackness
void destroy (Node* &root, Node* n, int c) {
  Node* nCopy = n;
  Node* x;
  if (n->getLeft() && n->getLeft()->getValue() == 0) {
    x = n->getRight();
    transplant(root, n, n->getRight());
  }
  else if (n->getRight() && n->getRight()->getValue() == 0) {
    x = n->getLeft();
    transplant(root, n, n->getLeft());
  }
  else {
    // successor
    nCopy = n->getRight();
    while (nCopy->getLeft()->getValue() != 0) { nCopy = nCopy->getLeft(); }
    c = nCopy->getColor();
    x = nCopy->getRight();

    if (nCopy->getParent() == n) {
      x->setParent(nCopy);
    }
    else {
      transplant(root, nCopy, nCopy->getRight());
      nCopy->setRight(n->getRight());
      nCopy->getRight()->setParent(nCopy);
    }
    
    transplant(root, n, nCopy);
    nCopy->setLeft(n->getLeft());
    nCopy->getLeft()->setParent(nCopy);
    nCopy->setColor(n->getColor());
  }

  delete n;
  
  if (root && c == 0) {
    destroyHelper(root, x);
  }

  return;
}

// fix the messed up tree after deleting the node
void destroyHelper (Node* &root, Node* x) {
  Node* w;
  while (x != root && x->getColor() == 0) {
    if (x->getParent()->getLeft() == x) {
      w = x->getParent()->getRight();
      if (w->getColor() == 1) { 
	w->setColor(0);
	x->getParent()->setColor(1);
	leftRotate(root, x->getParent());
	w = x->getParent()->getRight();
      }
      if (w->getRight()->getColor() == 0 && w->getLeft()->getColor() == 0) {
	w->setColor(1);
	x = x->getParent();
      }
      else {
	if (w->getRight()->getColor() == 0) {
	  w->getLeft()->setColor(0);
	  w->setColor(1);
	  rightRotate(root, w);
	  w = x->getParent()->getRight();
	}
	w->setColor(x->getParent()->getColor());
	x->getParent()->setColor(0);
	w->getRight()->setColor(0);
	leftRotate(root, x->getParent());
	x = root;
      }
    }
    else {
      w = x->getParent()->getLeft();
      if (w->getColor() == 1) {
	w->setColor(0);
	x->getParent()->setColor(1);
	rightRotate(root, x->getParent());
	w = x->getParent()->getLeft();
      }
      if (w->getLeft()->getColor() == 0 && w->getRight()->getColor() == 0) {
	w->setColor(1);
	x = x->getParent();
      }
      else {
	if (w->getLeft()->getColor() == 0) {
	  w->getRight()->setColor(0);
	  w->setColor(1);
	  leftRotate(root, w);
	  w = x->getParent()->getLeft();
	}
	
	w->setColor(x->getParent()->getColor());
	x->getParent()->setColor(0);
	w->getLeft()->setColor(0);
	rightRotate(root, x->getParent());
	x = root;
      }
    }
  }
  x->setColor(0);
}

// transplant two nodes (refactored from earlier code)
void transplant (Node* &root, Node* a, Node* b) {
  if (a == root) { root = b; }
  else if (a == a->getParent()->getRight()) {
    a->getParent()->setRight(b);
  }
  else {
    a->getParent()->setLeft(b);
  }
  b->setParent(a->getParent());
  return;
}

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
  if (cur->getValue() != 0) {
    for (int i = 0; i < indent; i++) { cout << "    "; }
    char c = cur->getColor() == 1 ? 'r' : 'b';
    int l, r, p;
    if (cur->getLeft()) l = cur->getLeft()->getValue();
    if (cur->getRight()) r = cur->getRight()->getValue();
    if (cur->getParent()) p = cur->getParent()->getValue();
    cout << cur->getValue() << ", " << c << endl; // << ", <" << p << ", " << l << ", " << r << ">" << endl; (DEBUGGING)
  }
  print (cur->getLeft(), indent + 1);
  return;
}
