#include <vector>
#include <functional>
#include <queue>
#include <set>
#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <list>
#include <unordered_map>
#include <sstream>
#include <regex>


using namespace std;
using std::cout;

using hashmap = unordered_map<int,pair<string, int>>;

void getAdaptors(vector<int> &adaptors, ifstream &file){
   int adaptor;
   while(file>>adaptor){
     adaptors.push_back(adaptor); 
   }

}



int main(){
   
   ifstream file{"i.txt"};
   string str{};

   //if(regex_search(lines[i],match, acc))while

   vector<int> adaptors;
   getAdaptors(adaptors, file);
   adaptors.push_back(0); //account for outlet

   sort(adaptors.begin(), adaptors.end());
   adaptors.push_back(adaptors.back()+3); //account device charger

   vector<vector<int>> ratings;
   for(auto i = 0;i<3;i++){
      vector<int> rating;
      ratings.push_back(rating);
   }


   for(auto i=1;i<adaptors.size();i++){
      switch(adaptors[i]-adaptors[i-1]){
         case 1:
              ratings[0].push_back(adaptors[i]); 
              break;
         case 2:
              ratings[1].push_back(adaptors[i]); 
              break;
         case 3:
              ratings[2].push_back(adaptors[i]); 
              break;
         default:
              std::cout << adaptors[i]-adaptors[i-1];
         std::cout << "Error invalid difference" << std::endl;
      }
   }

   cout<<"1, 2, 3 differences: "<<ratings[0].size()<<", "<<ratings[1].size()<<", "<<ratings[2].size()<<endl; 

   cout<<"ANS: "<<ratings[0].size()*ratings[2].size()<<endl;

   //P2
   map<int,unsigned long long int> adaptorSet;
   for(int i = 0 ; i<adaptors.size(); i++){
      adaptorSet.insert({adaptors[i],0});
   }
   adaptorSet[0] = 1;

   for(auto adaptor: adaptors){
      for(int j=1; j<4;j++){
         int connectAdaptor = adaptor+j;
         if(!(adaptorSet.find(connectAdaptor) == adaptorSet.end())){
              adaptorSet[connectAdaptor]+=adaptorSet[adaptor]; 
         }
      }
   }

   cout<<"ANS: "<<adaptorSet[adaptors[adaptors.size()-1]];

}
