#include <cstring>
#include <iostream>
#include "Media.h"

using namespace std;

class VideoGame : public Media {
 public:
  VideoGame();
  VideoGame(char*, int, char*, int, bool);
  virtual ~VideoGame();
  virtual char* getPublisher();
  virtual int getRating();
  virtual void display();
 private:
  char* publisher;
  int rating;
};
 
