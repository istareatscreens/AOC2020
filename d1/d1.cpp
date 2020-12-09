#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{

  fstream f("index.txt"); 
  vector<int> v;
  string s{""};

  while(getline(f, s)){
   istringstream is{s};
   int i;
   is >> i;
   v.push_back(i);
  }
   for(int i = 0; i<v.size();i++){
      for(int j =0; j<v.size();j++){
         for(int k=0; k<v.size(); k++){
            if(v[i]+v[j]+v[k] == 2020){
               cout<<v[i]*v[j]*v[k];
               cout<<endl;
            }
         }
      }

   }



   return 0;
}
