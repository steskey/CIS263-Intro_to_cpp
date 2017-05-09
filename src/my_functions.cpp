#include "my_functions.h"

std::string createString(){
    //Creates a string and returns it by value
    return std::string("Hello world!");
}

std::vector<std::string> createVector(){
    //Creates a vector of strings and returns it by value
    return std::vector<std::string>();
}

int putStringsInVector(int num){
    //Initializes a vector to the vector returned by createVector()
    std::vector<std::string> myVector = createVector();

    /** 
      Calls createString num times and appends the returned string
      to the vector each time.
    */
    for(int i = 0; i < num; ++i){
        myVector.push_back(createString());
    }

    //Returns final size of the vector, which should equal num
    return myVector.size();
}

void modifyVector(std::vector<int> & vector){
    //Loops through all the integers contained in referenced vector
    for(int i = 0; i < static_cast<int>(vector.size()); ++i){
        //If the index is divisible by 5, changes the contents to 42
        if( (i % 5) == 0 ){
            vector[i] = 42;	
        }
    }	
}
