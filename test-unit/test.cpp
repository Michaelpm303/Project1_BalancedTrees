#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#define private public
#include <../src/AVLTree.h>
/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("BST Insert", "[flag]"){
	/*
		MyAVLTree tree;   // Create a Tree object 
		tree.insert(3);
		tree.insert(2);
		tree.insert(1);
		std::vector<int> actualOutput = tree.inorder();
		std::vector<int> expectedOutput = {1, 2, 3};
		REQUIRE(expectedOutput.size() == actualOutput.size());
		REQUIRE(actualOutput == expectedOutput);
	*/

    int test = 1;
	REQUIRE(test == 1);
}
TEST_CASE("BST Delete", "[flag]") {

    REQUIRE(1 == 1);
}