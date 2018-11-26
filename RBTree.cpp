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

void RBTree::fixDeleteRBTree(Node *&node) {
    if (node == nullptr)
        return;

    if (node == root) {
        root = nullptr;
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node *child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
        else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
    }
    else {
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                }
                else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    }
                    else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            }
            else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                }
                else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    }
                    else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACK);
    }
}

Node* RBTree::deleteBST(Node *&root, string name) {
    if (root == nullptr)
        return root;

    if (name < root->name)
        return deleteBST(root->left, name);

    if (name > root->name)
        return deleteBST(root->right, name);

    if (root->left == nullptr || root->right == nullptr)
        return root;

    Node *temp = minValueNode(root->right);
    root->name = temp->name;
    return deleteBST(root->right, temp->name);
}

void RBTree::deleteValue(string name) {
    Node *node = deleteBST(root, name);
    fixDeleteRBTree(node);
}

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

Node *RBTree::minValueNode(Node *&node) {

    Node *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

Node* RBTree::maxValueNode(Node *&node) {
    Node *ptr = node;

    while (ptr->right != nullptr)
        ptr = ptr->right;

    return ptr;
}

int RBTree::getBlackHeight(Node *node) {
    int blackheight = 0;
    while (node != nullptr) {
        if (getColor(node) == BLACK)
            blackheight++;
        node = node->left;
    }
    return blackheight;
}

// Test case 1 : 5 2 9 1 6 8 0 20 30 35 40 50 0
// Test case 2 : 3 0 5 0
// Test case 3 : 2 1 3 0 8 9 4 5 0

void RBTree::merge(RBTree rbTree2) {
    string temp;
    Node *c, *temp_ptr;
	temp_ptr = nullptr;
	c = nullptr;
    Node *root1 = root;
    Node *root2 = rbTree2.root;
    int initialblackheight1 = getBlackHeight(root1);
    int initialblackheight2 = getBlackHeight(root2);
    if (initialblackheight1 > initialblackheight2) {
        c = maxValueNode(root1);
        temp = c->name;
        deleteValue(c->name);
        root1 = root;
    }
    else if (initialblackheight2 > initialblackheight1) {
        c = minValueNode(root2);
        temp = c->name;
        rbTree2.deleteValue(c->name);
        root2 = rbTree2.root;
    }
    else {
        c = minValueNode(root2);
        temp = c->name;
        rbTree2.deleteValue(c->name);
        root2 = rbTree2.root;
        if (initialblackheight1 != getBlackHeight(root2)) {
            rbTree2.insertValue(c->name, c->size);
            root2 = rbTree2.root;
            c = maxValueNode(root1);
            temp = c->name;
            deleteValue(c->name);
            root1 = root;
        }
    }
    setColor(c, RED);
    int finalblackheight1 = getBlackHeight(root1);
    int finalblackheight2 = getBlackHeight(root2);
    if (finalblackheight1 == finalblackheight2) {
        c->left = root1;
        root1->parent = c;
        c->right = root2;
        root2->parent = c;
        setColor(c, BLACK);
        c->name = temp;
        root = c;
    }
    else if (finalblackheight2 > finalblackheight1) {
        Node *ptr = root2;
        while (finalblackheight1 != getBlackHeight(ptr)) {
            temp_ptr = ptr;
            ptr = ptr->left;
        }
        Node *ptr_parent;
        if (ptr == nullptr)
            ptr_parent = temp_ptr;
        else
            ptr_parent = ptr->parent;
        c->left = root1;
        if (root1 != nullptr)
            root1->parent = c;
        c->right = ptr;
        if (ptr != nullptr)
            ptr->parent = c;
        ptr_parent->left = c;
        c->parent = ptr_parent;
        if (getColor(ptr_parent) == RED) {
            fixInsertRBTree(c);
        }
        else if (getColor(ptr) == RED) {
            fixInsertRBTree(ptr);
        }
        c->name = temp;
        root = root2;
    }
    else {
        Node *ptr = root1;
        while (finalblackheight2 != getBlackHeight(ptr)) {
            ptr = ptr->right;
        }
        Node *ptr_parent = ptr->parent;
        c->right = root2;
        root2->parent = c;
        c->left = ptr;
        ptr->parent = c;
        ptr_parent->right = c;
        c->parent = ptr_parent;
        if (getColor(ptr_parent) == RED) {
            fixInsertRBTree(c);
        }
        else if (getColor(ptr) == RED) {
            fixInsertRBTree(ptr);
        }
        c->name = temp;
        root = root1;
    }
    return;
}

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

void clearTree_helper(Node* top) {
    if (top == nullptr) return;

    clearTree_helper(top->left);
    clearTree_helper(top->right);

    delete top;
}

void RBTree::clearTree() {
    clearTree_helper(root);
}