#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Node.h"

using namespace std;

vector<int> parseInput ();
void add (Node* &root, vector<int> nums);
void insert (Node* cur, int n);
void remove (Node* &root);
void search (Node* root);
void display (Node* cur, int indent);

int main () {
  // variables
  Node* root = new Node();
  bool isRunning = true;

  while (isRunning) {
    // print commands
    cout << endl << "Commands:" << endl;
    cout << "ADD -- add numbers" << endl;
    cout << "REMOVE -- remove numbers" << endl;
    cout << "SEARCH -- search for a number" << endl;
    cout << "PRINT -- display tree" << endl;
    cout << "QUIT -- quit the program" << endl << endl;

    // user interaction
    string input;
    getline (cin, input);
    if (input == "QUIT") { isRunning = false; }
    else if (input == "ADD") {
      vector<int> nums = parseInput();
      add (root, nums);
    }
    else if (input == "REMOVE") {
      remove (root);
    }
    else if (input == "SEARCH") {
      search (root);
    }
    else if (input == "PRINT") {
      display (root, 0);
    }
    else { cout << "Bad input!" << endl; }
    
  }

  return 0;
}

// read in input to be added
vector<int> parseInput () {
  cout << "File or console input? (F/C) ";
  string input;
  getline (cin, input);
  vector<int> nums;
  
  // file input
  if (input == "F") {
    string fname;
    cout << "Name of file? ";
    getline (cin, fname);
    ifstream fin (fname);
    int x; cout << "Reading...";
    while (fin >> x) {
      nums.push_back(x);
    }
    fin.close();
    cout << endl << "Done." << endl;
  }

  // console input
  else if (input == "C") {
    int n, x;
    cout << "How many numbers? ";
    cin >> n; cin.get(); cout << "Reading...";
    for (int i = 0; i < n; i++) {
      cin >> x; nums.push_back(x);
    }
    cin.get();
    cout << "Done." << endl;
  }
  else { cout << "Bad input!" << endl; }

  return nums;
}

// for all the numbers to be added, insert them into the tree
void add (Node* &root, vector<int> nums) {
  for (int i : nums) { insert (root, i); }
  return;
}

// insert a node into the tree
void insert (Node* cur, int n) {
  if (cur->getValue() == 0) { cur->setValue(n); } // no value here
  else if (n <= cur->getValue()) {
    if (cur->getLeft() != NULL) { insert (cur->getLeft(), n); }
    else { cur->setLeft (new Node(n)); }
  }
  else if (n > cur->getValue()) {
    if (cur->getRight() != NULL) { insert (cur->getRight(), n); }
    else { cur->setRight (new Node(n)); }
  }
  return;
}

// remove a node from the tree
void remove (Node* &root) {
  cout << "Which node?" << endl;
  int v; cin >> v; cin.get();

  // find the node
  Node* prev = root;
  Node* cur = root;
  while (cur->getValue() != v) {
    if (cur->getValue() > v) {
      if (cur->getLeft() != NULL) {
	prev = cur;
	cur = cur->getLeft();
      }
      else { cout << "Node doesn't exist." << endl; return; }
    }
    else if (cur->getValue() < v) {
      if (cur->getRight() != NULL) {
	prev = cur;
	cur = cur->getRight();
      }
      else { cout << "Node doesn't exist." << endl; return; }
    }
  }

  // zero-child deletion
  int numChildren = 0;
  if (cur->getLeft() != NULL) { numChildren ++; }
  if (cur->getRight() != NULL) { numChildren ++; }
  bool toTheRight = prev->getRight() == cur;

  /* DEBUG COUTS 
  cout << "NUMCHILDREN: " << numChildren << endl;
  cout << "TOTHERIGHT: " << toTheRight << endl;
  cout << "VALUE OF PREV: " << prev->getValue() << endl;
  cout << "VALUE OF CUR: " << cur->getValue() << endl;
  */
  
  if (numChildren == 0) {
    // remove the head
    if (cur == root) { root = new Node(); }
    // cur is to the right of prev
    if (toTheRight) { prev->setRight (NULL); }
    // cur is to the left of prev
    else { prev->setLeft (NULL); }
    // do I need to delete the node or smth here?
  }
  else if (numChildren == 1) {
    // get the child node
    Node* child = cur->getRight();
    if (cur->getLeft() != NULL) { child = cur->getLeft(); }
    // remove the head
    if (cur == root) { root = child; }
    // cur is to the right of prev
    else if (toTheRight) { prev->setRight(child); }
    // cur is to the left of prev
    else { prev->setLeft(child); }      
  }
  else if (numChildren == 2) {
    // get the target node
    Node* prevTarget = cur;
    Node* target = cur->getRight();
    while (target->getLeft() != NULL) { prevTarget = target; target = target->getLeft(); }
    // sub in successor's value
    int temp = target->getValue();
    int old = cur->getValue();
    cur->setValue (temp);
    // delete original successor node
    // one child deletion
    if (target->getRight() != NULL) { prevTarget->setRight (target->getRight()); }
    // or zero child deletion
    else if (prevTarget->getRight() == target) { prevTarget->setRight (NULL); } 
    else { prevTarget->setLeft (NULL); }
  }
  else { cout << "Error." << endl; return; }
  cout << "Done." << endl;
  return;
}

// search for a node in the tree
void search (Node* root) {
  cout << "What node?" << endl;
  int v; cin >> v; cin.get();
  Node* cur = root;
  while (cur != NULL && cur->getValue() != v) {
    if (cur->getValue() < v) { cur = cur->getRight(); }
    else { cur = cur->getLeft(); }
  }
  if (cur == NULL) { cout << "No, this node doesn't exist." << endl; }
  else { cout << "Yes, the node exists." << endl; }
  return;
}
  

// display the tree recursively
void display (Node* cur, int indent) {
  if (cur == NULL) return; 
  display (cur->getRight(), indent + 1);
  for (int i = 0; i < indent; i++) { cout << "    "; }
  if (cur->getValue() == 0) { cout << endl; }
  else { cout << cur->getValue() << endl; }
  display (cur->getLeft(), indent + 1);
  return;
}
