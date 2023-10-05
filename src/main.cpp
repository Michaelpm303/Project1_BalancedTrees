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

    getline(cin, numCommands); // Number of commands

    regex IDReg = regex("^[0-9]{8,8}$"); // 8-digit number
    regex nameReg = regex("^\"[a-zA-Z\\s]+\"$"); // Text enclosed in quotation marks
    regex numReg = regex("^[0-9]+$");

    string commandString;


    // Run the loop as many times as there are commands
    for (int i = 0; i < stoi(numCommands); i++) {
        // Taking the command line and making it into isstream to get each word part from it
        getline(cin, commandString);
        istringstream commandStream(commandString);

        string command; // Command

        commandStream >> command >> ws;
        if (command == "insert") {
            // Declaring parameters
            string nameInput;
            string IDInput;

            // Ensures that the name is inputted within quotes
            if (commandStream.peek() == '"') {
                commandStream >> quoted(nameInput);
            }
            commandStream >> IDInput;

            tree.insert(nameInput, IDInput);
        } else if (command == "remove") {
            string IDInput;
            commandStream >> IDInput;
            tree.remove(IDInput);
        } else if (command == "search") {
            string input;
            // If input has quotes (expect spaces, so need quoted function)
            if (commandStream.peek() == '"') {
                commandStream >> quoted(input);
            } else {
                commandStream >> input;
            }
            tree.search(input);
        } else if (command == "printInorder") {
            tree.printInorder();
        } else if (command == "printPreorder") {
            tree.printPreorder();
        } else if (command == "printPostorder") {
            tree.printPostorder();
        } else if (command == "printLevelCount") {
            tree.printLevelCount();
        } else if (command == "removeInorder") {
            string input;
            commandStream >> input;
            tree.removeInorder(input);
        }
            // If no existing function was called
        else {
            cout << "unsuccessful" << endl;
        }

    }
}