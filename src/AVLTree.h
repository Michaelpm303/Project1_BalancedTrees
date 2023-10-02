#ifndef PROJECT1_BALANCEDTREES_AVLTREE_H
#define PROJECT1_BALANCEDTREES_AVLTREE_H
#include "Node.h"
#include <string>
using namespace std;


class AVLTree {
private:
    int levelCount;
    int nodeCount;
    Node* treeRoot; // The root of the entire AVL tree

    Node* insert(Node* root, string name, int ID);
    void remove(int ID);
    string search(int ID);
    int search(string ID);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void removeInorder(int n);

public:
    AVLTree();
    ~AVLTree();
};


#endif //PROJECT1_BALANCEDTREES_AVLTREE_H
