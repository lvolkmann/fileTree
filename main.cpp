//
// Created on 11/13/18.
//

#include<iostream>
#include "RBTree.h"
using namespace std;

int main() {

    // Initialize root folder

    // Execute operations on the folder

    /*ASSUMPTIONS
     * FILE NAMES MUST BE UNIQUE
     * FILE NAMES CANNOT CONTAIN NUMBERS/SYMBOLS
     */


    //orders the files by name
    RBTree tree;
    tree.insert(5, "quick");
    tree.insert(2, "the");
    tree.insert(4, "fox");
    tree.insert(6, "brown");

    cout << "Inoder Traversal of Created Tree\n";
    tree.inorder();


    return 0;
}
