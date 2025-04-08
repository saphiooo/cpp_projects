#include <iostream>
#include <cstring>
#include "Movie.h"

Movie::Movie() : Media () {
  director = new char[80];
  duration = 0;
  rating = 0;
}

Movie::Movie (char* newTitle, char* newDirector, int newYear, int newDuration, int newRating, bool newStatus) : Media(newTitle, newYear, newStatus) {
  title = new char[80];
  strcpy(title, newTitle);
  duration = newDuration;
  rating = newRating;
  director = new char[80];
  strcpy(director, newDirector);
}

Movie::~Movie() {
  delete director;
}

char* Movie::getDirector() {
  return director;
}

int Movie::getDuration () {
  return duration;
}

int Movie::getRating () {
  return rating;
}

void Movie::display() {
  cout << "Movie: " << getTitle();
  cout << " -- Director: " << getDirector();
  cout << " -- Duration: " << getDuration();
  cout << " -- Rating: " << getRating();
  cout << " -- Year: " << getYear() << endl;
}
