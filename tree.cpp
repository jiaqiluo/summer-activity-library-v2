// Jiaqi Luo
// hw4 tree.cpp
// this file contains all the functions of the class tree

#include "tree.h"
using namespace std;

// constructor
tree::tree() { root = NULL; }

// distructor
tree::~tree() { remove_all(root); }

// this function loads the data from an external file to the tree
// by invoking the add function, and return 1 finally
int tree::load_file() {
  info temp;
  temp.name = new char[SIZE];
  temp.description = new char[SIZE];
  temp.location = new char[SIZE];
  temp.gear_requirment = new char[SIZE];
  temp.tips = new char[SIZE];
  ifstream file_in;
  file_in.open("activity.txt");
  if (file_in) {
    file_in.get(temp.name, SIZE, ';');
    while (!file_in.eof()) {
      file_in.ignore(SIZE, ';');
      file_in.get(temp.description, SIZE, ';');
      file_in.ignore(SIZE, ';');
      file_in.get(temp.location, SIZE, ';');
      file_in.ignore(SIZE, ';');
      file_in.get(temp.gear_requirment, SIZE, ';');
      file_in.ignore(SIZE, ';');
      file_in.get(temp.tips, SIZE, ';');
      file_in.ignore(SIZE, ';');
      file_in >> temp.difficult;
      file_in.ignore(SIZE, '\n');
      add(temp);
      file_in.get(temp.name, SIZE, ';');
    }
    file_in.close();
  }
  return 1;
}

// this function removes all the nodes
// in the tree
int tree::remove_all(node *&root) {
  if (!root)
    return 0;
  remove_all(root->left);
  remove_all(root->right);
  delete root->left;
  delete root->right;
  delete root;
  root->left = NULL;
  root->right = NULL;
  root = NULL;
}

// this fucntion add an new node into
// the tree and insert it on the right
// position by invoking the conresponding
// function
int tree::add(info &to_add) {
  add(root, to_add);
  return 1;
}

/// this fucntion creates a new node containing the
// information from argument
// and insert it on the current position,
int tree::add(node *&root, info &to_add) {
  if (!root) {
    root = new node;
    root->data.create(to_add);
    root->left = NULL;
    root->right = NULL;
    return 1;
  }
  if (strcmp(to_add.location, root->data.get_location()) < 0)
    add(root->left, to_add);
  else
    add(root->right, to_add);
}

// this function display all the nodes in the
// tree by invoking the conresponding function
int tree::display_all() {
  display_all(root);
  return 1;
}

// this function displays all the nodes in
// the tree in order
int tree::display_all(node *root) {
  if (!root)
    return 0;
  display_all(root->left);
  root->data.display();
  display_all(root->right);
}

// this fucntion displays all the nodes which
// have the particular location in the tree
// by invoking the conresponding function
int tree::display(char location[]) {
  display(root, location);
  return 1;
}

// this fucntion displays all the nodes which
// have the particular location in the tree.
int tree::display(node *root, char location[]) {
  if (!root)
    return 0;
  display(root->left, location);
  if (strcmp(location, root->data.get_location()) == 0)
    root->data.display();
  display(root->right, location);
}

// this function receives a location by argument, and
// finds out all the nodes with the particualr location
// and return them as a linear linked list
// by invoking the conresponding function
int tree::retrieve(char location[], collection *&head) {
  retrieve(root, location, head);
  return 1;
}

// this function check through the tree and finds out all
// the nodes which has the particular location and pass the collection
// of those nodes as a linear linked list
int tree::retrieve(node *root, char location[], collection *&head) {
  if (!root)
    return 0;
  info temp;
  if (root->data.retrieve(location, temp) == 1) {
    if (!head) {
      head = new collection;
      head->data.create(temp);
      head->next = NULL;
    } else {
      collection *current = new collection;
      current->data.create(temp);
      current->next = head;
      head = current;
    }
  }
  retrieve(root->left, location, head);
  retrieve(root->right, location, head);
}

// this function finds the inorder successor
// of the root which is the argument and
// pass the inorder successor back as the argument
// return 1 finally
int tree::get_inorder_successor(node *root, node *&inorder_successor) {
  node *parent = root;
  inorder_successor = root->right;
  int is_left_child = 0;
  while (inorder_successor->left) {
    is_left_child = 1;
    parent = inorder_successor;
    inorder_successor = inorder_successor->left;
  }
  if (inorder_successor->right) {

    if (is_left_child == 0)
      parent->right = inorder_successor->right;
  }
  if (is_left_child == 1)
    parent->left = inorder_successor->right;
  return 1;
}

// this function invokes its conresponding function to
// remove all the nodes which contains the particlar
// location passed ny argument
int tree::remove(char location[]) {
  root = remove(root, location);
  return 1;
}

// this function removes all the nodes which location is the same
// as the argument, and it invokes itselfe recursivly.
node *tree::remove(node *root, char location[]) {
  if (!root)
    return NULL;
  if (strcmp(location, root->data.get_location()) < 0)
    root->left = remove(root->left, location);
  root->right = remove(root->right, location);
  if (strcmp(location, root->data.get_location()) == 0) {
    // leaf
    if (!root->left && !root->right)
      return NULL;
    // only left child
    if (root->left && !root->right) {
      node *temp = root->left;
      delete root;
      return temp;
    }
    // only right child
    if (!root->left && root->right) {
      node *temp = root->right;
      delete root;
      return temp;
    }
    // two children
    if (root->left && root->right) {
      node *temp = NULL;
      node *successor = NULL;
      info successor_info;
      if (!root->right->left)
        temp = root->right->right;
      get_inorder_successor(root, successor);
      successor->data.get_info(successor_info);
      root->data.create(successor_info);
      if (temp)
        root->right = temp;
      delete successor;
      return root;
    }
  } else
    return root;
}
