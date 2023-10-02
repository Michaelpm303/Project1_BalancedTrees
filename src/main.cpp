#include <iostream>
#include <string>
#include <sstream>
#include "Node.h"
using namespace std;

int main() {
    string input;
    cout << "Input:" << endl;
    getline(cin,input);

    stringstream commandList(input);
    string numCommands;
    getline(commandList,numCommands);
    string command;
    // Loop iterating through each command
//    for(int i = 0; i < stoi(numCommands); i++) {
//
//        getline(commandList, command);
//        if(command == "insert") {
//            cout << "WOOW" << endl;
//        }
//        cout << command << endl;
//        count++;
//    }
//    cout << count;

while(getline(commandList,command)) {
    cout << command << endl;
}

    // insert NAME ID

    // remove ID

    //search ID

    //search NAME

    //printInorder

    //printPreorder

    //printPostorder

    //printLevelCount

    //removeInorder N
}
