#ifndef MEDIA_H
#define MEDIA_H

#include <iostream>
#include <cstring>

using namespace std;

class Media {
 public:
  Media ();
  Media (char*, int, bool);
  virtual ~Media ();
  char* getTitle();
  int getYear();
  virtual char* getDirector();
  virtual int getDuration();
  virtual int getRating();
  virtual char* getArtist();
  virtual char* getPublisher();
  virtual void display();
  virtual bool getStatus();
  virtual void setStatus(bool);
 protected:
  char* title;
  int year;
  bool status;
};

#endif
