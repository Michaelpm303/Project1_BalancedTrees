#include "AVLTree.h"
#include <regex>

AVLTree::AVLTree() {
    treeRoot = nullptr;
    levelCount = 0;
    nodeCount = 0;
}

AVLTree::~AVLTree() = default;

void AVLTree::updateHeights(Node* root) {
    if(root == nullptr) {
        return;
    }
    updateHeights(root->left);
    updateHeights(root->right);

    root->height = 1 + max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);
}

// Using code from 9/28 lecture
// O(log(n))
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
        cout << "successful" << endl;
        nodeCount++;
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
    root->balanceFactor = (root->left ? root->left->height : 0) - (root->right ? root->right->height : 0);

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
        Node* temp1 = root->left->right->left; // Bottom node's left
        root->left->right->left = root->left;
        Node* temp2 = root->left->right; // Bottom node
        root->left->right = temp1;
        root->left = temp2;

        // 2nd step of left-right rotation
        temp1 = root->left; // Center node (future root)
        root->left = root->left->right;
        temp1->right = root;
        root = temp1;
    }
    // Right Left Alignment
    if (root->balanceFactor == -2 && root->right->balanceFactor == 1) {

        // Adjusting the heights as they change from the rotation
        root->height -= 2;
        root->right->left->height++;
        root->right->height--;

        // 1st step of right-left rotation
        Node* temp1 = root->right->left->right; // Bottom node's right
        root->right->left->right = root->right;
        Node* temp2 = root->right->left; // Bottom node
        root->right->left = temp1;
        root->right = temp2;

        // 2nd step of right-left rotation
        temp1 = root->right; // Center node (future root)
        root->right = root->right->left;
        temp1->left = root;
        root = temp1;
    }

    return root;
}

void AVLTree::insert(string name, string ID) {

    treeRoot = insertHelper(treeRoot, name, ID);

}

Node* AVLTree::removeHelper(Node* root, string ID, bool& foundTarget) {
    if (root == nullptr) {
        return root;
    }
    if (ID < root->ID) {
        root->left = removeHelper(root->left, ID, foundTarget);
    }
    else if (ID > root->ID) {
        root->right = removeHelper(root->right, ID, foundTarget);
    }
    // If the root is the deletion target
    else {
        // Update bool
        foundTarget = true;

        // Case 1: target node has no children
        if (!root->left && !root->right) {
            if(treeRoot == root) {
                treeRoot = nullptr;
            }
            delete root;
            root = nullptr;
            return nullptr;
        }
        // Case 2: target node has only left child
        else if (root->left && !root->right) {
            Node* temp = root->left;
            // Special case: deleted node is the treeRoot
            if(treeRoot == root) {
                treeRoot = temp;
            }
            delete root;
            root = nullptr;
            return temp;
        }
        // Case 3: target node has only right child
        else if (!root->left && root->right) {
            Node* temp = root->right;
            // Special case: deleted node is the treeRoot
            if(treeRoot == root) {
                treeRoot = temp;
            }
            delete root;
            root = nullptr;
            return temp;
        }
        // Case 4: target node has both children
        else if (root->left && root->right) {
            Node* successor = root->right;
            while (successor->left) {
                // When successor->left is the target successor, ensure moving the successor does
                // not cause a cycle in the tree (this could break the code later)
                if(!successor->left->left) {
                    Node* temp = successor->left;
                    successor->left = nullptr;
                    successor = temp;
                    break;
                }
                successor = successor->left;
            }
            // Preventing node pointing to itself
            if(root->right == successor) {
                successor->right = nullptr;
            }
            else {
                successor->right = root->right;
            }
            successor->left = root->left;
            // Special case: deleted node is the treeRoot
            if(treeRoot == root) {
                treeRoot = successor;
            }
            delete root;
            root = nullptr;
            return successor;
        }

    }
    return root;
}


