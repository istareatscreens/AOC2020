#include <iostream>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <string>
#include <fstream>
#include <regex>

using namespace std;


using bagVector = vector<pair<string,int>>;
int searchBag(vector<string> lines, pair<string,int> bag, regex excludeBag, vector<string> &nestedRules,int rec=0){
	int count{};
	string str{};

	smatch match;
   regex reg{bag.first};
   regex noGold{"shiny gold bag"};

   for(auto str: lines){
      //remove oriignal bag name
      string searchStr{str.substr(str.find("contain"))};
      //does not contain child bag, not looking at parent bag
		if(!regex_search(searchStr, match, excludeBag) && regex_search(searchStr, match, reg) && !regex_search(str,match,noGold)){
			string bagName{str.substr(0, str.find("s contain"))};
         //cout<<"BAG NAME TO SEARCH!!!!: "<<bagName;
         if(find(nestedRules.begin(), nestedRules.end(), bagName) == nestedRules.end()){

            nestedRules.push_back(bagName);
		   	int number{str.at(str.find(bag.first)-2)-'0'};
            cout<<endl<<"Recurse: "<<rec<<" ";
            cout<<str;
            cout<<endl<<"SEARCH BAG: "<<bag.first;
            cout<<endl<<"NAME: "<<bagName<<" NUM: "<<number<<endl;
		   	pair<string,int> bagMatch{bagName, number};
            //check bags for that bag
            count+=searchBag(lines, bagMatch, regex{bag.first}, nestedRules, (rec+1)) + 1;
      }
   }
}
	
   return count;
}


int main(){

   ifstream file{"i.txt" };
   string str;
	
   bagVector rules{};

   string sgBagReg{"shiny gold bag"};
	smatch match;
	regex reg{sgBagReg};
	int count{};
   vector<string> lines;

   while(getline(file, str)){
      string searchStr{str.substr(str.find("contain"))};
		if(regex_search(searchStr, match, reg)){
			string bagName{str.substr(0, str.find("s contain"))};
			int number{str.at(str.find(sgBagReg)-2)-'0'};
         cout<<"NAME: "<<bagName<<" NUM: "<<number<<endl;
			pair<string,int> bagMatch{bagName, number};
			rules.push_back(bagMatch); 	
			count++;
		}
      lines.push_back(str);
   }

	//reset file pointer
   /*
	file.clear();
	file.seekg(0,ios::beg);
   */

   vector<string> nestedRules{};
   for(auto rule: rules){
      nestedRules.push_back(rule.first);
   }

   for(auto rule: rules){
      count+=searchBag(lines,rule, reg, nestedRules);
   }

   cout<<"ANS: "<<count;
}
