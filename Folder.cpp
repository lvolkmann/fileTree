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

    /*

     //Goes to directory
    Folder* CurrentDir = traverseDirectory(path);


    if(CurrentDir -> left == NULL){
    CurrentDir ->left = insert(Folder ->left, folder_name);
    }


    if(CurrentDir -> left == NULL && CurrentDir -> right != NULL){
    CurrentDir ->right = insert(Folder->right, folder_name);
    }

     //still need to figure what to do if both are full

     if(CurrentDir -> left == NULL && CurrentDir -> right == NULL){
     CurrentDir -> left -> left = insert(Folder -> left -> left, folder_name);
     }

    */
}

void Folder::delete_folder(string path, string folder_name)
{
    //will need to have a way to delete all files within as well

}

void Folder::add_file(string path, string file_name, int size)
{
}



list<File> Folder::get_files(string path, string file_name)
{
    return list<File>();
}

void Folder::delete_file(string path, string file_name)
{
}

File Folder::get_file(string path, string file_name) {
    return File();
}