void AVLTree::remove(string ID) {

    // bool to check if successful or not
    bool foundTarget = false;

    // First verify correct input
    regex IDReg = regex("^[0-9]{8,8}$"); // 8-digit number
    if(!regex_match(ID, IDReg)) {
        cout << "unsuccessful" << endl;
        return;
    }

    // Special case: only 1 node in tree
    if(nodeCount == 1 && treeRoot->ID == ID) {
        delete treeRoot;
        cout << "successful" << endl;
        nodeCount--;
        treeRoot = nullptr;
    }
    // Removing node form normal tree
    else {
        removeHelper(treeRoot, ID, foundTarget);

        // The function found and deleted target
        if (foundTarget) {
            updateHeights(treeRoot); // Fix the heights O(n)
            cout << "successful" << endl;
            nodeCount--;
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }
}

// O(log(n))
Node* AVLTree::searchID(Node* root, string ID) {
    if(root == nullptr) {
        return nullptr;
    }
    // Base case: matching ID
    if(root->ID == ID) {
        return root;
    }
    // Search left subtree
    else if(ID < root->ID) {
        root = searchID(root->left, ID);
    }
    // Search right subtree
    else if(ID > root->ID) {
        root = searchID(root->right, ID);
    }

    return root;
}

// O(n)
bool AVLTree::searchName(Node* root, string name) {
    bool nameFound = false;
    // Base case: leaf node
    if(root == nullptr) {
        return false;
    }
    // Node (N)
    if (root->name == name) {
        cout << root->ID << endl;
        nameFound = true;
    }
    // Left subtree (L)
    if(searchName(root->left, name)) {
        nameFound = true;
    }
    // Right subtree (R)
    if(searchName(root->right, name)) {
        nameFound = true;
    }
    // If no matching name was found
    return nameFound;
}

// search(string input) function checks for ID or NAME input
void AVLTree::search(string input) {
    regex IDReg = regex("^[0-9]{8,8}$"); // 8-digit number
    regex nameReg = regex("^[a-zA-Z\\s]+$"); // Alphabetical characters and spaces, quotes were already checked

    // If searching using ID as input
    if(regex_match(input,IDReg)) {
        Node* match = searchID(treeRoot,input);
        if (match) {
            cout << match->name << endl;
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }
    // If searching using NAME as input
    else if(regex_match(input,nameReg)) {
        // If no matching name was found
        if (!searchName(treeRoot, input)) {
            cout << "unsuccessful" << endl;
        }
    }
    // Invalid input
    else {
        cout << "unsuccessful" << endl;
        return;
    }
}
// Passing bool by reference so it updates the state when getting to the bottom of the call stack
// O(n)
void AVLTree::printInorderHelper(Node* root, bool& isFirst) {
    // LNR traversal
    if(root == nullptr) {
        return;
    }
    // Left (L)
    printInorderHelper(root->left, isFirst);

    // Node (N)
    if(isFirst) {
        cout << root->name;
        isFirst = false;
    }
    else {
        cout << ", " << root->name;
    }

    // Right (R)
    printInorderHelper(root->right, isFirst);
}

// O(n)
void AVLTree::printInorder() {
    if(treeRoot != nullptr) {
        bool isFirst = true;
        printInorderHelper(treeRoot, isFirst);
        cout << endl;
    }
}

// O(n)
void AVLTree::printPreorderHelper(Node* root, bool& isFirst) {
    if(root == nullptr) {
        return;
    }
    // Node (N)
    if(isFirst) {
        cout << root->name;
        isFirst = false;
    }
    else {
        cout << ", " << root->name;
    }

    // Left (L)
    printPreorderHelper(root->left, isFirst);

    // Right (R)
    printPreorderHelper(root->right, isFirst);
}

// O(n)
void AVLTree::printPreorder() {
    if(treeRoot != nullptr) {
        bool isFirst = true;
        printPreorderHelper(treeRoot, isFirst);
        cout << endl;
    }
}

// O(n)
void AVLTree::printPostorderHelper(Node* root, bool& isFirst) {
    if(root == nullptr) {
        return;
    }
    // Left (L)
    printPostorderHelper(root->left, isFirst);
    // Right (R)
    printPostorderHelper(root->right, isFirst);
    // Node (N)
    if(isFirst) {
        cout << root->name;
        isFirst = false;
    }
    else {
        cout << ", " << root->name;
    }
}

// O(n)
void AVLTree::printPostorder() {
    if(treeRoot != nullptr) {
        bool isFirst = true;
        printPostorderHelper(treeRoot, isFirst);
        cout << endl;
    }
}

void AVLTree::printLevelCount() {
    if(treeRoot == nullptr) {
        cout << "0" << endl;
    }
    else {
        cout << treeRoot->height << endl;
    }
}


Node *AVLTree::removeInorderHelper(Node* root, int& i, int n) {
    if(root == nullptr) {
        return root;
    }
    // Left (L)
    root->left = removeInorderHelper(root->left, i, n);


    // Node (N)
    // Found target node to delete
    if (i == n) {

        nodeCount--;
        i++;

        // Case 1: target node has no children
        if (!root->left && !root->right) {
            // Special case: deleted node is the treeRoot
            if(treeRoot == root) {
                treeRoot = nullptr;
            }
            delete root;
            root = nullptr;
            return nullptr;
        }
        // Case 2: target node has only left child
        else if (root->left && !root->right) {
            Node* temp = root->left;
            // Special case: deleted node is the treeRoot
            if(treeRoot == root) {
                treeRoot = temp;
            }
            delete root;
            root = nullptr;
            return temp;
        }
            // Case 3: target node has only right child
        else if (!root->left && root->right) {
            Node* temp = root->right;
            // Special case: deleted node is the treeRoot
            if(treeRoot == root) {
                treeRoot = temp;
            }
            delete root;
            root = nullptr;
            return temp;
        }
            // Case 4: target node has both children
        else {
            Node* successor = root->right;
            while (successor->left) {
                // When successor->left is the target successor, ensure moving the successor does
                // not cause a cycle in the tree (this could break the code later)
                if(!successor->left->left) {
                    Node* temp = successor->left;
                    successor->left = nullptr;
                    successor = temp;
                    break;
                }
                successor = successor->left;
            }
            // Preventing node pointing to itself
            if(root->right == successor) {
                successor->right = nullptr;
            }
            else {
                successor->right = root->right;
            }
            successor->left = root->left;
            // Special case: deleted node is the treeRoot
            if(treeRoot == root) {
                treeRoot = successor;
            }
            delete root;
            root = nullptr;
            return successor;
        }

    }
    i++;

    // Right (R)
    root->right = removeInorderHelper(root->right, i, n);

    return root;
}


void AVLTree::removeInorder(string n) {

    // Verifying correct input
    regex numReg = regex("^[0-9]+$");
    if(!regex_match(n,numReg)) {
        cout << "unsuccessful" << endl;
    }
    // If correct input
    else {
        int numN = stoi(n);
        // If N exceeds the number of nodes in the tree
        if(numN > nodeCount) {
            cout << "unsuccessful" << endl;
            return;
        }
        int i = 0;
        removeInorderHelper(treeRoot, i, numN);
        cout << "successful" << endl;
    }
}

int AVLTree::getNodeCount() {
    return nodeCount;
}
