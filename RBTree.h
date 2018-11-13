//
// Created by caskla on 11/13/18.
//

#ifndef FILETREE_RBTREE_H
#define FILETREE_RBTREE_H

/** C++ implementation for Red-Black Tree Insertion
   This code is adopted from the code provided by
   Dinesh Khandelwal in comments **/

#include <bits/stdc++.h>
using namespace std;

enum Color {RED, BLACK};

struct Node
{
    int data;
    bool color;
    Node *left, *right, *parent;

    // Constructor
    Node(int data)
    {
        this->data = data;
        left = right = parent = NULL;
    }
};

// Class to represent Red-Black Tree
class RBTree
{
private:
    Node *root;
protected:
    void rotateLeft(Node *&, Node *&);
    void rotateRight(Node *&, Node *&);
    void fixViolation(Node *&, Node *&);
public:
    // Constructor
    RBTree() { root = NULL; }
    void insert(const int &n);
    void inorder();
    void levelOrder();
};


#endif //FILETREE_RBTREE_H
