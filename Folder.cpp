//
// Created on 11/13/18.
//

#include "Folder.h"

vector<std::string> parsePath(string path) {
    std::vector<std::string> result;
    std::stringstream ss(path);
    std::string folder;

    while(std::getline(ss, folder, '/') {
        result.push_back(folder);
    }
    return result;
}


void Folder::add_folder(string path, string folder_name) {
//    vector<std::string> pathVector = parsePath(path);
//    int pathVectorInc = 0;
//
//    for (list<Folder*>::iterator it; it != childFolders.end(); it++) {
//        // while you're not in the right folder to add to
//        while (pathVectorInc < pathVector.size()) {
//            // Locate folder in root's list of folders
//            if (pathVector[0] == (*it)->name) {
//
//            } else {
//                // Create Folder and child folders
//            }
//        }
//    }


}