// Jiaqi Luo
// hw4, activityType.h
// this file contains the declaration of the struct info, collection and the
// class activity_type

#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>

const int SIZE = 100;

// this the the declaration of the struct named info which contains all the
// detial information
// of a activity
struct info {
  char *name; // eg. wind surfing
  char *description;
  char *location;        // eg. Portland
  char *gear_requirment; // eg. required, or unrequired
  char *tips;            // some tips for success
  int difficult;         // 1 - no prior knowledge, 5 - requried training
};

// this is the declaration of the class activity_type which contains
// the operations of a activity
class activity_type {
public:
  activity_type();
  ~activity_type();
  // received to_add which is an info struct and save it in this
  // class as the data
  int create(info &to_add);
  // compare the recieved location with that in data, and pass
  // the info struct back if matched
  int retrieve(char location[], info &back);
  // display data in the class
  int display();
  // return the location in the class
  char *get_location();
  // pass the info struct in this class back
  int get_info(info &back);

private:
  info *data;
};

// this is the declaration of the struct collection
// which will be a "node" of a linear linked list of activities
// in the same location
struct collection {
  activity_type data;
  collection *next;
};
