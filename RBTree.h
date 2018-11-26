//
// Red Black Tree Definition
//

#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

#include <string>
#include <list>
using namespace std;

//colors for the RBTree
enum Color { RED, BLACK};

//Node structure
struct Node
{
    int size;
    std::string name;
    int color;
    Node *left, *right, *parent;

    // Constructors
    Node(){
        size = 0;
        name = "";
    }
    Node(std::string name, int size)
    {
        this->size = size;
        this->name = name;
        left = right = parent = NULL;
    }
};
//RBTree class
class RBTree
{
private:
    Node * root;
protected:
    void rotateLeft(Node *&);
    void rotateRight(Node *&);
    void fixInsertRBTree(Node *&);
    void inorderBST(Node *&);
    void preorderBST(Node *&);
    int getColor(Node *&);
    void setColor(Node *&, int);
    void Transplant(Node *dest, Node *src);
    Node *minValueNode(Node *&);
    Node* maxValueNode(Node *&node);
    Node* insertBST(Node *&, Node *&);
    void deleteBST(string name);
    void fixDeleteRBTree(Node *&node);
    int getBlackHeight(Node *);
public:
    RBTree();
    void insertValue(std::string, int);
    void deleteValue(std::string);
    void inorder();
    void preorder();
    Node getFile(std::string name);
    std::list<Node> getFiles();
    void clearTree();
};


#endif //RED_BLACK_TREE_RBTREE_H