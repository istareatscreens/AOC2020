#include <vector>
#include <unordered_map>
#include <cmath>
#include <deque>
#include <set>
#include <iostream>
#include <bitset>
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


using bInt = unsigned long long int;

int main(){

   ifstream file{"i.txt"};
   string str;
   vector<pair<bInt,bInt>> rangeValues1;
   vector<pair<bInt,bInt>> rangeValues2;

   regex rangeMatch{"\\d+-\\d+"};
   regex nearby {"nearby"};
   regex your {"your"};
   vector<vector<bInt>> nearbyValues;
   bool atNearbyTickets=false;
   bool atMyTicket=false;
   vector<int> myTicket;
   smatch match{};

   //P1
   size_t num{};
   size_t count{};
   while(getline(file,str)){
      if(regex_search(str,match,rangeMatch)){
         while(regex_search(str,match,rangeMatch)){
            string numbers = static_cast<string>(match[0]);
            if(num==1){
               rangeValues1.push_back( {stoi(numbers.substr(0,numbers.find('-'))), stoi(numbers.substr(numbers.find('-')+1, str.length()))});
               num--;
            }else if(num==0){
               rangeValues2.push_back( {stoi(numbers.substr(0,numbers.find('-'))), stoi(numbers.substr(numbers.find('-')+1, str.length()))});
               num++;
            }
            str=match.suffix();
         }
      }else if(regex_search(str, match,your)){
         atMyTicket = true;
      }else if(atMyTicket){
         istringstream input{str};
         string stringValue;
         while(getline(input, stringValue, ',')){
            myTicket.push_back(stoi(stringValue));
         }
         atMyTicket=false;
      }else if(regex_search(str, match,nearby)){
         atNearbyTickets=true;
      }else if(atNearbyTickets){
         vector<bInt> v;
         nearbyValues.push_back(v);
         istringstream input{str};
         string stringValue;
         while(getline(input, stringValue, ',')){
            nearbyValues[count].push_back(stoi(stringValue));
         }
         count++;
      }
   }

   bInt sum{};
   count=0;

   vector<vector<bInt>> validTickets;
   for(auto i=0;i<nearbyValues.size(); i++){
      bool saveTicket = true;
      for(auto j = 0;j<nearbyValues[i].size();j++){
         bool invalid = true;
         for(int m =0;m<rangeValues1.size();m++){
            if((nearbyValues[i][j]>=rangeValues1[m].first && nearbyValues[i][j]<=rangeValues1[m].second) ||(nearbyValues[i][j]>=rangeValues2[m].first && nearbyValues[i][j]<=rangeValues2[m].second) ){
               invalid=false;
            }
         }
         if(invalid){
            sum+=nearbyValues[i][j]; 
            saveTicket=false;
         }
      }
      if(saveTicket){
         validTickets.push_back(nearbyValues[i]);
      }
   }
   nearbyValues.clear();

   //P2
   vector<set<size_t>> membership;
   set<size_t> numbers;
   for(auto i = 0;i<validTickets[0].size();i++){
      numbers.insert(i);
   }

   for(auto i = 0;i<validTickets[0].size();i++){
      //set<bInt> numbers;
      membership.push_back(numbers);
   }

   for(auto i = 0; i<validTickets.size();i++){
      for(auto j = 0;j<validTickets[i].size();j++){
         for(auto m=0;m<rangeValues1.size();m++){
   //      cout<<rangeValues1[m].first<<" "<<rangeValues1[m].second<<" OR ";
   //      cout<<rangeValues2[m].first<<" "<<rangeValues2[m].second;
   //      cout<<endl;
               if(!((validTickets[i][j]>=rangeValues1[m].first && validTickets[i][j]<=rangeValues1[m].second) || (validTickets[i][j]>=rangeValues2[m].first && validTickets[i][j]<=rangeValues2[m].second))){
                  membership[j].erase(m); 
               }
            }
         }
      }

   count=0; 
   for(auto m: membership){
      cout<<count++<<" SET: ";
      for(auto i: m){
         cout<<i<<" ";
      }
      cout<<endl;
   }

   //narrow down seats
   set<size_t> closed;
   while(closed.size() < membership.size()){
   for(auto i = 0; i<membership.size();i++){
      if(closed.find(i)==closed.end() && membership[i].size() == 1){
         for(auto j = 0; j<membership.size();j++){
               if(j!=i){
                  membership[j].erase(*membership[i].begin());          
               }
         }
         closed.insert(i);
         }
      }
   }

   count=0; 
   for(auto m: membership){
      cout<<count++<<" SET: ";
      for(auto i: m){
         cout<<i<<" ";
      }
      cout<<endl;
   }

   //first 6
   bInt prod{1};
     for(auto i = 0; i<membership.size();i++){
         for(auto j = 0; j<6;j++){
            if(membership[i].find(j) != membership[i].end()){
               cout<<myTicket[i]<<" j: "<<j<<" i: "<<i<<", " ;
               prod*=myTicket[i];
            }
      }
   }
   cout<<endl;

   cout<<"P2 Results: "<<prod<<endl;
   cout<<"P1 Results: "<<sum<<endl;
   
}

