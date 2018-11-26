//
// Created on 11/13/18.
//

#include <sstream>
#include <iostream>
#include "Folder.h"
#include <algorithm>

//constructor
Folder::Folder(string name) {
    this->name = name;
}

//sorts the path by '/' to help with traversal
vector<std::string> parsePath(string path) {
    std::vector<std::string> result;
    std::stringstream ss(path);
    std::string folder;

    while(std::getline(ss, folder, '/')) {
        result.push_back(folder);
    }
    return result;
}

Folder* Folder::traverseDirectory(string path) {
    // Returns the pointer to the folder directory

    vector<std::string> pathVector = parsePath(path);
    int pathVec = pathVector.size();
    Folder* currentDir = this;
    bool folderFound = false;

    // Iterate through path
    for (int i = 1; i < pathVector.size(); i++) {
        // Check all folders in current path
        for (auto it = currentDir->childFolders.begin(); it != currentDir->childFolders.end(); it++) {
            // If the name matches, set that as the new folder
            if (pathVector[i] == (*it)->name) {
                currentDir  = *it;
                folderFound = true;
                break;
            }
        }

        //if (!folderFound) {
        //    throw ("Folder not found");
        //}
        folderFound = false;
    }

    return currentDir;
}

//adds folder in current directory
void Folder::add_folder(string path, string folder_name) {

     //Goes to directory
    Folder* CurrentDir = traverseDirectory(path);

    CurrentDir->childFolders.push_back(new Folder(folder_name));
}

void delete_folder_helper(Folder* folder) {

    // Delete folders within directory
    if (!folder->childFolders.empty()) {
        for (auto it = folder->childFolders.begin(); it != folder->childFolders.end(); it++)
            delete_folder_helper(*it);
    }

    // Delete file tree
    folder->childFiles.clearTree();

    // Delete folder
    delete folder;

}

void Folder::delete_folder(string path) {


    Folder* CurrentDir = traverseDirectory(path);
    string folderna = CurrentDir->name;

    // Handle change in size
    string parentpath = path.substr(0, path.find('/', 0));
    Folder* ParentDir = traverseDirectory(parentpath + "/");
    ParentDir->size -= CurrentDir->size;

    // Remove it from the list
    for (auto it = ParentDir->childFolders.begin(); it != ParentDir->childFolders.end(); it++){
        if ((*it)->name == CurrentDir->name)
            ParentDir->childFolders.erase(it++);
    }

    // Delete folders within directory
    if (!CurrentDir->childFolders.empty()) {
        for (auto it = CurrentDir->childFolders.begin(); it != CurrentDir->childFolders.end(); it++)
            delete_folder_helper(*it);
    }

    // Delete file tree
    CurrentDir->childFiles.clearTree();

    // Delete folder
    delete CurrentDir;
}

void Folder::add_file(string path, string file_name, int size) {
    //follows path to current folder
    Folder* CurrentDir = traverseDirectory(path);

    //insert the file
    CurrentDir->childFiles.insertValue(file_name, size);

    //update parent folder size
    CurrentDir->size += size;
}

list<Node> Folder::get_files(string path) {
    //will search all Folders and files at end of path

    // traverse directory, then return list of files
    Folder* CurrentDir = traverseDirectory(path);

    return CurrentDir->childFiles.getFiles();
}

void Folder::delete_file(string path, string file_name) {
    // traverse directory, get file
    Folder* CurrentDir = traverseDirectory(path);
    Node tmp = CurrentDir->childFiles.getFile(file_name);

    // Handle change in size
    CurrentDir->size -= tmp.size;

    // Delete file
    CurrentDir->childFiles.deleteValue(tmp.name);
}

Node Folder::get_file(string path, string file_name) {
    // traverse directory, then return file
    Folder* CurrentDir = traverseDirectory(path);

    return CurrentDir->childFiles.getFile(file_name);
}
