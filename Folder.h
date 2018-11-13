//
// Created on 11/13/18.
//

#ifndef FILETREE_FOLDER_H
#define FILETREE_FOLDER_H

#include<string>
#include<list>
using namespace std;

struct File {
	string name;
	int size;
};

class Folder {

private:

	string name;
	int size; //in bytes
    list<Folder> childFolders;
    //RBTree<File> childFiles;

public:

	void add_folder(string path, string folder_name);
	void delete_folder(string path, string folder_name);
	void add_file(string path, string file_name, int size);
	File get_file(string path, string file_name);
	list<File> get_files(string path, string file_name);
	void delete_file(string path, string file_name);

};


#endif //FILETREE_FOLDER_H
