#include "AVLTree.h"

AVLTree::AVLTree() {
    treeRoot = nullptr;
    levelCount = 0;
    nodeCount = 0;
}

AVLTree::~AVLTree() {

}

// Using code from 9/28 lecture
Node* AVLTree::insertHelper(Node* root, string name, string ID) {
    // Base Case: creating leaf node in appropriate position
    if(root == nullptr) {
        return new Node(name, ID);
    }
    // If ID is smaller than current node
    else if(ID < root->ID) {
        root->left = insertHelper(root->left, name, ID);
    }
    // If ID is greater than current node
    else if(ID > root->ID) {
        root->right = insertHelper(root->right, name, ID);
    }
    // Calculating height of current node
    root->height = 1 + max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);
    // Calculating balance factor of current node
    root->balanceFactor = (root->left ? root->left->height+1 : 0) - (root->right ? root->right->height+1 : 0);

    // Left Left Alignment
    if (root->balanceFactor == 2 && root->left->balanceFactor == 1) {
        // Adjusting the heights as they change from the rotation
        root->height -= 2;
        // Rotating
        Node* temp = root->left;
        root->left = root->left->right;
        temp->right = root;
        root = temp;
    }
    // Right Right Alignment
    if (root->balanceFactor == -2 && root->right->balanceFactor == -1) {
        // Adjusting the heights as they change from the rotation
        root->height -= 2;
        // Rotating
        Node* temp = root->right;
        root->right = root->right->left;
        temp->left = root;
        root = temp;
    }
    // Left Right Alignment
    if (root->balanceFactor == 2 && root->left->balanceFactor == -1) {
        // Adjusting the heights as they change from the rotation
        root->height -= 2;
        root->left->right->height++;
        root->left->height--;
        // 1st step of left-right rotation
        root->left->right->left = root->left;
        Node* temp = root->left->right;
        root->left->right = nullptr;
        root->left = temp;
        // 2nd step of left-right rotation
        temp = root->left;
        root->left = root->left->right;
        temp->right = root;
        root = temp;
    }
    // Right Left Alignment
    if (root->balanceFactor == -2 && root->right->balanceFactor == 1) {
        // Adjusting the heights as they change from the rotation
        root->height -= 2;
        root->right->left->height++;
        root->right->height--;
        // 1st step of left-right rotation
        root->right->left->right = root->right;
        Node* temp = root->right->left;
        root->right->left = nullptr;
        root->right = temp;
        // 2nd step of right-left rotation
        temp = root->right;
        root->right = root->right->left;
        temp->left = root;
        root = temp;
    }

    return root;
}

void AVLTree::insert(string name, string ID) {
    treeRoot = insertHelper(treeRoot, name, ID);

    printBTHeight(treeRoot);

}
// With help from ChatGPT to visualize the tree to make troubleshooting much easier
void AVLTree::printBTHeight(Node* rootV, int indent) {
    if (rootV == nullptr) {
        return;
    }

    // Print the right subtree first
    if (rootV->right != nullptr) {
        printBTHeight(rootV->right, indent + 4);
    }

    // Print the current node's data with indentation
    std::cout << std::setw(indent) << " " << rootV->ID << "/" << rootV->balanceFactor << "/" << rootV->height << "\n";

    // Print the left subtree
    if (rootV->left != nullptr) {
        printBTHeight(rootV->left, indent + 4);
    }
}

