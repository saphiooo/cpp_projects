#include <iostream>
#include <cstring>
#include <vector>
#include "Music.h"
#include "VideoGame.h"
#include "Movie.h"

using namespace std;

// function prototypes
int checkInput(char cmd[80]);
void addMedia(vector<Media*> &media);
vector<Media*> search(vector<Media*> &media);
void destroy(vector<Media*> &media);
void printAll(vector<Media*> &media);

// main functions
int main () {
  vector<Media*> media;
  char command[80];
  bool running = true;
  
  // main loop
  while (running) {
    cout << "\nEnter valid command:" << endl;
    cin.get(command, 80);
    cin.get();
    int cmd = checkInput(command);
    if (cmd == 0) { // add media
      cout << "Add media!" << endl;
      addMedia(media);
    }
    else if (cmd == 1) { // search for media
      cout << "Search for media!" << endl;
      search(media);
    }
    else if (cmd == 2) { // delete media
      cout << "Delete media!" << endl;
      destroy(media);
    }
    else if (cmd == 3) { // quit
      cout << "See ya." << endl;
      running = false;
    }
    else if (cmd == 4) { // print all media (debugging purposes)
      printAll(media);
    }
    else { // weird input
      cout << "Invalid command." << endl;
    }
  }

  return 0;
}

// checks input and maps it to an integer
// this is really not necessary but I like it
int checkInput(char cmd[80]) {
  if (strcmp(cmd, "ADD") == 0)
    return 0;
  else if (strcmp(cmd, "SEARCH") == 0)
    return 1;
  else if (strcmp(cmd, "DELETE") == 0)
    return 2;
  else if (strcmp(cmd, "QUIT") == 0)
    return 3;
  else if (strcmp(cmd, "PRINT") == 0)
    return 4;
  else
    return -1;
}

// add media to the vector
void addMedia (vector<Media*> &media) {
  char* title = new char[80];
  char* publisher = new char[80];
  char* artist = new char[80];
  char* director = new char[80];
  int year;
  int duration;
  int rating;

  // getting data that every child class uses
  cout << "What type of media are you adding? (Music/Videogame/Movie)" << endl;
  char input[80];
  cin.get(input, 80);
  cin.get();
  cout << "What's the title of your media?" << endl;
  cin.get(title, 80);
  cin.get();
  cout << "What year was the media created?" << endl;
  cin >> year;
  cin.get();

  // create a new song
  if (strcmp(input, "Music") == 0) {
    cout << "Who is the artist?" << endl;
    cin.get(artist, 80);
    cin.get();
    cout << "How long is the song?" << endl;
    cin >> duration;
    cin.get();
    cout << "Who published the song?" << endl;
    cin.get(publisher, 80);
    cin.get();
    Media* song = new Music(title, artist, year, duration, publisher, true);
    media.push_back(song);
  }

  // create a new video game
  else if (strcmp(input, "Videogame") == 0) {
    cout << "Who published the video game?" << endl;
    cin.get(publisher, 80);
    cin.get();
    cout << "What's the game's rating?" << endl;
    cin >> rating;
    cin.get();
    Media* game = new VideoGame(title, year, publisher, rating, true);
    media.push_back(game);
  }

  // create a new movie
  else if (strcmp(input, "Movie") == 0) {
    cout << "Who directed the movie?" << endl;
    cin.get(director, 80);
    cin.get();
    cout << "How long is the movie?" << endl;
    cin >> duration;
    cin.get();
    cout << "What is the movie's rating?" << endl;
    cin >> rating;
    cin.get();
    Media* movie = new Movie(title, director, year, duration, rating, true);
    media.push_back(movie);
  }

  // weird input
  else {
    cout << "Don't know what that is." << endl;
  }
  return;
}

// search for media
vector<Media*> search (vector<Media*> &media) {
  vector<Media*> results;
  char input[80];
  int year;
  char title[80];
  
  cout << "\nSearch for title or year? (t/y)" << endl;
  cin.get(input, 80);
  cin.get();

  // search by title
  if (strcmp(input, "t") == 0) {
    cout << "Enter the title:" << endl;
    cin.get(title, 80);
    cin.get();
    cout << "Search results:" << endl;
    for (vector <Media*>::iterator it = media.begin();
	 it != media.end(); it ++) {
      // find relevant media and display
      if (strcmp((*it)->getTitle(), title) == 0) {
	(*it)->display();
	results.push_back(*it);
      }
    }
  }

  // search by year
  else if (strcmp(input, "y") == 0) {
    cout << "Enter the year:" << endl;
    cin >> year;
    cin.get();
    cout << "Search results:" << endl;
    for (vector <Media*>::iterator it = media.begin();
	 it != media.end(); it++) {
      // find relevant media and display
      if (year == (*it)->getYear()) {
	(*it)->display();
	results.push_back(*it);
      }
    }
  }

  // weird input
  else {
    cout << "Don't know what that is." << endl;
  }

  // return results so this can be used in the destroy() function
  return results;
}


// delete media - takes input and deletes the media after searching
void destroy(vector<Media*> &media) {
  cout << "What do you want to delete?" << endl;
  vector<Media*> results = search(media);
  vector<int> toDelete;
  char input[80];

  // marks all relevant media for deletion based on user input
  for (vector <Media*>::iterator it = results.begin();
       it != results.end(); it++) {
    cout << "\nDelete this media? (y/n)" << endl;
    (*it)->display();
    cin.get(input, 80);
    cin.get();
    if (strcmp(input, "y") == 0) {
      (*it)->setStatus(false);
    }
  }

  // deletes it from the original vector
  for (vector <Media*>::iterator it = media.begin();
       it != media.end();) {
    if ((*it)->getStatus() == false) {
      (*it)->~Media(); // destructor
      it = media.erase(it); // remove from vector
    }
    else {
      ++it;
    }
  }

  cout << "Done." << endl;
  return;
}

// print all media stores in the vector (debugging purposes)
void printAll(vector<Media*> &media) {
  for (vector<Media*>::iterator it = media.begin();
       it != media.end(); it++) {
    (*it)->display();
  }
}
