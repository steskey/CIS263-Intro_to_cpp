#include "my_functions.h"

std::string createString(){
	return std::string("Hello world!");
}

std::vector<std::string> createVector(){
	return std::vector<std::string>();
}

int putStringsInVector(int num){
	std::vector<std::string> myVector = createVector();
	for(int i = 0; i < num; ++i){
		myVector.push_back(createString());
	}
	return myVector.size();
}

void modifyVector(std::vector<int> & vector){
	for(int i = 0; i < vector.size(); ++i){
		// The 5th element corresponds to index i=4
		if( (i % 5) == 0 ){
			vector[i] = 42;	
		}	
	}	
}

