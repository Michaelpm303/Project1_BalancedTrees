#include "AVLTree.h"

AVLTree::AVLTree() {
    treeRoot = nullptr;
}

// Using code from 9/28 lecture
Node* AVLTree::insert(Node* root, string name, int ID) {
    if(root == nullptr) {
        return new Node(name, ID);
    }
    else if(ID < root->ID) {
        root->left = insert(root->left, name, ID);
    }
    else if(ID > root->ID) {
        root->right = insert(root->right, name, ID);
        root->height = 1 + max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);
    }

return root;
}


