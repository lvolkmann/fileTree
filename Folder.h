//
// Created on 11/13/18.
//

#ifndef FILETREE_FOLDER_H
#define FILETREE_FOLDER_H

#include<string>
#include<list>
#include "RBTree.h" b

using namespace std;



struct File {
	string name;
	int size;

	//pretty sure these are also needed
	File *left, *right, *parent;

	File(int data)
	{
		this->name = name;
		left = right = parent = NULL;
	}

};
class Folder {
public:
    list<Folder*> childFolders;
    RBTree childFiles;
    string name;
    int size;

    Folder* traverseDirectory(string path);
    void add_folder(string path, string folder_name);
    void delete_folder(string path, string folder_name);
    void add_file(string path, string file_name, int size);
    File get_file(string path, string file_name);
    list<File> get_files(string path, string file_name);
    void delete_file(string path, string file_name);

};


#endif //FILETREE_FOLDER_H
