#ifndef PROJECT1_BALANCEDTREES_NODE_H
#define PROJECT1_BALANCEDTREES_NODE_H
#include <string>
using namespace std;

struct Node {
    Node* left;
    Node* right;
    string name;
    int ID;
    int height;
    int balanceFactor;

    Node(string name, int ID);
};


#endif
