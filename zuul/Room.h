#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

// room header file
class Room{
 public:
  // constructors
  Room();
  Room(char*);
  // methods
  void getDescription();
  void setExit(int, Room*);
  void showExits();
  bool hasExit (int);
  Room* getExit(int);
  void setItem(char*);
  void showItems();
  bool getItem(char*);
  int amtItems();

 private:
  // private variables
  char* description;
  map<int, Room*> exits;
  vector<char*> items;
};

#endif
