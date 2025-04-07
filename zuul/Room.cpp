#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "Room.h"

using namespace std;

// default constructor
Room::Room() {
  description = new char[80];
}

// room constructor
Room::Room(char* d) {
  description = new char[160];
  strcpy(description, d);
}

// room info
void Room::getDescription() {
  cout << description;
  return;
}

// set exit
void Room::setExit(int d, Room* room) {
  exits[d] = room;
  return;
}

// room exits
void Room::showExits() {
  for (map<int, Room*>::iterator it = exits.begin(); it != exits.end(); it++) {
    if (it->first == 0) cout << "NORTH ";
    else if (it->first == 1) cout << "EAST ";
    else if (it->first == 2) cout << "SOUTH ";
    else if (it->first == 3) cout << "WEST ";
  }
  return;
}

// check if a room has that exit
bool Room::hasExit(int dir)  {
  if (exits.count(dir) > 0) {
    return true;
  }
  return false;
}

// get the room in a certain direction
Room* Room::getExit(int d) {
  return exits[d];
}

// add item to room
void Room::setItem(char* item) {
  items.push_back(item);
  return;
}

// show items in the room
void Room::showItems () {
  for (char* item : items) {
    cout << item << " ";
  }
  return;
}

// get item
bool Room::getItem(char* item) {
  for (vector<char*>::iterator it = items.begin(); it != items.end(); it++) {
    if (strcmp((*it), item) == 0) {
      items.erase(it);
      return true;
    }
  }
  return false;
}

// amount of items in the room
int Room::amtItems() {
  return items.size();
}
