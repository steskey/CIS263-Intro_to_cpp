#include <vector>
#include <string>

std::string createString(){
	std::string hi("Hello world!");
	return hi;
}

std::vector<std::string> createVector(){
	std::vector<std::string> my_vector;
	my_vector.push_back(createString());
	my_vector.push_back(createString());
	my_vector.push_back(createString());
	return my_vector;
}

int putStringsInVector(int num){
	std::vector<std::string> my_strings;
	for(int i=0; i<num; i++){
		my_strings.push_back(createString());
	}
	return my_strings.size();
}

void modifyVector(std::vector<int> & vector){
	for(int i=0; i<vector.size(); i+=5){
		vector[i] = 42;
	}
}
