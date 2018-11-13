//
// Created on 11/13/18.
//

#ifndef FILETREE_FOLDER_H
#define FILETREE_FOLDER_H


class Folder {
private:
    List<*Folder> childFolders;
    RBTree<File> childFiles;

};


#endif //FILETREE_FOLDER_H
