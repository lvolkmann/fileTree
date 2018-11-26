//
// Red Black Tree Implementation
//
//#include <bits/stdc++.h>
#include <string>
#include "RBTree.h"
#include <iostream>
using namespace std;
RBTree::RBTree() {
    root = nullptr;
}
int RBTree::getColor(Node *&node) {
    if (node == nullptr)
        return BLACK;
    return node->color;
}
void RBTree::setColor(Node *&node, int color) {
    if (node == nullptr)
        return;
    node->color = color;
}
Node* RBTree::insertBST(Node *&root, Node *&ptr) {
    if (root == nullptr)
        return ptr;
    if (ptr->name < root->name) {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    }
    else if (ptr->name > root->name) {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }
    return root;
}
void RBTree::insertValue(string name, int size) {
    Node *node = new Node(name, size);
    root = insertBST(root, node);
    fixInsertRBTree(node);
}
void RBTree::rotateLeft(Node *&ptr) {
    Node *right_child = ptr->right;
    ptr->right = right_child->left;
    if (ptr->right != nullptr)
        ptr->right->parent = ptr;
    right_child->parent = ptr->parent;
    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;
    right_child->left = ptr;
    ptr->parent = right_child;
}
void RBTree::rotateRight(Node *&ptr) {
    Node *left_child = ptr->left;
    ptr->left = left_child->right;
    if (ptr->left != nullptr)
        ptr->left->parent = ptr;
    left_child->parent = ptr->parent;
    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;
    left_child->right = ptr;
    ptr->parent = left_child;
}
void RBTree::fixInsertRBTree(Node *&ptr) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            }
            else {
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
        else {
            Node *uncle = grandparent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            }
            else {
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);
}

// deletes the given node, based off of code from https://gist.github.com/nandor/9249431
void RBTree::deleteBST(string name) {
        Node *node = root;
        //traverses down the tree
        while (node)
        {
            if (node->name > name)
            {
                node = node->left;
            }
            else if (node->name< name)
            {
                node = node->right;
            }
            else
            {
                break;
            }
        }
        //checks if node is NULL or has the wrong name
        if (!node || node->name != name)
        {
            return;
        }

        Node *sub, *old;
        //Had to static cast since old->color was an int
        Color original = static_cast<Color>(old->color);

        //switches the nodes to prepare for deletion
        if (!node->left)
        {
            Transplant(node, sub = node->right);
        }
        else if (!node->right)
        {
            Transplant(node, sub = node->left);
        }
        else
        {
            old = minValueNode(node->right);
            ;
            sub = old->right;

            if (old->parent == node && sub != NULL)
            {
                sub->parent = node;
            }
            else
            {
                Transplant(old, old->right);
                old->right = node->right;
                old->right->parent = old;
            }

            Transplant(node, old);
            old->left = node->left;
            old->left->parent = old;
            old->color = node->color;
        }

        delete node;

        //the part that fixes the tree after deleting the node
        if (original == BLACK)
        {
            bool side;
            Node *sibling;
            while (old != root && old->color == BLACK)
            {
                if ((side = (old == old->parent->left)))
                {
                    sibling = old->parent->right;
                }
                else
                {
                    sibling = old->parent->left;
                }

                if (sibling->color == RED)
                {
                    sibling->color = BLACK;
                    old->parent->color = RED;
                    side ? rotateLeft(old->parent) : rotateRight(old->parent);
                    sibling = side ? old->parent->right : old->parent->left;
                }

                if (sibling->left->color == BLACK && sibling->right->color == BLACK)
                {
                    sibling->color = RED;
                    old = old->parent;
                }
                else
                {
                    if (BLACK == side ? sibling->right->color : sibling->left->color)
                    {
                        sibling->color = RED;
                        if (side)
                        {
                            sibling->left->color = BLACK;
                            rotateRight(sibling);
                            sibling = old->parent->right;
                        }
                        else
                        {
                            sibling->right->color = BLACK;
                            rotateLeft(sibling);
                            sibling = old->parent->left;
                        }
                    }

                    sibling->color = old->parent->color;
                    old->parent->color = BLACK;
                    if (side)
                    {
                        sibling->left->color = BLACK;
                        rotateLeft(old->parent);
                    }
                    else
                    {
                        sibling->right->color = BLACK;
                        rotateRight(old->parent);
                    }

                    old = root;
                }
            }
        }
    }

//public function that calls the protected delete function
void RBTree::deleteValue(string name) {
    deleteBST(name);
}

//in order traversal
void RBTree::inorderBST(Node *&ptr) {
    if (ptr == nullptr)
        return;
    inorderBST(ptr->left);
    cout << ptr->name << " " << ptr->color << endl;
    inorderBST(ptr->right);
}
void RBTree::inorder() {
    inorderBST(root);
}
// pre order traversal
void RBTree::preorderBST(Node *&ptr) {
    if (ptr == nullptr)
        return;
    cout << ptr->name << " " << ptr->color << endl;
    preorderBST(ptr->left);
    preorderBST(ptr->right);
}
void RBTree::preorder() {
    preorderBST(root);
    cout << "-------" << endl;
}

//finds the bottom left/minimum node
Node *RBTree::minValueNode(Node *&node) {
    Node *ptr = node;
    while (ptr->left != nullptr)
        ptr = ptr->left;
    return ptr;
}

//finds the bottom right/maximum node
Node* RBTree::maxValueNode(Node *&node) {
    Node *ptr = node;
    while (ptr->right != nullptr)
        ptr = ptr->right;
    return ptr;
}
//finds the height of the black nodes
int RBTree::getBlackHeight(Node *node) {
    int blackheight = 0;
    while (node != nullptr) {
        if (getColor(node) == BLACK)
            blackheight++;
        node = node->left;
    }
    return blackheight;
}

//functions to get the files
Node* file;
Node* getFile_helper(Node* top, string name) {
    if (top == nullptr)
        throw ("Empty Tree");
    if (name < top->name) {
        getFile_helper(top->left, name);
        //top->left->parent = top;
    }
    else if (name > top->name) {
        getFile_helper(top->right, name);
        //top->right->parent = top;
    } else if (name == top->name) {
        file = top;
    }
    return file;
}
Node RBTree::getFile(string name) {
    return *getFile_helper(root, name);
}
void getFiles_helper(Node* top, std::list<Node>& files) {
    files.push_front(*top);
    if (top->left != nullptr) {
        getFiles_helper(top->left, files);
    }
    if (top->right != nullptr) {
        getFiles_helper(top->right, files);
    }
}
std::list<Node> RBTree::getFiles() {
    std::list<Node> files;
    if (root == nullptr)
        throw ("Empty Tree");
    getFiles_helper(root, files);
    return files;
}
//deletes the tree
void clearTree_helper(Node* top) {
    if (top == nullptr) return;
    clearTree_helper(top->left);
    clearTree_helper(top->right);
    delete top;
}
void RBTree::clearTree() {
    clearTree_helper(root);
}

//switches the nodes around for deletion
void RBTree::Transplant(Node *dest, Node *src) {
    if (dest->parent == NULL)
    {
        root = src;
    }
    else if (dest == dest->parent->left)
    {
        dest->parent->left = src;
    }
    else
    {
        dest->parent->right = src;
    }

    if (src)
    {
        src->parent = dest->parent;
    }
}
