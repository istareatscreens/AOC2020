#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <sstream>
#include <regex>


using namespace std;

int p1(){

/*
P1
   unordered_map<int,pair<string, int>> instructions {};
   int i{};
   while(true){
       if(!(instructions.find(i) == instructions.end())){
			cout<<"LAST INSTRUCTION: "<<i;
			break;
		}
      istringstream ss{lines[i].substr(3)};
      int number;
      ss>>number;
      string instruction{lines[i].substr(0,3)};
		cout<<instruction<<" "<<number<<endl;
      pair<string,int> values {instruction, number};
		instructions.insert({i,values});
      if(regex_search(lines[i],match, acc)){
			accumulator+=number;		
			i++;
      }else if(regex_search(lines[i],match, jmp)){
			cout<<i<<" + "<<number<<(i+number)<<endl;
			i+=number;
      }else{
			i++;
      }
   }

*/
return 0;

}


int main(){

   ifstream file{"i.txt"};
   string str{};
   regex nop{"nop"};
   regex acc{"acc"};
   regex jmp{"jmp"};
   int accumulator{};
   vector<string> lines{};

   while(getline(file,str)){
      lines.push_back(str);		
   }

	smatch match;
	
	bool instructionChanged=false;
   unordered_map<int,pair<int, bool>> instructions {};
   int i{};
   while(true){
      int number;
		if(i==lines.size()) break;
       if(i>lines.size() || !(instructions.find(i) == instructions.end())){
			cout<<"LAST INSTRUCTION: "<<i;
			instructions[i].second=true;
			accumulator = instructions[i].first;	
			instructionChanged = false;
		}else{
      	istringstream ss{lines[i].substr(3)};
      	ss>>number;
			cout<<lines[i]<<" "<<number<<endl;
      	pair<int,bool> values {accumulator,false};
			instructions.insert({i,values});
		}
      if(regex_search(lines[i],match, acc)){
			accumulator+=number;		
			i++;
      }else if(regex_search(lines[i],match, jmp)){
			if(!instructionChanged || (instructions[i].second)){
				cout<<i<<" + "<<number<<(i+number)<<endl;
				i+=number;
			}else{
				instructionChanged = true;
				i++;
			}
      }else{
			if(!instructionChanged || (instructions[i].second)){
				i++;
			}else{
				instructionChanged = true;
				cout<<i<<" + "<<number<<(i+number)<<endl;
				i+=number;
			}
      }
   }

	cout<<"ACCUMULATOR: "<<accumulator;


}
