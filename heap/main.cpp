#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void addNum (int heap[101], int &heapSize, int x);
void add (int heap[101], int &heapSize, bool &added);
void swap (int heap[101], int i_x, int i_y);
void remove (int heap[101], int &heapSize, bool &added);
void removeAll (int heap[101], int &heapSize, bool &added);
void display (int heap[101], int i, int indent, bool added);
void printCmds ();

int main () {
  int heap [101], heapSize = 0;
  for (int i = 0; i < 101; i++) { heap[i] = 0; }
  cout << "Beginning the heap program." << endl << endl;

  // central management stuff
  bool isRunning = true, added = false;
  string cmd;

  // main loop
  while (isRunning) {
    printCmds ();
    getline (cin, cmd);
    cout << endl;
    if (cmd == "ADD") { add (heap, heapSize, added); }
    else if (cmd == "DELETE") { remove (heap, heapSize, added); }
    else if (cmd == "DELETEALL") { removeAll (heap, heapSize, added); }
    else if (cmd == "DISPLAY") { display (heap, 1, 0, added); }
    else if (cmd == "QUIT") { isRunning = false; cout << "Sorry to see you go.";}
    else { cout << "Huh?" << endl; }
    cout << endl;
  }

  return 0;
}


// 1: ADD
// addNum: adds a single number
void addNum (int heap[101], int &heapSize, int x) {
  // add to first empty space
  int i = heapSize + 1;
  heap[i] = x; // one-based indexing
  
  // move up the tree
  while (heap[i] > heap[i/2] && i != 1) {
    swap (heap, i, i/2);
    i /= 2;
  }
  
  // update heap size
  heapSize ++;
  return;
}

// add: main add function
void add (int heap[101], int &heapSize, bool &added) {
  cout << "Add numbers from file (F) or standard input/output (C)?" << endl;
  char input; cin >> input; cin.get();
  int h = heapSize; // initial heap size

  // file input
  if (input == 'F') {
    string fname;
    cout << "Name of file? ";
    getline (cin, fname);
    ifstream fin (fname);
    int x;
    cout << "Reading... ";
    while (fin >> x) {
      addNum (heap, heapSize, x);
    }
    fin.close();
    if (heap[h + 1] != 0) {
      added = true;
      cout << endl << "Done." << endl;
    }
    else {
      cout << endl << "Error reading file." << endl;
    }
  }
  
  // standard input
  else if (input == 'C') {
    int n, x;
    cout << "How many numbers? ";
    cin >> n; cin.get();
    cout << endl;
    cout << "Reading... ";
    for (int i = h; i < h + n; i++) {
      cin >> x;
      addNum (heap, heapSize, x);
    }
    cin.get();
    added = true;
    cout << endl << "Done." << endl;    
  }

  // bad input
  else { cout << "I don't know what you mean." << endl; }

  return;
}

// 2: DELETE
void remove (int heap[101], int &heapSize, bool &added) {
  if (!added || heap[1] == 0) return;
  
  // output root
  cout << heap[1] << endl;

  // move bottom-most element to the top and remove the original root
  heap[1] = 0;
  swap(heap, heapSize, 1);
  heapSize --;

  // move down the tree
  int i = 1;
  // empty values have 0, which are automatically less than the current number
  while (heap[i * 2] > heap[i] || heap[i * 2 + 1] > heap[i]) {
    if (heap[i * 2] > heap[i * 2 + 1]) {
      swap(heap, i, i * 2);
      i *= 2;
    }
    else {
      swap(heap, i, i * 2 + 1);
      i *= 2; i++;
    }
  }

  if (heap[1] == 0) { added = false; }

  return;
}

// 3: DELETE ALL
void removeAll (int heap[101], int &heapSize, bool &added) {
  if (!added || heap[1] == 0) return;
  while (heap[1] != 0) {
    remove (heap, heapSize, added);
  }
  added = false;
  return;
}

// 4: DISPLAY
// display: nicely prints the tree
void display (int heap[101], int i, int indent, bool added) {
  if (!added || heap[i] == 0) return;
  display(heap, i * 2 + 1, indent + 1, added);
  for (int i = 0; i < indent; i++) { cout << "    "; }
  cout << heap[i] << endl;
  display(heap, i * 2, indent + 1, added);
  return;
}

// HELPER FUNCTIONS

// swap: in a heap, swaps the element at index i_x for the element at index i_y
void swap (int heap[101], int i_x, int i_y) {
  int temp = heap[i_x];
  heap[i_x] = heap[i_y];
  heap[i_y] = temp;
  return;
}

// printCmds: prints available commands for the user
void printCmds () {
  cout << "Your commands:" << endl;
  cout << "- ADD -- add numbers to the heap" << endl;
  cout << "- DELETE -- delete the maximum of the heap" << endl;
  cout << "- DELETEALL -- delete everything in the heap" << endl;
  cout << "- DISPLAY -- display the heap" << endl;
  cout << "- QUIT -- quit the program" << endl << endl;
  return;
}
