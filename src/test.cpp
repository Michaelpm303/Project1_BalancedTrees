#define CATCH_CONFIG_MAIN

#include "catch2/catch_test_macros.hpp"
#include "AVLTree.cpp"
#include "Node.cpp"
#include <algorithm>

using namespace std;

TEST_CASE("Incorrect Commands"){
    // Making cout go to output stream
    ostringstream oss;
    streambuf* p_cout_streambuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;

    // (1) Invalid insert NAME input
    tree.insert("R1chard 3", "12341234"); // "uns."
    // (2) Invalid insert ID input
    tree.insert("Abe Lincoln", "1234123"); // "uns."

    // Inserting a node to prove that the input was wrong not the function itself
    tree.insert("tree Root", "11111111"); // "suc."

    // (3) Invalid search input
    tree.search("tree Root 11111111"); // "uns."
    // (4) Invalid removeInorder N input // "uns."
    tree.removeInorder("zero");
    // (5) Invalid remove ID
    tree.remove("tree Root"); // "uns."

    // Valid search input
    tree.search("11111111"); // "tree Root"
    // Valid removeInorder N input
    tree.removeInorder("0"); // "suc."




    cout.rdbuf(p_cout_streambuf); // restore

    REQUIRE(oss.str() == "unsuccessful\n"
                         "unsuccessful\n"
                         "successful\n"
                         "unsuccessful\n"
                         "unsuccessful\n"
                         "unsuccessful\n"
                         "tree Root\n"
                         "successful\n");

}

TEST_CASE("Edge Cases") {
    // Making cout go to output stream
    ostringstream oss;
    streambuf* p_cout_streambuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;

    // Inserting some sample nodes
    tree.insert("John Smith", "55555555"); // "suc."
    tree.insert("John Smith", "44444444"); // "suc."
    tree.insert("John Smith", "33333333"); // "suc."

    // (1) Removing unknown Node
    tree.remove("33333330"); // "uns."

    // (2) Searching duplicate names
    tree.search("John Smith"); // "3... \n 4... \n 5..."

    // (3) Inserting duplicate ID
    tree.insert("Uhoh", "44444444"); // "uns."

    // (4) Removing treeRoot
    tree.remove("44444444"); // "suc."

    // (5) N out of bounds for removeInorder
    tree.removeInorder("10"); // "uns."

    // restore
    cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "successful\n"
                         "successful\n"
                         "successful\n"
                         "unsuccessful\n"
                         "44444444\n"
                         "33333333\n"
                         "55555555\n"
                         "unsuccessful\n"
                         "successful\n"
                         "unsuccessful\n");
}

TEST_CASE("Right Rotation") {
    // Making cout go to output stream
    ostringstream oss;
    streambuf* p_cout_streambuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;

    tree.insert("Top", "55555555"); // "suc."
    tree.insert("Center", "44444444"); // "suc."
    tree.insert("Bottom", "33333333"); // "suc."

    tree.printLevelCount(); // "2"

    // restore
    cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "successful\n"
                         "successful\n"
                         "successful\n"
                         "2\n");
}

TEST_CASE("Left Rotation") {
    // Making cout go to output stream
    ostringstream oss;
    streambuf* p_cout_streambuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;

    tree.insert("Top", "33333333"); // "suc."
    tree.insert("Center", "44444444"); // "suc."
    tree.insert("Bottom", "55555555"); // "suc."

    tree.printLevelCount(); // "2"

    // restore
    cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "successful\n"
                         "successful\n"
                         "successful\n"
                         "2\n");
}

TEST_CASE("Left Right Rotation") {
    // Making cout go to output stream
    ostringstream oss;
    streambuf* p_cout_streambuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;

    tree.insert("Top", "44444444"); // "suc."
    tree.insert("Center", "33333333"); // "suc."
    tree.insert("Bottom", "33334444"); // "suc."

    tree.printLevelCount(); // "2"

    // restore
    cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "successful\n"
                         "successful\n"
                         "successful\n"
                         "2\n");
}
TEST_CASE("Right Left Rotation") {
    // Making cout go to output stream
    ostringstream oss;
    streambuf* p_cout_streambuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;

    tree.insert("Top", "33333333"); // "suc."
    tree.insert("Center", "44444444"); // "suc."
    tree.insert("Bottom", "33334444"); // "suc."

    tree.printLevelCount(); // "2"

    // restore
    cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "successful\n"
                         "successful\n"
                         "successful\n"
                         "2\n");
}
TEST_CASE("All Deletion Cases") {
    // Making cout go to output stream
    ostringstream oss;
    streambuf* p_cout_streambuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;

    tree.insert("Root", "55555555"); // suc
    tree.insert("Michael", "11111111"); // suc
    tree.insert("John", "88888888"); // suc
    tree.insert("Mark", "77777777"); // suc
    tree.insert("Dave", "99999999"); // suc

    tree.printPreorder(); // root, mic, john, mark, dave

    // Deleting with 2 children (replace with successor)
    tree.remove("55555555"); // suc
    tree.printPreorder(); // mark, mic, john, dave

    // Deleting with no children
    tree.remove("99999999"); // suc
    // Deleting with 1 child
    tree.remove("88888888"); // suc


    tree.printPreorder(); // mark, michael

    // restore
    cout.rdbuf(p_cout_streambuf);

    REQUIRE(oss.str() == "successful\n"
                         "successful\n"
                         "successful\n"
                         "successful\n"
                         "successful\n"
                         "Root, Michael, John, Mark, Dave\n"
                         "successful\n"
                         "Mark, Michael, John, Dave\n"
                         "successful\n"
                         "successful\n"
                         "Mark, Michael\n");
}

TEST_CASE("BST Insert Large") {
    // Making cout go to output stream
    ostringstream oss;
    streambuf* p_cout_streambuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;
    std::vector<string> expectedOutput, actualOutput;

    // From catch test example
    for(int i = 0; i < 100; i++) {
        string randomID;
        // Making 8-digit random number
        for (int j = 0; j < 8; j++) {
            char digit = '0' + (rand() % 10); // Generates a random digit from 0-9
            randomID += digit;
        }
        string defName = "John Smith";

        tree.insert(defName, randomID);
    }

    string output;
    istringstream iss(oss.str());

    // Verifying 100 successful insertion outputs
    for(int i = 0; i < 100; i++) {
        // checking that each (100) line outputs "successful"
        getline(iss, output);

        REQUIRE(output == "successful");
    }
    // Deleting 10 nodes
    for(int i = 0; i < 10; i++) {
        int deleted = rand() % 9;
        tree.removeInorder(to_string(deleted));
    }

    // restore
    cout.rdbuf(p_cout_streambuf);

    REQUIRE(tree.getNodeCount() == 90);

}
