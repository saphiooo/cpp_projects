#include <iostream>
#include <cstring>
#include "Media.h"

Media::Media() {
  title = new char[80];
  year = 0;
}

Media::Media(char* newTitle, int newYear, bool newStatus) {
  title = new char[80];
  strcpy(title, newTitle);
  year = newYear;
  status = newStatus;
}

Media::~Media() {
  delete title;
}

char* Media::getTitle() {
  return title;
}

int Media::getYear() {
  return year;
}

char* Media::getDirector() {
  return new char[1];
}

int Media::getDuration() {
  return 0;
}
int Media::getRating() {
  return 0;
}

char* Media::getArtist() {
  return new char[1];
}

char* Media::getPublisher() {
  return new char[1];
}

void Media::display() {
  cout << "" << endl;
}

bool Media::getStatus() {
  return status;
}

void Media::setStatus(bool state) {
  status = state;
}
