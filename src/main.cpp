#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "my_functions.h"

// Test cases take two parameters - the first is a test
// name and the second is a tag.
TEST_CASE( "My first test", "[testing, my_tests]" ){
	REQUIRE( 1 == 1 );
}

