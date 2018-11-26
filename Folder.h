//
// Created on 11/13/18.
//

#ifndef FILETREE_FOLDER_H
#define FILETREE_FOLDER_H

#include<string>
#include<list>
#include<vector>
#include "RBTree.h"

using namespace std;

//Folder class
class Folder {
public:
    list<Folder*> childFolders;
    RBTree childFiles;
    string name;
    int size;

    Folder(string name);
    Folder* traverseDirectory(string path);
    void add_folder(string path, string folder_name);
    void delete_folder(string path);
    void add_file(string path, string file_name, int size);
    Node get_file(string path, string file_name);
    list<Node> get_files(string path);
    void delete_file(string path, string file_name);
};


#endif //FILETREE_FOLDER_H
