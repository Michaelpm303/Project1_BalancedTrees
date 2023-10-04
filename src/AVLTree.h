#ifndef PROJECT1_BALANCEDTREES_AVLTREE_H
#define PROJECT1_BALANCEDTREES_AVLTREE_H
#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


class AVLTree {
private:
    int levelCount;
    int nodeCount;
    Node* treeRoot; // The root of the entire AVL tree

    Node* insertHelper(Node* root, string name, string ID);
    string searchID(Node* root, string ID);
    string searchName(Node* root, string name);
    void removeHelper(Node* root, Node* parent, string ID);
public:
    void insert(string name, string ID);
    void remove(string ID);
    string search(string input);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void removeInorder(int n);
    void printBTHeight(Node* rootV, int indent = 0);
    AVLTree();
    ~AVLTree();
};


#endif //PROJECT1_BALANCEDTREES_AVLTREE_H
