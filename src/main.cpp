#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include "Node.h"
#include "AVLTree.h"
using namespace std;

int main() {
    AVLTree tree;

    string numCommands;
    cout << "Input:" << endl;
    getline(cin,numCommands); // Number of commands

    regex IDReg = regex("^[0-9]{8,8}$"); // 8-digit number
    regex nameReg = regex("^\"[a-zA-Z\\s]+\"$"); // Text enclosed in quotation marks

    string commandString;


    // Run the loop as many times as there are commands
    for(int i = 0; i < stoi(numCommands); i++) {
        // Taking the command line and making it into isstream to get each word part from it
        getline(cin, commandString);
        istringstream commandStream(commandString);

        string command; // Command


        commandStream >> command >> ws;
        if(command == "insert") {
            // Declaring parameters
            string parameter1;
            string parameter2;
            getline(commandStream,parameter1,'"');
            commandStream >> parameter2;
        }
        //vector<string> commandV;
//        while(getline(commandStream,word, ' ')) {
//            commandV.push_back(word);
//        }
//
//
//        // If the first word of the command is "insert"
//        // insert NAME ID
//        if (commandV.at(0) == "insert") {
//            // If wrong format of command
//            if(commandV.size() != 3) {
//                cout << "unsuccessful" << endl;
//            }
//            // If invalid name format
//            else if (!regex_match(commandV.at(1),nameReg)) {
//                cout << "unsuccessful" << endl;
//            }
//            // If invalid ID format
//            else if (!regex_match(commandV.at(2), IDReg)) {
//                cout << "unsuccessful" << endl;
//            }
//            // If valid format
//            else {
//                tree.insert(commandV.at(1), commandV.at(2));
//                //cout << "successful: " << commandV.at(1)<< endl;
//            }
//        }
        // If no function was called
        else {
            cout << "unsuccessful" << endl;
        }

    }




    // remove ID

    //search ID

    //search NAME

    //printInorder

    //printPreorder

    //printPostorder

    //printLevelCount

    //removeInorder N
}
