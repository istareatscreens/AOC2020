#include <iostream>
#include <cassert>
#include <algorithm>
#include <exception>
#include <memory>
#include <ctype.h>
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

//global variables


int q3(int x, int y);
std::vector<char> transpose_vector(const std::vector<std::vector<char>> &column_vec);
vector<vector<int>> readIntsFromLines(vector<string> strings);
vector<string> readLinesFromFile(string fileName);
vector<vector<double>> readDoubleFromLines(vector<string> strings);
vector<vector<char>> readCharsFromLines(vector<string> strings);
int countChar(vector<char> chars, char value);
bool validLetterPlacement(vector<char> chars, char let, int pos1, int pos2);
int charToInt(char c);

   auto lines = readLinesFromFile("index.txt");
   auto chars = readCharsFromLines(lines);
   auto ints = readIntsFromLines(lines);

int main()
{
   //get all type data to write
	ostringstream ostr;

      


/*
   vector<vector<char>> chars;
   for(int j = 0;j<tchars[0].size();j++){
      vector<char> t;
      for(int i = 0; i<tchars.size();i++){
         t.push_back(tchars[i][j]);
      }
      chars.push_back(t);
      t.clear();
   }
   //transpose vector


    //debug arrays
   for (int i = 0; i < chars.size(); ++i) {
      for (int j = 0; j < chars[i].size(); j++) {
         cout<<chars[i][j];
      }
      cout<<endl;
   }
   

   */
   /*
   int count = 0;
   for(int i = 0, j=0;i<chars.size();i++, j+=3){
      cout<<(i+1)<<" "<<lines[i]<<" ";
      if(j==0) j++;
      if( !(j<chars[i].size()) ){
         //break;
         j=0;
      }
      cout<<"> "<<i<<","<<j;
      if(chars[i][j] == '#'){
         count++;
         cout<<" : #";
      }
         cout<<endl;

   }
   cout<<endl<<"ans";
   cout<<count;
   */
/*
   int validCount = 0;
   int i = 0;
   for(auto cs: chars){
      bool foundL=false;
      char letter = ' ';

      for(auto c: cs){
         if(!foundL && isalpha((char)c)){
            letter=c;
            break;
         }
      }

     cout<<"Letter is: "<<letter<<"bounds: "<<ints[i][0]<<", "<<ints[i][1]<<" count: "<<countChar(cs,letter);
      if(countChar(cs,letter) >= ints[i][0]  && countChar(cs, letter) <= ints[i][1]){
//         validCount++;
      }
      if(validLetterPlacement(chars[i], letter, ints[i][0], ints[i][1])){
         validCount++;
         cout<<boolalpha<<" "<<true;
      }
      i++;
      cout<<endl;
   }
   cout<<"VALID NUMBER: "<<validCount;
   */

   cout<<endl<<"ANS: "<<(q3(1,1)*q3(3,1)*q3(5,1)*q3(7,1)*q3(1,2));

}

int q3(int x, int y){

   int ans = 0;
   for(int i = 0, m =0; i<chars.size();m+=x, i+=y){
      m = m%31;
      for(int j=0;j<chars[i].size();j++){
        if(j==m){
         if(chars[i][j] == '#'){
            cout<<"O";
            ans++;
         }else{
            cout<<"X";
         }
        }else{
         cout<<chars[i][j];
        }
      }
      cout<<endl;
   }

   cout<<endl<<ans<<"ans";
   return ans;

}



bool validLetterPlacement(vector<char> chars, char let, int pos1, int pos2){
   long unsigned int i = 0;
   for(i = 1; i<chars.size();i++){
     if(chars[i-1] == ':') break;
   }

   for(int j = i; j<chars.size();j++){
      cout<<chars[j];
   }
   cout<<endl;

   return ((chars[i+pos1-1] == let && !(chars[i+pos2-1] == let)) || 
          (!(chars[i+pos1-1] == let) && chars[i+pos2-1] == let));

}

int countChar(vector<char> chars, char value){
int count= -1;
   for(auto c: chars){
      if(c==value) count++;
   }
   return count;
}

vector<string> readLinesFromFile(string fileName){
   //read from file
   std::ifstream file(fileName);
   if(!file.is_open()){
      throw runtime_error{string{"file not found"}};
   }
   vector<string> strings;
   string input;
   while(getline(file, input)){
      strings.push_back(input); //add to array
   }
	
   file.close();
   return strings;
}
 
 
vector<vector<double>> readDoubleFromLines(vector<string> strings){
   //read from file
   vector<vector<double>> ints;
   string input;
   int i=0;
   for(auto s: strings){
	   istringstream istr{s}; //Add new array
      vector<double> line;
      ints.push_back(line); 

     while(!istr.eof()){
     string temp;
     istr>>temp;
         double found;
         if(stringstream{temp}>>found){ //number found
            ints[i].push_back(found); //add to array
         }
      }
      i++; //increment
   }
   return ints;
}
 
vector<vector<int>> readIntsFromLines(vector<string> strings){
   //read from file
   vector<vector<int>> ints;
   string input;
   int i=0;
   for(auto s: strings){
	   //istringstream istr{s}; //add line to istr

      vector<int> line; // make a new array
      ints.push_back(line); 

      replace(s.begin(), s.end(), '-',' ');
      stringstream stream(s);
      while(1)
       {
         int found;
         stream>>found;
         ints[i].push_back(found); //add to array
         if(!stream)
              break;
       }

       i++;
     } 

   return ints;
}
 
 
vector<vector<char>> readCharsFromLines(vector<string> strings){
   //read from file
   vector<vector<char>> chars;
   string input;
   int i=0;
   for(auto s: strings){
	   istringstream istr{s}; //Add new array
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
   return chars;
}
