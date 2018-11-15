//
// Created on 11/13/18.
//

#include "Folder.h"

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
    Folder* currentDir = this;
    bool folderFound = false;

    // Iterate through path
    for (int i = 0; i < pathVector.size()-1; i++) {
        // Check all folders in current path
        for (auto it = currentDir->childFolders.begin(); it != currentDir->childFolders.end(); it++) {
            // If the name matches, set that as the new folder
            if (pathVector[i] == (*it)->name) {
                currentDir  = *it;
                folderFound = true;
                break;
            }
        }

        if (!folderFound) {
            throw ("Folder not found");
        }
        folderFound = false;
    }

    return currentDir;
}


void Folder::add_folder(string path, string folder_name) {

}

void Folder::delete_folder(string path, string folder_name)
{
}

void Folder::add_file(string path, string file_name, int size)
{
}

File Folder::get_file(string path, string file_name)
{
    return File();
}

list<File> Folder::get_files(string path, string file_name)
{
    return list<File>();
}

void Folder::delete_file(string path, string file_name)
{
}