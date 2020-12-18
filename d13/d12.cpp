//Source https://medium.com/@shelarvs11/chinese-remainder-theorem-information-security-solving-examples-with-steps-implement-using-4b8c5b339093
//Source https://www.geeksforgeeks.org/chinese-remainder-theorem-set-2-implementation/
#include <vector>
#include <unordered_map>
#include <cmath>
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

using bigInt = unsigned long long int;
bigInt calculateNextDeparture(bigInt busID, bigInt time){
   return static_cast<bigInt>(ceil(static_cast<long double>(time)/static_cast<long double>(busID)))*busID;
}

bigInt inv(long long int a, long long int m) 
{ 
    long long int m0 = m, t, q; 
    long long int x0 = 0, x1 = 1; 
 
    if (m == 1) 
    return 0; 

    // Apply extended Euclid Algorithm 
    while (a > 1) 
    { 
        // q is quotient 
        q = a / m; 
 
        t = m; 
 
        // m is remainder now, process same as 
        // euclid's algo 
        m = a % m, a = t; 
 
        t = x0; 
 
        x0 = x1 - q * x0; 
 
        x1 = t; 
    } 
 
    // Make x1 positive 
    if (x1 < 0) 
    x1 += m0; 
 
    return x1; 
} 

int main(){
   
   ifstream file{"i.txt"};
   int available{},  busID{};

   file>>available;
   cout<<"available: "<<available<<endl;
   string idStr;
   vector<pair<int,int>> ids;
   vector<pair<int,int>> busIds;

   int count{};
   bigInt M{1};
   
   //P1
   while(getline(file,idStr,',')){
      istringstream value;
      value.str(idStr);
      value.ignore(idStr.length(),'x');
      if(!value.eof()){
         count++;
         continue;
      }
      //cout<<"id: "<<value.str()<<endl;
      //value>>busID;
      busID = stoi(idStr);
      //cout<<"busID: "<<busID<<endl;
      //results.push_back(static_cast<double>(available)/static_cast<double>(busID));
      //P2
      M*=busID;
      busIds.push_back({busID,(count==0)? count++:busID-count++});
      
      //P1
      ids.push_back({ calculateNextDeparture(busID,available),
            busID});

   }

   sort(ids.begin(), ids.end());
   cout<<"Available: "<<available<<endl;
   cout<<"ID: "<<ids.front().second<<endl;
   cout<<"depart: "<<ids.front().first<<endl;

   cout<<"P1 Result: "<<(ids.front().first - available)*ids.front().second<<endl;
   
   //P2
   vector<bigInt> mPrime;
   vector<bigInt> m;

   cout<<"M: "<<M<<endl;
   for(auto [n,a]:busIds){
      cout<<"n: "<<n<<" a: "<<a<<endl;
      m.push_back(M/n);
		cout<<"M/n: "<<M/n<<" M/n\%n "<<(M/n)%n<<endl;
      mPrime.push_back(inv((M/n),n));
   }

   bigInt y{};
   for(auto i = 0;i<busIds.size();i++){
         y+=m[i]*mPrime[i]*busIds[i].second; 
   }

   cout<<"P2 RESULT: "<<(y%=M);
}

