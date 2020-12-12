#include <vector>
#include <unordered_map>
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

using seatMatrix=vector<vector<char>>;

void debug(seatMatrix &seats){
   cout << endl;
   for(auto s: seats){
      for(auto p: s){
         cout<<p<<" ";
      }
      cout<<endl;
   }
   cout << endl;
}

bool checkPosition(int x, int y, vector<pair<int,int>> &coordinates, seatMatrix &oldArrangement, int &spots){
   if(oldArrangement[x][y]=='L'){
      return true;
   }else if(oldArrangement[x][y] == '#'){
         spots++;
         return true;
   }
   return false;
}

void applyRulesP2(int i, int j, seatMatrix &seats, seatMatrix &oldArrangement){
   int spots{};
   //cout<<"i: "<<i<<", "<<"j: "<<j<<endl;
   
   vector<pair<int,int>> coordinates;
   for(int k = i - 1; k<i+2 && k<static_cast<int>(seats.size()); k++){
      if(k<0) continue;
      for(int m=j-1; m<j+2 && m<static_cast<int>(seats[k].size()); m++){
        if((k==i && j==m) || m<0) continue;
    //    cout<<"k: "<<k;
    //    cout<<", m: "<<m<<endl;
        if(oldArrangement[k][m]=='#'){
         spots++;
        }else if(oldArrangement[k][m] == '.'){
          coordinates.push_back({k,m});
        }
      }
   }
   
   //The worst thing I have ever coded maybe probably not...
      for(auto [x,y]: coordinates){
         if(x>i && y>j){
            for(;y<seats[x].size() && x<seats.size();x++, y++){
               if(checkPosition(x, y,coordinates, oldArrangement,spots)) goto DONE;
            }
         }else if(x<i && y>j){
            for(;x>=0 && y<seats[x].size();x--, y++){
            if(checkPosition(x, y,coordinates, oldArrangement,spots)) goto DONE;
            }         
         }else if(x>i && y<j){
            for(;x<seats.size() && y>=0;y--,x++){
            if(checkPosition(x, y,coordinates, oldArrangement,spots)) goto DONE;
            }
         }else if(x<i && y<j){
            for(;x>=0&&y>=0;y--,x--){
            if(checkPosition(x, y,coordinates, oldArrangement,spots)) goto DONE;
            }
         }else if(x == i && y<j){
               for(;y>=0;y--){
            if(checkPosition(x, y,coordinates, oldArrangement,spots)) goto DONE;
               }
         }else if(x==i && y>j){
               for(;y<seats[x].size();y++){
            if(checkPosition(x, y,coordinates, oldArrangement,spots)) goto DONE;
               }
         }else if(x<i && y==j){
               for(;x>=0;x--){
            if(checkPosition(x, y,coordinates, oldArrangement,spots)) goto DONE;
               }
         }else if(x>i && y==j){
               for(;x<seats.size();x++){
            if(checkPosition(x, y,coordinates, oldArrangement,spots)) goto DONE;
               }
         }
DONE:;
      }

      //cout<<"RESULTS: "<< spots['#']<<endl;
   if(seats[i][j] == '#' && spots>4){
      seats[i][j] = 'L';
//      cout<<"HERE";
   }else if(seats[i][j] == 'L' && spots == 0){
      seats[i][j] = '#';
   }
}


void applyRules(int i, int j, seatMatrix &seats, seatMatrix &oldArrangement){
   int spots;
//   cout<<"i: "<<i<<", "<<"j: "<<j<<endl;
   
   for(int k = i - 1; k<i+2 && k<static_cast<int>(seats.size()); k++){
      if(k<0) continue;
      for(int m=j-1; m<j+2 && m<static_cast<int>(seats[k].size()); m++){
        if((k==i && j==m) || m<0) continue;
//        cout<<"k: "<<k;
//        cout<<", m: "<<m<<endl;
         spots++;
      }
   }

   if(seats[i][j] == '#' && spots >3){
      seats[i][j] = 'L';
//      cout<<"HERE";
   }else if(seats[i][j] == 'L' && spots == 0){
      seats[i][j] = '#';
   }
}

int countEmptySeats( seatMatrix &seats){

   int emptySeats{};

   for(auto i = 0; i<seats.size(); i++){
      for(auto j=0 ;j<seats[i].size();j++){
         if(seats[i][j]=='#'){
            emptySeats++;
         }
      }
   }
   return emptySeats;

}


int main(){
   
   ifstream file{"i.txt"};

   seatMatrix seats;

   string row;
   while(getline(file,row)){
      istringstream line {row};
      char position;
      vector<char> rowValues;
      while(line>>position){
         if(position == 'L'){ //do initial change
            rowValues.push_back('#'); 
         }else{
            rowValues.push_back(position);
         }
      }
      seats.push_back(rowValues);
   }

   int currSeats = countEmptySeats(seats);
   int prevSeats = -1;
   while(currSeats-prevSeats){
      debug(seats);
      seatMatrix oldArrangement{seats};
      for(auto i = 0; i<seats.size();i++){
         for (auto j = 0; j < seats[i].size(); ++j) {
            applyRulesP2( i,  j, seats, oldArrangement);
         }
      }
      prevSeats = currSeats;
      currSeats = countEmptySeats(seats);
   }

   cout <<"ANS: "<<currSeats;

}

