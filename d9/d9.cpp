#include <vector>
#include <bits/stdc++.h>
#include <deque>
#include <set>
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

void calculateSums(deque<int> &preamble, set<int> &sums){
   sums.clear();
   for(int i=0; i<preamble.size();i++){
      for(int j=0; j<preamble.size();j++){
         if(i!=j){
            sums.insert(preamble[i] + preamble[j]);     
         }
      }
   }
}

void updatePreamble(deque<int> &preamble, set<int> &sums, int number){
   preamble.pop_back();     
   preamble.push_front(number);
   calculateSums(preamble,sums);
}

int main(){
   
   ifstream file{"i.txt"};
   string str{};

   //if(regex_search(lines[i],match, acc))
   vector<int> numbers;
   int number{};

   while(file>>number){
      numbers.push_back(number);
   }

   int preambleLength{25};
   set<int> sums{}; 
   deque<int> preamble{};

   //initiate numbers
   for(int i = 0; i <preambleLength;i++){
      preamble.push_front(numbers[i]);
   }

   calculateSums(preamble,sums);
   int invalidNum{0};
   int i = preambleLength;
   for(; i<numbers.size();i++){
         if(!sums.count(numbers[i])){
            invalidNum = numbers[i];
            goto L1;
         }else{
            updatePreamble(preamble, sums, numbers[i]); 
         }
   }
L1:

         cout<<"Invalid Num: "<<invalidNum<<" index: "<<i;
         int j = 0;
         int k =0;
         for(; j<i;j++){
            int sum{0};
            sum+=numbers[j];
            for(k=j+1; k<i;k++){
               sum+=numbers[k];
               if(!(j == k) && invalidNum == sum ){
                  cout<<j<<", "<<k<<endl;
                  cout<<"NUMBERS "<<numbers[j]<<", "<<numbers[k]<<" SUM= "<<sum<<endl;
                  goto L2;
               }
            }
         }
L2:
         int max = INT_MIN;
         int min = INT_MAX;
         for(int m = j; m<k+1;m++){
            if(numbers[m] > max){
               max = numbers[m];
            }
            if(numbers[m] < min){
               min = numbers[m];
            }
         }
         cout<<"ANS: "<<(min + max);



         return 0;
}

