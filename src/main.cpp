#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "my_functions.h"

// Test cases take two parameters - the first is a test
// name and the second is a tag.
// This test merely checks that 1 is equal to 1.  It
// should always pass.  It is included here to show how
// to write test cases.

TEST_CASE( "My first test", "[testing, my_tests]" ){
	// REQUIRE causes the execution to stop
	// if the test fails.
	REQUIRE( 1 == 1 );
}

// The following test checks to see if the createString
// function works correctly.

TEST_CASE( "Testing createString", "[createString]" ){
	// CHECK will run the test but continue
	// checking other tests regardless of whether
	// or not this test passes.
	CHECK( createString() == "Hello world!");
}

TEST_CASE( "Testing createVector", "[createVector]" ){
	std::vector<std::string> my_vector = createVector();
	my_vector.push_back(createString());
	my_vector.push_back(createString());
	my_vector.push_back(createString());
	CHECK( my_vector.size() == 3 );
}

TEST_CASE( "Testing putStringsInVector", "[putStringsInVector]"){
	CHECK( putStringsInVector(5) == 5);
	CHECK( putStringsInVector(3) == 3);
	CHECK( putStringsInVector(0) == 0);
	CHECK( putStringsInVector(11) == 11);
}

TEST_CASE( "Testing modifyVector", "[modifyVector]"){
	std::vector<int> vector;
	for(int i=0; i<100; i++){
		vector.push_back(i);
	}
	modifyVector(vector);
	for(int i=0;i<100; i+=5){
		CHECK( vector[i] == 42);
	}
}
