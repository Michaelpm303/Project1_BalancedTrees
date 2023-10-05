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
    Node* treeRoot; // The root of the entire AVL tree

    void updateHeights(Node* root);
    Node* insertHelper(Node* root, string name, string ID);
    Node* searchID(Node* root, string ID);
    bool searchName(Node* root, string name);
    Node* removeHelper(Node* root, string ID, bool& foundTarget);
    void printInorderHelper(Node* root, bool& isFirst);
    void printPreorderHelper(Node* root, bool& isFirst);
    void printPostorderHelper(Node* root, bool& isFirst);
    Node* removeInorderHelper(Node* root, int& i, int n);
    int nodeCount;
public:
    void insert(string name, string ID);
    void remove(string ID);
    void search(string input);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void removeInorder(string n);

    int getNodeCount();

    AVLTree();
    ~AVLTree();

};


#endif //PROJECT1_BALANCEDTREES_AVLTREE_H
