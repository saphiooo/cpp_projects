#include <iostream>
#include <cstring>
#include "VideoGame.h"

VideoGame::VideoGame() : Media () {
  publisher = new char[80];
  rating = 0;
}

VideoGame::VideoGame(char* newTitle, int newYear, char* newPublisher, int newRating, bool newStatus) : Media(newTitle, newYear, newStatus) {
  publisher = new char[80];
  strcpy(publisher, newPublisher);
  rating = newRating;
}

VideoGame::~VideoGame () {
  delete publisher;
}

char* VideoGame::getPublisher () {
  return publisher;
}

int VideoGame::getRating () {
  return rating;
}

void VideoGame::display() {
  cout << "Video Game: " << getTitle();
  cout << " -- Publisher: " << getPublisher();
  cout << " -- Rating: " << getRating();
  cout << " -- Year: " << getYear() << endl;
}
