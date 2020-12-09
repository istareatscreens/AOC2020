#include <vector>
#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <sstream>
#include <regex>


using namespace std;
using std::cout;

void p1(vector<string> lines, regex acc, regex jmp){

   smatch match{};

   int accumulator{};
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
cout<<accumulator;

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
   stack<int> oldInc{}; 
   stack<int> oldAcc{};
   unordered_map<int,pair<int, bool>> instructions {};
   bool allowChange = true;

   int i{};
   while(true){
      int number;
       if((i<0 || static_cast<long unsigned int>(i)>lines.size()) ||(!(instructions.find(i) == instructions.end()) && oldAcc.size() == 1)){
         cout<<endl<<"\tREVERT BACK "<<i<<" "<<lines[i];
         i = oldInc.top();
         oldInc.pop();
         accumulator = oldAcc.top();
         oldAcc.pop();
         cout<<endl<<"\tREVERT BACK "<<i<<" "<<lines[i];
         instructions[i].second=false;
         allowChange = true;
      	istringstream ss{lines[i].substr(3)};
      	ss>>number;
		}else{
      	istringstream ss{lines[i].substr(3)};
      	ss>>number;
      	pair<int,bool> values {accumulator,true};
			instructions.insert({i,values});
      }

      if(regex_search(lines[i],match, acc)){
            cout<<endl<<i<<" "<<lines[i];
			   accumulator+=number;		
			   i++;
      }else if(regex_search(lines[i],match, jmp)){
         cout<<endl<<i<<" "<<lines[i];
         if(allowChange && instructions[i].second){
            allowChange = false;
            oldInc.push(i); 
            oldAcc.push(accumulator);
            cout<<" CHANGED JUMP to NOP: ";
            i++;
         }else{
			  i+=number;
         }
      }else{
         cout<<endl<<i<<" "<<lines[i];
         if(allowChange && instructions[i].second && (number!=0)){
            allowChange = false;
            oldInc.push(i); 
            oldAcc.push(accumulator);
            cout<<" CHANGED NOP to JUMP: ";
			   i+=number;
         }else{
			   i++;
         }
      }
       if(static_cast<long unsigned int>(i) == lines.size()) break;
   }

	cout<<endl<<"ACCUMULATOR: "<<accumulator;

}
