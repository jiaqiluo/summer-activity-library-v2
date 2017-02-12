// Jiaqi Luo
// tree.h
// this file contains the declaration of the struct node and the class trss

#include "activityType.h"
#include <fstream>

// this is the declaration of the struct node
struct node {
  activity_type data;
  node *left;
  node *right;
};

// this is the declaration of the class tree
class tree {
public:
  tree();
  ~tree();
  int load_file();             // load data from an external fila
  int add(info &to_add);       // add data into the root
  int display_all();           // display all the data in the tree
  int remove(char location[]); // remove all the roots whit a particular
                               // location
  int retrieve(char location[], collection *&head); // pass all the roots with a
                                                    // particular location in a
                                                    // LLL
  int display(
      char location[]); // display all the roots with a particular location
private:
  node *root;
  int add(node *&root, info &to_add);
  int display_all(node *root);
  int remove_all(node *&root);
  int display(node *root, char location[]);
  int retrieve(node *root, char location[], collection *&head);
  node *remove(node *root, char location[]);
  int get_inorder_successor(node *root, node *&inorder_successor);
};
