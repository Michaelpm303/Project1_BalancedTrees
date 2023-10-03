#ifndef PROJECT1_BALANCEDTREES_NODE_H
#define PROJECT1_BALANCEDTREES_NODE_H
#include <string>
using namespace std;

struct Node {
    Node* left;
    Node* right;
    string name;
    string ID;
    int height;
    int balanceFactor;

    Node();
    Node(string name, string ID);
};


#endif
