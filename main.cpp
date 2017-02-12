// Jiaqi Luo
// hw4, main.cpp
// this file contains the main function

#include "Tree.h"
using namespace std;

int main() {
  tree test;
  test.load_file();
  test.display_all();

  cout << "\n****display()********" << endl;
  char location[SIZE];
  cout << "where do you want to display:";
  cin.get(location, SIZE, '\n');
  cin.ignore(SIZE, '\n');
  test.display(location);

  cout << "\n****retrieve()********" << endl;
  char location2[SIZE];
  collection *head = NULL;
  cout << "enter the location for retrieve:";
  cin.get(location2, SIZE, '\n');
  cin.ignore(SIZE, '\n');
  test.retrieve(location2, head);
  collection *temp = head;
  while (temp != NULL) {
    temp->data.display();
    temp = temp->next;
  }

  cout << "\n*****remove*******" << endl;
  cout << "enter location to remove:";
  char location3[SIZE];
  cin.get(location3, SIZE, '\n');
  cin.ignore(SIZE, '\n');
  test.remove(location3);
  test.display_all();
  return 0;
}
