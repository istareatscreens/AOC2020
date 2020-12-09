#include <iostream>
#include <memory>
#include <cstring>
#include <stdio.h>
#include <algorithm>
#include <typeinfo>
#include <functional>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


vector<vector<char>> readCharsFromFile(string fileName);

int main()
{
   //get all type data to write
	ostringstream ostr;

   string fileName = "input.txt";
	vector<vector<char>> temp = readCharsFromFile("input.txt");

	for(int i = 0; i<temp.size();i++){
		for(int j = 0;j<temp.size(); j++){
            
		}
	}

}

vector<vector<char>> readCharsFromFile(string fileName){

   //read from file
   std::ifstream file(fileName);
   if(file.is_open()){

   }else{
      cout<<"Error accessing file";
   }

   vector<vector<char>> chars;
   string input;
   int i=0;
   while(getline(file, input)){
	   istringstream istr{input}; //Add new array
      vector<char> line;
      chars.push_back(line); 
      while(true){
         char value; //temp read variable
         istr >> value;
         if(!istr.good()) break; //no good input
         chars[i].push_back(value); //add to array
      }
      i++; //increment
   }
	
   file.close();
	return chars;
}
 

