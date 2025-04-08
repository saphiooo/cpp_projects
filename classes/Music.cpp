#include <iostream>
#include <cstring>
#include "Music.h"

Music::Music() : Media() {
  artist = new char[80];
  duration = 0;
  publisher = new char[80];
}

Music::Music(char* newTitle, char* newArtist, int newYear, int newDuration, char* newPublisher, bool newStatus) : Media(newTitle, newYear, newStatus) {
  artist = new char[80];
  strcpy(artist, newArtist);
  duration = newDuration;
  publisher = new char[80];
  strcpy(publisher, newPublisher);
}

Music::~Music() {
  delete artist;
  delete publisher;
}

char* Music::getArtist () {
  return artist;
}

int Music::getDuration () {
  return duration;
}

char* Music::getPublisher () {
  return publisher;
}

void Music::display() {
  cout << "Music: " << getTitle();
  cout << " -- Artist: " << getArtist();
  cout << " -- Duration: " << getDuration();
  cout << " -- Publisher: " << getPublisher();
  cout << " -- Year: " << getYear() << endl;
}
