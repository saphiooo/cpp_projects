#include <iostream>
#include <cstring>
#include <vector>
#include <map>

#include "Room.h"

using namespace std;

int parseCmd (char input[80]);
int parseDir (char input[80]);
void display(Room* room);
void printInventory (vector<char*> inventory);

int main () {
  // intro
  cout << "Zuul!" << endl;
  cout << "You are stuck in Mr. Galbraith's secret lair!" << endl;
  cout << "Collect all the items and escape secretly through the business office." << endl;
  cout << "(The main office has too many watchful eyes.)" << endl;

  cout << "\nThere are five items:" << endl;
  cout << "- COMPUTER - scare off the teachers with your nerdiness." << endl;
  cout << "- CALCULATOR - in case the computer isn't nerdy enough." << endl;
  cout << "- BARBELL - in case you need to resort to violence." << endl;
  cout << "- COSTUME - so the teachers don't know who you are." << endl;
  cout << "- PENCIL - so you still seem like a good student." << endl;
  cout << "\nYour commands are:" << endl;
  cout << "- GO [DIRECTION] - go somewhere." << endl;
  cout << "- GET [ITEM] - get an item." << endl;
  cout << "- DROP [ITEM] - why would you use this?" << endl;
  cout << "- HELP - show this page." << endl;
  cout << "- QUIT - quit, like a loser." << endl;
  cout << endl;
  
  cout << "Good luck!\n" << endl;

  // rooms, exits, and items
  char* lairD = new char[160];
  strcpy(lairD, "Galbraith's secret lair. Robots are whirring. Computers are chirping. Get out while you can.");
  Room* lair = new Room(lairD);
  char* labD = new char[160];
  strcpy(labD, "the computer lab. The sea of computers is daunting.");
  Room* lab = new Room (labD);
  char* computer = new char[80];
  strcpy(computer, "COMPUTER");
  lab->setItem(computer);
  char* oneD = new char[160];
  strcpy(oneD, "one hall. It's very crowded - flying backpack incoming!");
  Room* one = new Room(oneD);
  char* mathD = new char[160];
  strcpy(mathD, "some math classroom. All the nerds are here. They want you to join their calculus club.");
  Room* math = new Room (mathD);
  char* calculator = new char[80];
  strcpy(calculator, "CALCULATOR");
  math->setItem(calculator);
  char* lowerD = new char[160];
  strcpy(lowerD, "the lower commons. The cheer team will use this space for practice soon.");
  Room* lower = new Room (lowerD);
  char* upperD = new char[160];
  strcpy(upperD, "the upper commons. It smells like pizza here.");
  Room* upper = new Room(upperD);
  char* twoD = new char[160];
  strcpy(twoD, "two hall. Nothing exciting here. I guess the wall art is cool.");
  Room* two = new Room(twoD);
  char* auditoriumD = new char[160];
  strcpy(auditoriumD, "the auditorium. It's dark. The curtains are drawn. Are you supposed to be here?");
  Room* auditorium = new Room(auditoriumD);
  char* costume = new char[80];
  strcpy(costume, "COSTUME");
  auditorium->setItem(costume);
  char* gymD = new char[160];
  strcpy(gymD, "the gym. The AC here is terrible, and it smells like decaying socks.");
  Room* gym = new Room(gymD);
  char* barbell = new char[160];
  strcpy(barbell, "BARBELL");
  gym->setItem(barbell);
  char* mainD = new char[160];
  strcpy(mainD, "main hall. The exits here are a little weird.");
  Room* main = new Room(mainD);
  char* awingD = new char[160];
  strcpy(awingD, "A-wing. Keep your voice down, everyone's studying.");
  Room* awing = new Room(awingD);
  char* pencil = new char[80];
  strcpy(pencil, "PENCIL");
  awing->setItem(pencil);
  char* leadershipD = new char[160];
  strcpy(leadershipD, "the leadership room. Who knows what's even in here?");
  Room* leadership = new Room(leadershipD);
  char* communityD = new char[160];
  strcpy(communityD, "the community room. Is that the main office nearby?");
  Room* community = new Room(communityD);
  char* officeD = new char[160];
  strcpy(officeD, "the main office. RUN!!!");
  Room* office = new Room(officeD);
  char* businessD = new char[160];
  strcpy(businessD, "the business office. Congrats on making it here!");
  Room* business = new Room(businessD);

  lair->setExit(1, lab);
  lab->setExit(3, lair);
  lab->setExit(0, one);
  one->setExit(0, lower);
  one->setExit(1, main);
  one->setExit(2, lab);
  one->setExit(3, math);
  math->setExit(1, one);
  lower->setExit(0, two);
  lower->setExit(1, gym);
  lower->setExit(2, one);
  lower->setExit(3, upper);
  upper->setExit(1, lower);
  two->setExit(1, auditorium);
  two->setExit(2, lower);
  auditorium->setExit(3, two);
  gym->setExit(3, lower);
  main->setExit(0, awing);
  main->setExit(1, leadership);
  main->setExit(2, community);
  main->setExit(3, one);
  awing->setExit(3, main);
  leadership->setExit(0, main);
  leadership->setExit(3, community);
  community->setExit(0, main);
  community->setExit(1, leadership);
  community->setExit(2, office);
  office->setExit(0, community);
  office->setExit(1, business);
  business->setExit(3, office);


  // variables
  Room* current = lair;
  bool playing = true;
  bool won = false;
  vector<char*> inventory;

  // game loop
  while ((current != business || inventory.size() < 5) && playing) {
    cout << endl;
    display(current);

    // input
    char command[80];
    cin >> command;
    int cmd = parseCmd(command);
    char info[80];
    if (cmd < 3) {
      cin.ignore();
      cin.get(info, 80);
      cin.get();
    }
    else {
      cin.get();
    }

    int dir;
    if (cmd == 0) { // go to a room
      dir = parseDir(info);
      if (dir == -1) { // direction doesn't exist
	cout << "That is not a direction." << endl;
      }
      else if (current->hasExit(dir) == false) {
	cout << "That exit doesn't exist." << endl;
      }
      else {
	current = current->getExit(dir);
      }     
    }
    else if (cmd == 1) { // pick up an item
      char* itemPtr = new char[80];
      strcpy(itemPtr, info);
      bool removed = current->getItem(info);
      if (removed == false) {
	cout << "Item doesn't exist." << endl;
      }
      else {
	inventory.push_back(itemPtr);
	cout << "Item added to your inventory." << endl;
	cout << "Your inventory: " << endl;
	if (inventory.size() > 0) {
	  printInventory(inventory);
	}
	else {
	  cout << "NONE" << endl;
	}
      }
    }
    else if (cmd == 2) { // drop an item
      char* itemPtr = new char[80];
      strcpy(itemPtr, info);
      bool dropped = false;
      // first search for this in our inventory
      for (vector<char*>::iterator it = inventory.begin(); it != inventory.end();) {
	if (strcmp((*it), info) == 0) {
	  it = inventory.erase(it);
	  dropped = true;
	}
	else {
	  it ++;
	}
      }
      // update room
      if (dropped) {
	current->setItem(itemPtr);
	cout << "Item dropped.\nYour inventory:" << endl;
	if (inventory.size() > 0) {
	  printInventory(inventory);
	}
	else {
	  cout << "NONE" << endl;
	}
      }
      // item not found
      else {
	cout << "You don't have that item." << endl;
      }
    }
    else if (cmd == 3) {
      cout << "\nCollect all the items and escape secretly through the business office." << endl;
      cout << "There are five items:" << endl;
      cout << "- COMPUTER - scare off the teachers with your nerdiness." << endl;
      cout << "- CALCULATOR - in case the computer isn't nerdy enough." << endl;
      cout << "- BARBELL - in case you need to resort to violence." << endl;
      cout << "- COSTUME - so the teachers don't know who you are." << endl;
      cout << "- PENCIL - so you still seem like a good student." << endl;
      cout << "\nYour commands are:" << endl;
      cout << "- GO [DIRECTION] - go somewhere." << endl;
      cout << "- GET [ITEM] - get an item." << endl;
      cout << "- DROP [ITEM] - why would you use this?" << endl;
      cout << "- HELP - show this page." << endl;
      cout << "- QUIT - quit, like a loser." << endl;
      cout << endl;
    }
    else if (cmd == 4) { // quit the game (loser)
      cout << "Sorry to see you go." << endl;
      playing = false;
    }
    else { // weird input
      cout << "Didn't recognize that command." << endl;
    }
  }

  cout << "You made it!" << endl;

  return 0;
}

int parseCmd (char input[80]) {
  if (strcmp(input, "GO") == 0) {
    return 0;
  }
  if (strcmp(input, "GET") == 0) {
    return 1;
  }
  if (strcmp(input, "DROP") == 0) {
    return 2;
  }
  if (strcmp(input, "HELP") == 0) {
    return 3;
  }
  if (strcmp(input, "QUIT") == 0) {
    return 4;
  }
  return -1;
}

int parseDir (char input[80]) {
  if (strcmp(input, "NORTH") == 0) {
    return 0;
  }
  if (strcmp(input, "EAST") == 0) {
    return 1;
  }
  if (strcmp(input, "SOUTH") == 0) {
    return 2;
  }
  if (strcmp(input, "WEST") == 0) {
    return 3;
  }
  return -1;
}

void display (Room* room) {
  cout << "You are in ";
  room->getDescription();
  cout << endl << "There are exits: ";
  room->showExits();
  cout << endl << "There are items: ";
  if (room->amtItems() > 0) {
    room->showItems();
  }
  else {
    cout << "NONE";
  }
  cout << endl;
}

void printInventory (vector<char*> inventory) {
  for (char* item : inventory) {
    cout << item << " ";
  }
  cout << endl;
  return;
}
