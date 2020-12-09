#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>


using namespace std;


int getCount(unordered_map<char,char> m, vector<unordered_map<char,char>> g){
      int count{};
      for(auto [k,v] : m){
         for(auto p: g){
            if(p.find(k) == p.end()){
               goto elementNotFound;
            }
         }         
         count++;
elementNotFound:;
   }
   return count;
}

int main(){

   ifstream f{"i.txt"};
   vector<unordered_map<char,char>> g{};

   string str{};
   int sum{};
   int sumP1{};
   unordered_map<char, char> m{};
   while(getline(f,str)){
       if(str.length()==0){
            sum+=getCount(m,g);
            sumP1+=m.size();
            m.clear();
            g.clear();
       }else{
         unordered_map<char, char> mp{};
         for(const auto& c: str){
           m.insert({c, 'y'}); 
           mp.insert({c, 'y'});
         }
         g.push_back(mp);
      }
}

      int last = getCount(m,g);
      cout<<"LAST VAL CHECK "<<last<<endl;
      sum+=last;
      sumP1+=m.size();
      m.clear();
      g.clear();

  cout<<"P1 ANS: "<<sumP1<<endl;
  cout<<"sum: "<<sum<<endl;
      
}

