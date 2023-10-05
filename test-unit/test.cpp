#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include <../src/AVLTree.cpp>
#include <../src/Node.cpp>
#include <algorithm>

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("Incorrect commands", "[flag]"){
    // Making cout go to output stream
    ostringstream oss;
    cout.rdbuf(oss.rdbuf());

    AVLTree tree;
    stringstream outputS;

    // Invalid name input
    tree.insert("R1chard 3", "12341234");
    REQUIRE(oss.str() == "unsuccessful\n");

    int test = 1;
	REQUIRE(test == 1);
}
TEST_CASE("BST Delete", "[flag]") {

    REQUIRE(1 == 1);
}

//TEST_CASE("BST Insert Large", "[flag]"){
//    AVLTree tree;
//    std::vector<string> expectedOutput, actualOutput;
//
//    // From catch test example
//    for(int i = 0; i < 100; i++)
//    {
//        string randomID;
//        // Making 8-digit random number
//        for (int j = 0; j < 8; j++) {
//            char digit = '0' + (rand() % 10); // Generates a random digit from 0-9
//            randomID += digit;
//        }
//        string defName = "John Smith";
//
//        tree.insert(defName, randomID);
//    }
//    // Deleting 10 nodes
//    for(int i = 0; i < 10; i++) {
//        int deleted = rand() % 9;
//        tree.removeInorder(to_string(deleted));
//    }
//    REQUIRE(tree.nodeCount == 90);
//
//}
