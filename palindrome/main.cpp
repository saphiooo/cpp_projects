#include <iostream>
#include <cstring>

using namespace std;

int main () {

  // initialize variables
  char str[80];
  bool isEmptyString = false;
  cout << "Enter a string." << endl;

  cin.get(str, 80, '\n');
  cin.get();

  // removing punctuation
  char strFiltered[80];
  int count = 0;
  int i = 0;
  while (i < 80 && str[i] != '\0') {
    if (isalnum(str[i]) != 0) {
      // is an alphanumeric character (a-z, A-Z, 0-9)
      strFiltered[count] = str[i];
      count++;
    }
    i++;
  }

  // text doesn't have alphanumeric characters
  if (count == 0) { isEmptyString = true; }

  // add back null character
  strFiltered[count] = '\0';

  // change to lowercase
  char strLower[80];
  for (int i = 0; i < 80; i++) {
    if ((int(strFiltered[i]) >= 65) && (int(strFiltered[i]) <= 90)) {
      strLower[i] = int(strFiltered[i]) + 32;
    }
    else {
      strLower[i] = strFiltered[i];
    }
  }
 
  // reverse string
  char strReverse[80];
  int position = 0;
  // we use count, a variable from earlier that also counted
  // the number of chars in the actual string (not just the
  // length of the array)
  for (int i = count - 1; i >= 0; i--) { 
    strReverse[position] = strLower[i];
    position++;
  }

  // add back null character
  strReverse[position] = '\0';

  // compare string and its reverse
  if (strcmp(strLower, strReverse) == 0 and !isEmptyString) {
    cout << "Palindrome." << endl;
  }
  else if (!isEmptyString) {
    cout << "Not a palindrome." << endl;
  }
  else {
    cout << "String is empty or doesn't have alphanumeric characters." << endl;
  }
  
  return 0;
}
