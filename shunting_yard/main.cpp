#include <iostream>
#include <string>
#include <vector>
#include "Stack.h"
#include "Queue.h"
#include "Node.h"

using namespace std;

// FUNCTION PROTOTYPES
void parseToken (Stack* &expressionTree);
void toPostfix (vector<char> tokens, Stack* &expressionTree);
void createExpressionTree (Queue* &outputQueue, Stack* &expressionTree);
void printPostfix (Node* cur);
void printPrefix (Node* cur);
void printInfix (Node* cur);
void printCmds ();
void outputTree (Stack* &expressionTree);
int classifyToken (char c);
void treeDisplay (Stack* &expressionTree);


// SHUNTING YARD ALGORITHM FUNCTIONS

// parse input
void parseTokens (Stack* &expressionTree) {
  cout << "Enter an expression in infix: ";
  string input;
  getline (cin, input);
  // process tokens
  vector<char> tokens;
  for (int i = 0; i < input.size(); i++) {
    if (input[i] == *(" ")) { continue; }
    tokens.push_back(input[i]);
  }
  
  // translate to postfix
  toPostfix(tokens, expressionTree);
  return;
}

// after parsing tokens, translate to postfix notation
void toPostfix (vector<char> tokens, Stack* &expressionTree) {
  vector<char> postfix;
  Stack* operatorStack = new Stack(NULL);
  Queue* outputQueue = new Queue(NULL);
  
  for (int i = 0; i < tokens.size(); i++) {
    int precedence = classifyToken (tokens[i]);

    // number
    if (precedence == 0) {
      outputQueue->enqueue(new Node(tokens[i]));
    }

    // operator
    else if (precedence >= 1 && precedence <= 3) {
      Node* op = operatorStack->peek();
      if (op != NULL) {
	while (op != NULL && op->getValue() != '(' &&
	       ((classifyToken (op->getValue()) > precedence) ||
	       ((classifyToken (op->getValue()) == precedence) &&
		 precedence != 3))) {
	  op = operatorStack->pop();
	  outputQueue->enqueue(op);
	  op = operatorStack->peek();
	}
      }
      // push operator to the stack
      operatorStack->push(new Node(tokens[i]));
    }
    
    // parentheses
    else if (precedence == 4) {
      // left parentheses
      if (tokens[i] == '(') {
	operatorStack->push(new Node(tokens[i]));
      }
      // right parentheses
      else {
	Node* op = operatorStack->pop();
	while (op != NULL && op->getValue() != '(') {
	  outputQueue->enqueue(op);
	  op = operatorStack->pop();
	}
	// stop once bad input is reached or matching parentheses are found
	if (op == NULL) { cout << "Bad input!" << endl; return; }
	else if (op->getValue() == '(') { continue; }
      }
    }
    
    // bad input
    else { cout << "Bad input!" << endl; return; }
  }

  cout << "Done." << endl;

  // clean up operator stack
  Node* op = operatorStack->pop();
  while (op != NULL && op->getValue() != '(') {
    outputQueue->enqueue(op);
    op = operatorStack->pop();
  }

  cout << "POSTFIX EXPRESSION: ";
  Node* cur = outputQueue->getHead();
  while (cur!=NULL) { cout << cur->getValue() << " "; cur = cur->getNext(); } cout << endl;

  // create expression tree
  createExpressionTree (outputQueue, expressionTree);
  
  return;
}

// after translating to postfix, create the expression tree
void createExpressionTree (Queue* &outputQueue, Stack* &expressionTree) {
  Node* op = outputQueue->dequeue();
  while (op != NULL) {
    // number
    if (classifyToken (op->getValue()) == 0) { expressionTree->push(new Node(op->getValue())); }

    // operator
    else {
      Node* r = expressionTree->pop();
      Node* l = expressionTree->pop();
      if (r == NULL || l == NULL) { cout << "Bad input!" << endl; return; }
      Node* o = new Node(op->getValue());
      o->setLeft (l);
      o->setRight (r);
      expressionTree->push(o);
    }

    op = outputQueue->dequeue();
  }

  cout << "EXPRESSION TREE:" << endl;
  treeDisplay (expressionTree);
  
  return;
}


