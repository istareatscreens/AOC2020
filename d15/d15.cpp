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

using m64 = unsigned long long int;

int main(){

   //vector<int> input = {0,3,6};//test
   vector<m64> input = {8,13,1,0,18,9};//actual
   map<m64,pair<m64,m64>> count;
   vector<m64> length = {2020, 30000000};
   vector<m64> ans;

   for(auto l : length){

      count.clear();
      int lastNumber{};
      for(int i =0;i<l;i++){
         if(i<input.size()){
            count[input[i]] = pair<m64,m64>{i+1,0};
            lastNumber = input[i];
         }else{
             if(count[lastNumber].second == 0){
               lastNumber = 0;
               count[lastNumber].second = count[lastNumber].first;
               count[lastNumber].first = i+1;
             }else{
               lastNumber = count[lastNumber].first - count[lastNumber].second;
               if(count.find(lastNumber) == count.end()){
                  count[lastNumber] = pair<m64,m64>{i+1,0};
               }else{
                  count[lastNumber].second = count[lastNumber].first;
                  count[lastNumber].first = i+1;
               }
             }
         }
         cout<<"i: "<<i<<" "<<lastNumber<<endl;
      }

      ans.push_back(lastNumber);
   }
   cout<<"P1: "<<ans[0]<<endl;
   cout<<"P2: "<<ans[1]<<endl;

   /*
   string str;
   vector<m64> masks;
   vector<size_t> floatingShifts;
   unordered_map<m64,m64> memory;
   unordered_map<m64,m64> memoryP2;
   m64 indexTemplate{};
   vector<pair<m64,m64>> memMasks;

   regex memNumbers{"\\[\\d+|\\] = \\d+"};
   smatch match{};
   */


   //P1
   
}

