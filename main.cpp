//
// Created on 11/13/18.
//

#include<iostream>
#include "RBTree.h"
#include "Folder.h"
using namespace std;

int main() {


    /*ASSUMPTIONS
     * FILE NAMES ARE CASE SENSITIVE
     */

    Folder* root = new Folder("");

    // ADD FOLDERS AND FILES

    root->add_file("/", "a.txt", 1);
    root->add_file("/", "ab.txt", 2);
    root->add_file("/", "c.txt", 3);

    root->add_folder("/", "child1");
    root->add_folder("/", "child2");
    root->add_folder("/", "child3");

    root->add_file("/child1/", "a.txt", 1);
    root->add_file("/child1/", "b.txt", 2);
    root->add_file("/child1/", "c.txt", 3);

    root->add_file("/child2/", "a.txt", 1);
    root->add_file("/child2/", "b.txt", 2);
    root->add_file("/child2/", "c.txt", 3);

    root->add_file("/child3/", "a.txt", 1);
    root->add_file("/child3/", "b.txt", 2);
    root->add_file("/child3/", "c.txt", 3);

    // GET FILES AND FILE

    cout << endl << "Get files from child1:" << endl;
    list<Node> files = root->get_files("/child1/");
    for(auto it = files.begin(); it != files.end(); it++) {
        cout << it->name << endl;
    }

    cout << endl << "Get files from child2:" << endl;
    files = root->get_files("/child2/");
    for(auto it = files.begin(); it != files.end(); it++) {
        cout << it->name << endl;
    }

    cout << endl << "Get files from child3:" << endl;
    files = root->get_files("/child3/");
    for(auto it = files.begin(); it != files.end(); it++) {
        cout << it->name << endl;
    }

    cout << endl << "Get file from child1" << endl;
    Node tmp = root->get_file("/child1/", "c.txt");
    cout << "File Name: " << tmp.name << endl << endl;

    cout << "Delete /child3/c.txt file" << endl;
    root->delete_file("/child3/", "c.txt");

    cout << "Get files from child3:" << endl;
    files = root->get_files("/child3/");
    for(auto it = files.begin(); it != files.end(); it++) {
        cout << it->name << endl;
    }

    cout << "Delete folder /child2/" << endl;
    root->delete_folder("/child2/");

    cout << "Print root's child folders" << endl;
    for(auto it = root->childFolders.begin(); it != root->childFolders.end(); it++) {
        cout << (*it)->name << ", ";
    }


    return 0;
}
