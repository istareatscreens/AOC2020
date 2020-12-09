#include <iostream>
#include <sstream>
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

string bagContents(vector<string> lines, string bag){
   //cout<<endl<<"BAG: "<<bag<<endl;

   string listStart{"s contain "};
	smatch match;
	regex reg{bag};
   string oneBagContent;
   string fullBagContents;

   for(auto str: lines){
      string searchStr{str.substr(0, str.find("contain"))};
		if(regex_search(searchStr, match, reg)){
         //cout<<endl<<str<<endl;
         string searchStr = str.substr(0,str.find("contain"));
         //remove period at end
         oneBagContent=str.substr(str.find(listStart)+listStart.length(), str.length()-1);
         //cout<<oneBagContent<<endl;
         if(fullBagContents.length()==0){
            fullBagContents.append(" ").append(oneBagContent);
         }else{
            fullBagContents.append(", ").append(oneBagContent);
         }

      }
   }
   return fullBagContents.substr(0,fullBagContents.length()-1);
}

int innerBag(vector<string> lines, string contents){
   int sum{1};
	regex reg{"no other bags"};
	if(regex_search(contents, reg)) return 1;

   stringstream ss(contents);
   cout<<contents<<endl;
         while(ss.good()){

            string subString;
            getline(ss, subString,',');
        		int number = (int)subString.at(1) - '0';
            string bag = subString.substr(3,subString.find("bag"));
            string bagContent = bagContents(lines,bag);

               
            int result= innerBag(lines, bagContent );
            cout<<"-------------------------------------------------\n";
            cout<<endl<<"BAG TYPE: "<<bag<<" NUM: "<<number<<endl;
            cout<<endl<<"Bag CONTENT: "<<bagContent<<endl;
            sum+= number*(result);
				cout<<sum<<" = "<<number<<" * "<<result<<endl;
            cout<<"-------------------------------------------------\n";
         }

   return sum;
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
   vector<string> goldBagLine;

   string goldString{};

   string listStart{"s contain "};

   while(getline(file, str)){
      string searchStr{str.substr(str.find("contain"))};
		if(regex_search(searchStr, match, reg)){
			string bagName{str.substr(0, str.find("s contain"))};
			int number{str.at(str.find(sgBagReg)-2)-'0'};
         //cout<<"NAME: "<<bagName<<" NUM: "<<number<<endl;
			pair<string,int> bagMatch{bagName, number};
			rules.push_back(bagMatch); 	
			count++;
		}
      searchStr= str.substr(0,str.find("contain"));
		if(regex_search(searchStr, match, reg)){
         goldString = str;
      }
      lines.push_back(str);
   }

/*
   P1 answer:
   vector<string> nestedRules{};
   for(auto rule: rules){
      nestedRules.push_back(rule.first);
   }

   for(auto rule: rules){
      count+=searchBag(lines,rule, reg, nestedRules);
   }

   cout<<"P1 ANS: "<<count<<endl;
   */

   goldString = bagContents(lines, "shiny gold bag");
   cout<<"gold bag contents: "<<goldString<<endl;
	cout<<innerBag(lines, goldString)-1;
}


