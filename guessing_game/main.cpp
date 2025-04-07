#include <iostream>

using namespace std;

int main () {
  // variables
  int num;
  srand (time(NULL));
  bool isPlaying = true;
  cout << "Welcome to the guessing game." << endl;
    
  // gameplay
  while (isPlaying) {
    // input
    num = rand() % 101;
    // debugging:
    // cout << num << endl;
    int guess;
    int tries = 1;
    cout << "Enter a number between 0 and 100." << endl;
    cin >> guess;

    // guess is incorrect
    while (guess != num) {
      // give appropriate hint
      if (guess > num) {
	cout << "Too high." << endl;
      }
      else if (guess < num) {
	cout << "Too low." << endl;
      }
      cout << "Try again!" << endl;
      // add one to attempts
      tries ++;
      cin >> guess;
    }

    // guess is correct
    if (guess == num) {
      cout << "Correct!" << endl;
      if (tries == 1) {
	cout << "It took you " << tries << " guess. Nice!" << endl;
      }
      else {
	cout << "It took you " << tries << " guesses." << endl;
      }

      // playing again
      cout << "Play again? (y/n)" << endl;
      char again;
      cin >> again;

      if (again == 'n') { isPlaying = false; }
    }
  }

  return 0;
}
