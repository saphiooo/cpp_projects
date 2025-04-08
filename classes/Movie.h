#include <cstring>
#include <iostream>
#include "Media.h"

using namespace std;

class Movie: public Media {
 public:
  Movie();
  Movie(char*, char*, int, int, int, bool);
  virtual ~Movie();
  virtual char* getDirector();
  virtual int getDuration();
  virtual int getRating();
  virtual void display();
 private:
  char* director;
  int duration;
  int rating;
};
