#include "Node.h"
Node::Node(string name, string ID) {
    this->name = name;
    this->ID = ID;
    left = nullptr;
    right = nullptr;
    balanceFactor = 0;
    height = 0;
}

Node::Node() {
    name = "";
    ID = "";
    left = nullptr;
    right = nullptr;
}





