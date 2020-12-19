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

using m64 = uint_fast64_t;

void getMasksPart2(vector<pair<m64,m64>> &memMasks,vector<size_t> shifts){
   memMasks.clear(); 
   m64 size=pow(2,shifts.size())-1;
   do{
      //m64 mask=!0ULL;
      m64 mask{size}; //decrements size
//      cout << bitset<64>(mask) << endl;
      m64 zeroMask{0};
      m64 oneMask{0};
      for(int i=0;i<shifts.size();i++){
            m64 bit = 1ULL&mask;
 //           cout<<bitset<64>(mask)<<" "<<bit<<" HERE"<<endl;
            if(bit == 0){
               zeroMask|=1ULL<<(shifts[i]);
            }else if(bit == 1){
               oneMask|=1ULL<<(shifts[i]);
            }
            //cout<<"ZERO: "<<bitset<64>(temp)<<endl;
            mask=mask>>1;
       }
      //cout<<"IT ZERO: "<<bitset<64>(~zeroMask)<<endl;
      //cout<<"IT ONE:  "<<bitset<64>(oneMask)<<endl;
      memMasks.push_back({~zeroMask,oneMask});
   }while(size--);

   cout<<endl;
   cout<<memMasks.size()<<endl;
   int count{};
   for(auto [z,o]: memMasks){
      cout<<count<<" MASKS ZERO: "<<bitset<64>(z)<<endl;
      cout<<count++<<" MASKS ONE:  "<<bitset<64>(o)<<endl<<endl;
   }
   cout<<endl;

}

void getMasks(vector<m64> &masks, vector<size_t> &shifts, string str){
   masks.clear();
   shifts.clear();
   str = str.substr(7,str.length());
   masks.push_back(0);
   masks.push_back(0);
   cout<<str<<endl;
   for(auto i = static_cast<int>(str.length())-1,j=0; i>=0;i--,j++){
      m64 temp = 0;
      if(str.at(i)=='0'){
         //temp=1ULL<<(j);
         temp=1ULL<<(j);
//         cout<<"ZERO: "<<bitset<64>(temp)<<endl;
         masks[0]|=temp;
      }else if(str.at(i)=='1'){
         temp=1ULL<<(j);
         //cout<<" ONE: "<<bitset<64>(temp)<<endl;
         masks[1]|=temp;
      }else if(str.at(i)=='X'){
         //temp=1ULL<<(j);
         //cout<<" ONE: "<<bitset<64>(temp)<<endl;
         //masks[2]|=temp;
         //masks[2]=!masks[2];
         shifts.push_back(j);
      }
   }
   masks[0]=~masks[0];
   cout<<"MASK0     "<<bitset<64>(masks[0])<<endl;
   cout<<"MASK1     "<<bitset<64>(masks[1])<<endl;
}

pair<int,int> getNumbers(string str, regex memNumbers, smatch match){
         pair<int,int> indexValue;
         int Number{}, index{};
         while(regex_search(str,match,memNumbers)){
               string number = static_cast<string>(match[0]);
               if(number.at(0) == '['){
                 index = stoi(number.substr(1,number.length())); 
               }else{
                  cout<<"Number: "<<stoi(number.substr(4,number.length()))<<" "<<endl;
                  cout<<"index: "<<index<<endl;
                  
                  Number =stoi(number.substr(4,number.length()));
               }
               str=match.suffix();
         }
         return {index,Number};
}



int main(){

   ifstream file{"i.txt"};
   string str;
   vector<m64> masks;
   vector<size_t> floatingShifts;
   unordered_map<m64,m64> memory;
   unordered_map<m64,m64> memoryP2;
   m64 indexTemplate{};
   vector<pair<m64,m64>> memMasks;

   regex memNumbers{"\\[\\d+|\\] = \\d+"};
   smatch match{};

   //P1
   while(getline(file,str)){
      uint_fast64_t numberToWrite;
      size_t index;
      if(regex_search(str,match,memNumbers)){
         //P1
         pair<m64,m64> indexValue = getNumbers(str, memNumbers, match);
         memory[indexValue.first] = ((indexValue.second)&masks[0])|masks[1]; 
         indexValue.first|=masks[1]; 
         getMasksPart2(memMasks, floatingShifts);
         cout<<"ADDRESSES:"<<endl;
         for(auto mask: memMasks){
            cout<<bitset<64>((indexValue.first&mask.first)|mask.second)<<endl;
            memoryP2[((indexValue.first&mask.first)|mask.second)]=indexValue.second;
         }
         cout<<endl;
      }else{
         getMasks(masks, floatingShifts, str);
      }
   }

   m64 sum{};
   for(auto [key,value]: memory){
      sum+=value;
   }
   cout<<"P1 Results: "<<sum<<endl;

   sum=0;
   for(auto [key,value]: memoryP2){
      sum+=value;
   }
   cout<<"P2 Results: "<<sum;
   //P2
   
}

