#include <iostream>
#include <cstring>

using namespace std;

// function prototypes
bool isLegalMove (char move[80], int &r, int &c, int board[][3]);
void displayBoard (int board[][3]);
int checkWin (int board[][3], int curPlayer);

// main loop
int main () {

  int winsX = 0, winsO = 0, ties = 0;
  bool isPlaying = true;
  bool won = false;
  char move[80];
  
  // player 1 = X = 0
  // player 2 = O = 1
  // no token there = -1
    
  while (isPlaying) {
    // initialize and fill board
    int board[3][3];
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        board[i][j] = -1;
      }
    }
    int curPlayer = 0;
    won = false;
    
    cout << "Welcome to tic-tac-toe!" << endl;
        
    displayBoard(board);

    while (!won) {
      // enter a move
      if (curPlayer == 0) { cout << "Player X's turn!" << endl; }
      else { cout << "Player O's turn!" << endl; }
      cout << "Enter a move, e.g. a1." << endl;
      
      cin.get(move, 80);
      cin.get();

      // parse move and check if move is legal
      int r, c;
      while (!isLegalMove(move, r, c, board)) {
	if (move[0] == '\0' or move[0] == '\n') {
	  cin.clear();
	  cin.ignore();
	}
	cout << "Enter a legal move, e.g. a1." << endl;
	cin.get(move, 80);
	cin.get();
      }

      // update board
      board[r][c] = curPlayer;
    
      // display board
      displayBoard(board);

      // check for win
      int win = checkWin(board, curPlayer);
      if (win >= 0) {
	won = true;
	if (win == 0) {
	  if (curPlayer == 0) {
	    cout << "Player X won!" << endl;
	    winsX ++;
	  }
	  else {
	    cout << "Player O won!" << endl;
	    winsO ++;
	  }
	}
	else if (win == 1) {
	  cout << "There was a tie." << endl;
	  ties ++;
	}

	// display score
	cout << "Current standings:" << endl;
	cout << "X wins: " << winsX << " -- O wins: " << winsO << " -- Ties: " << ties << endl;

	// play again?
	cout << "Play again? (y/n)" << endl;
	char again[2];
	cin.get(again, 2, '\n');
	cin.get();
	if (again[0] == 'n') {
	  isPlaying = false;
	}
	else {
	  curPlayer = 0;
	  cout << "Starting a new game." << endl;
	}
      }
      else {
	// change player
	curPlayer = (curPlayer + 1) % 2;
      }
    }
  }
  return 0;
}

// other functions
// returns if the inputted move is legal
bool isLegalMove (char move[80], int & r, int & c, int board[][3]) {
  char letter = move[0];
  char number = move[1];

  // check letter
  if (letter != 'a' && letter != 'b' && letter != 'c') {
    cout << "Not a real square." << endl;
    return false;
  }
  else {
    if (letter == 'a') { r = 0; }
    else if (letter == 'b') { r = 1; }
    else { r = 2; }
  }

  // check number
  if (number != '1' && number != '2' && number != '3') {
    cout << "Not a real square." << endl;
    return false;
  }
  else {
    if (number == '1') { c = 0; }
    else if (number == '2') { c = 1; }
    else { c = 2; }
  }

  // check if board position is empty
  if (board[r][c] != -1) {
    cout << "That spot's taken." << endl;
    return false;
  }

  // otherwise return true
  return true;
}

// displaying the board
void displayBoard (int board[][3]) {
  cout << "  1 2 3" << endl;
  char letter = 'a';
  for (int i = 0; i < 3; i++) {
    cout << (char)letter << " ";
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == 0) {
	cout << "X ";
      }
      else if (board[i][j] == 1) {
	cout << "O ";
      }
      else { cout << "  "; }
    }
    cout << endl;
    letter += 1;
  }
}

// checking for wins
// 0 = curPlayer won, 1 = tie, -1 = no win yet
int checkWin (int board[][3], int curPlayer) {  
  // rows
  for (int i = 0; i < 3; i++) {
    if ((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) && (board[i][2] == curPlayer)) {
      return 0;
    }
  }

  // columns
  for (int i = 0; i < 3; i++) {
    if ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]) && (board[2][i] == curPlayer)) {
      return 0;
    }
  }

  // diagonals
  if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) && (board[2][2] == curPlayer)) {
    return 0;
  }
  if ((board[2][0] == board[1][1]) && (board[1][1] == board[0][2]) && (board[0][2] == curPlayer)) {
    return 0;
  }

  // tie
  bool hasEmpty = false;
  
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == -1) {
	hasEmpty = true;
      }
    }
  }

  if (!hasEmpty) { return 1; } // there is a tie if there are no more moves left to play

  return -1;   
}
