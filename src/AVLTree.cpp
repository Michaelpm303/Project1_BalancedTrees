#include "AVLTree.h"
#include <regex>

AVLTree::AVLTree() {
    treeRoot = nullptr;
    levelCount = 0;
    nodeCount = 0;

}

AVLTree::~AVLTree() {

}

// Using code from 9/28 lecture
Node* AVLTree::insertHelper(Node* root, string name, string ID) {
    regex IDReg = regex("^[0-9]{8,8}$"); // 8-digit number
    regex nameReg = regex("^[a-zA-Z\\s]+$"); // Alphabetical characters and spaces, quotes were already checked

    // If invalid name or ID format
    if(!regex_match(name,nameReg) || !regex_match(ID,IDReg)) {
        cout << "unsuccessful" << endl;
        return root;
    }
    // Base Case: creating leaf node in appropriate position
    if(root == nullptr) {
        return new Node(name, ID);
    }
    // If current ID is already stored
    else if(ID == root->ID) {
        cout << "unsuccessful" << endl;
        return root;
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
// Need to store the parent node to add the subtree back to the tree after its root is deleted
void AVLTree::removeHelper(Node* root, Node* parent, string ID) {
    // Case 1: target node has left child

    // Case 2: target node has right child

    // Case 3: target node has both children

    // Case 4: target node has no children

}

void AVLTree::remove(string ID) {
    // First verify correct input
    regex IDReg = regex("^[0-9]{8,8}$"); // 8-digit number
    if(!regex_match(ID, IDReg)) {
        cout << "unsuccessful" << endl;
        return;
    }

    // Start search for removal with left subtree
    if (treeRoot->left && ID < treeRoot->left->ID) {
        removeHelper(treeRoot, treeRoot->left, ID);
    }
    else if (treeRoot->right && ID > treeRoot->right->ID) {
        removeHelper(treeRoot, treeRoot->right, ID);
    }
}

string AVLTree::searchID(Node* root, string ID) {
    string foundName;
    // Base case: matching ID
    if(root->ID == ID) {
        cout << root->name << endl;
        return root->name;
    }
    // Search left subtree
    else if(ID < root->ID) {
        foundName = searchID(root->left, ID);
    }
    // Search right subtree
    else if(ID > root->ID) {
        foundName = searchID(root->right, ID);
    }
    // Base case: no matching ID
    else {
        cout << "unsuccessful" << endl;
    }
    return foundName;
}

string AVLTree::searchName(Node* root, string name) {
    return "";
}

// search(string input) function checks for ID or NAME input
string AVLTree::search(string input) {
    regex IDReg = regex("^[0-9]{8,8}$"); // 8-digit number
    regex nameReg = regex("^[a-zA-Z\\s]+$"); // Alphabetical characters and spaces, quotes were already checked

    // If searching using ID as input
    if(regex_match(input,IDReg)) {
        return searchID(treeRoot,input);
    }
    // If searching using NAME as input
    if(regex_match(input,nameReg)) {
        return searchName(treeRoot, input);
    }
    // Invalid input
    else {
        cout << "unsuccessful" << endl;
        return "";
    }
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

