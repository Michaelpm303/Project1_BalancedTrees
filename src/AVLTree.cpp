#include "AVLTree.h"

AVLTree::AVLTree(string name, int ID) {
    root->name = name;
    root->ID = ID;
}

Node* AVLTree::insert(Node* root, string name, int ID) {
    if(root == nullptr) {
        root->name = name;
        root->ID = ID;
    }
    else if(ID < root->ID) {
        root->left = insert()
    }
}