// EXPRESSION TREE FUNCTIONS
// display
void display (Node* cur, int indent) {
  if (cur == NULL) return;
  display(cur->getRight(), indent + 1);
  for (int i = 0; i < indent; i++) { cout << "    "; }
  cout << cur->getValue() << endl;
  display(cur->getLeft(), indent + 1);
  return;
}

// to be honest, this function isn't necessary anymore
// I needed to see everything on the stack while debugging,
// so that's why it exists. I'm too lazy to change it
void treeDisplay (Stack* &expressionTree) {
  Node* cur = expressionTree->getHead();
  while (cur != NULL) {
    display (cur, 0); // BUG
    cur = cur->getNext();
  }
  return;
}

// print postfix recursively
void printPostfix (Node* cur) {
  if (cur->getLeft() != NULL && cur->getRight() != NULL) {
    printPostfix(cur->getLeft());
    printPostfix(cur->getRight());
  }
  cout << cur->getValue() << " ";
  return;
}

// print prefix recursively
void printPrefix (Node* cur) {
  cout << cur->getValue() << " ";
  if (cur->getLeft() != NULL && cur->getRight() != NULL) {
    printPrefix(cur->getLeft());
    printPrefix(cur->getRight());
  }
  return;
}

// print infix recursively
void printInfix (Node* cur) {
  if (classifyToken (cur->getValue()) == 0) { cout << cur->getValue() << " "; }
  else {
    if (cur->getLeft() != NULL && cur->getRight() != NULL) {
      cout << "( ";
      printInfix(cur->getLeft());
      cout << cur->getValue() << " ";
      printInfix(cur -> getRight());
      cout << ") ";
    }
  }
  return;    
}

// output expression tree
void outputTree (Stack* &expressionTree) {
  if (expressionTree->getHead() == NULL) {
    cout << "There's nothing here!";
    return;
  }
  cout << "What notation? (PREFIX/POSTFIX/INFIX)" << endl;
  string input;
  getline (cin, input);
  // process command
  if (input == "PREFIX") { printPrefix (expressionTree->peek()); cout << endl; }
  else if (input == "POSTFIX") { printPostfix (expressionTree->peek()); cout << endl; }
  else if (input == "INFIX") { printInfix (expressionTree->peek()); cout << endl; }
  else { cout << "Bad input!" << endl; }
  return;
}


// HELPER FUNCTIONS
// print commands
void printCmds () {
  cout << endl << "Commands:" << endl;
  cout << "INPUT -- input new expression" << endl;
  cout << "OUTPUT -- output expression in prefix/postfix/infix" << endl;
  cout << "QUIT -- quit the program" << endl << endl;
}

// classify as a number or operator
int classifyToken (char c) {
  // number
  if (c >= 48 && c <= 57) { return 0; }
  // left-associative operator - A/S (precedence 1)
  else if (c == '-' || c == '+') { return 1; }
  // left-associative operator - M/D (precedence 2)
  else if (c == '*' || c == '/') { return 2; }
  // right-associative operator
  else if (c == '^') { return 3; }
  // parentheses
  else if (c == '(' || c == ')') { return 4; }
  // bad input
  return -1;
}

// MAIN LOOP
int main () {
  // main variables
  bool isRunning = true;
  Stack* expressionTree = new Stack(NULL);
  
  while (isRunning) {
    // user stuff
    printCmds();
    string input;
    getline (cin, input);
    // process command
    // QUIT
    if (input == "QUIT") { isRunning = false; }
    // INPUT
    else if (input == "INPUT") {
      expressionTree = new Stack(NULL);
      parseTokens(expressionTree);
    }
    // OUTPUT
    else if (input == "OUTPUT") { outputTree(expressionTree); }
    else { cout << "Bad input!" << endl; }
  }
  return 0;
}
